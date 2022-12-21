/*
% Copyright (C) 2022 GraphicsMagick Group
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                   J  X X  L                                 %
%                                   J   X   L                                 %
%                                 JJJ  X X  LLL                               %
%                                                                             %
%                        Read/Write JPEG-XL Image Format.                     %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Status: Only support basic images (no animations) with grayscale/SRGB colorspace
* Note that JXL is a C++ library so does require linking with a c++ compiler.
*
* Currently tested vs libjxl-0.7.0 on ubuntu only, likely will have build problems
* on other platforms. Also note the amount of third-party-libs required!
*
* Features still to be completed:
*
*   * Support premultiplied alpha
*   * Support Alpha bits != RGB sample bits
*   * Support CMYK layers
*   * Support progressive
*   * Support embedded profiles
*   * Support 16-bit float ("Half") format
*   * Support progress monitor
*   * Use import/export functions (ImportImagePixelArea()/ExportImagePixelArea())
*/

#include "magick/studio.h"
#include "magick/analyze.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/log.h"
#include "magick/constitute.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/profile.h"
#include "magick/utility.h"
#include "magick/resource.h"

#if defined(HasJXL)
#include <jxl/decode.h>
#include <jxl/encode.h>
#include <jxl/thread_parallel_runner.h>

#define MaxBufferExtent 16384

struct MyJXLMemoryManager {
  JxlMemoryManager super;
  ExceptionInfo *exception;
  const char *filename;
};

static void *MyJXLMalloc(void *opaque, size_t size)
{
  unsigned char
    *data=MagickAllocateResourceLimitedMemory(unsigned char *,size);
  if (data == (unsigned char *) NULL)
    {
      struct MyJXLMemoryManager
        *mm = (struct MyJXLMemoryManager*)opaque;
      ThrowException(mm->exception, ResourceLimitError,MemoryAllocationFailed,
                     mm->filename);
    }
  return data;
}

static void MyJXLFree(void *dummy, void *address)
{
  (void)(dummy);
  MagickFreeResourceLimitedMemory(address);
}

static void MyJxlMemoryManagerInit(struct MyJXLMemoryManager *mm,
                                   Image *image,ExceptionInfo *exception)
{
  mm->exception=exception;
  mm->filename=image->filename;
  mm->super.opaque=mm;
  mm->super.alloc=MyJXLMalloc;
  mm->super.free=MyJXLFree;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d J X L I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadJXLImage() reads an image in the JXL image format.
%
%  The format of the ReadJXLImage method is:
%
%      Image *ReadJXLImage(const ImageInfo *image_info,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image_info: the image info.
%
%    o exception: return any errors or warnings in this structure.
%
*/
static inline OrientationType convert_orientation(JxlOrientation orientation)
{
  switch (orientation)
    {
    default:
    case JXL_ORIENT_IDENTITY:
      return TopLeftOrientation;
    case JXL_ORIENT_FLIP_HORIZONTAL:
      return TopRightOrientation;
    case JXL_ORIENT_ROTATE_180:
      return BottomRightOrientation;
    case JXL_ORIENT_FLIP_VERTICAL:
      return BottomLeftOrientation;
    case JXL_ORIENT_TRANSPOSE:
      return LeftTopOrientation;
    case JXL_ORIENT_ROTATE_90_CW:
      return RightTopOrientation;
    case JXL_ORIENT_ANTI_TRANSPOSE:
      return RightBottomOrientation;
    case JXL_ORIENT_ROTATE_90_CCW:
      return LeftBottomOrientation;
    }
}

/** Convert any linear RGB to SRGB
 *  Formula from wikipedia:
 *      https://en.wikipedia.org/wiki/SRGB
 */
static void linear2nonlinear_quantum(Quantum *q)
{
  double p = *q * (1.0/256.0);
  if (p < 0.0031308) {
    p=p * 12.92;
  } else {
    p=1.055 * pow(p, 1.0/2.4) - 0.055;
  }
  *q = RoundDoubleToQuantum(p * MaxRGBDouble);
}

static const char *JxlTransferFunctionAsString(const JxlTransferFunction fn)
{
  const char *str = "Unknown";

  switch (fn)
    {
    case JXL_TRANSFER_FUNCTION_709:
      str = "Rec709 (SMPTE RP 431-2)";
      break;
    case JXL_TRANSFER_FUNCTION_UNKNOWN:
      str = "Unknown";
      break;
    case JXL_TRANSFER_FUNCTION_LINEAR:
      str = "Linear (Gamma 1.0)";
      break;
    case JXL_TRANSFER_FUNCTION_SRGB:
      str = "sRGB (IEC 61966-2-1)";
      break;
    case JXL_TRANSFER_FUNCTION_PQ:
      str = "PQ (SMPTE ST 428-1)";
      break;
    case JXL_TRANSFER_FUNCTION_DCI:
      str = "DCI (SMPTE ST 428-1)";
      break;
    case JXL_TRANSFER_FUNCTION_HLG:
      str = "HLG (Rec. ITU-R BT.2100-1)";
      break;
    case JXL_TRANSFER_FUNCTION_GAMMA:
      str = "Gamma (use gamma from JxlColorEncoding)";
      break;
    }

  return str;
}

static const char *JxlColorSpaceAsString(const JxlColorSpace color_space)
{
  const char *str = "Unknown";

  switch (color_space)
    {
    case JXL_COLOR_SPACE_RGB:
      str = "Tristimulus RGB";
      break;
    case JXL_COLOR_SPACE_GRAY:
      str = "Luminance based (Gray)";
      break;
    case JXL_COLOR_SPACE_XYB:
      str = "XYB (opsin)";
      break;
    case JXL_COLOR_SPACE_UNKNOWN:
      str = "Unknown";
      break;
    }

  return str;
}

static const char *JxlDataTypeAsString(const JxlDataType data_type)
{
  const char *str = "Unknown";

  switch (data_type)
    {
    case JXL_TYPE_FLOAT:
      str = "Float";
      break;
    case JXL_TYPE_UINT8:
      str = "UINT8";
      break;
    case JXL_TYPE_UINT16:
      str = "UINT16";
      break;
    case JXL_TYPE_FLOAT16:
      str = "FLOAT16";
      break;
    }

  return str;
}

#define JXLReadCleanup()                                \
  MagickFreeResourceLimitedMemory(out_buf);             \
  MagickFreeResourceLimitedMemory(in_buf);              \
  if (jxl_thread_runner)                                \
    JxlThreadParallelRunnerDestroy(jxl_thread_runner);  \
  if (jxl)                                              \
    JxlDecoderDestroy(jxl);


#define ThrowJXLReaderException(code_,reason_,image_)   \
  {                                                     \
    JXLReadCleanup();                                   \
    ThrowReaderException(code_,reason_,image_);         \
  }

static Image *ReadJXLImage(const ImageInfo *image_info,
                           ExceptionInfo *exception)
{
  Image
    *image;

  JxlDecoder
    *jxl = NULL;

  void
    *jxl_thread_runner = NULL;

  JxlDecoderStatus
    status;

  JxlPixelFormat
    format;

  struct MyJXLMemoryManager
    mm;

  const size_t
    in_len = MaxBufferExtent;

  unsigned char
    *in_buf = NULL,
    *out_buf = NULL;

  MagickBool
    grayscale = MagickFalse;

  MagickBool
    isLinear = MagickFalse;

  magick_off_t
    blob_len = 0;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);

  memset(&format,0,sizeof(format));

  /*
    Open image file.
  */
  image=AllocateImage(image_info);
  if (image == (Image *) NULL)
    ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  if (OpenBlob(image_info,image,ReadBinaryBlobMode,exception) == MagickFail)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);

  /* Init JXL-Decoder handles */
  MyJxlMemoryManagerInit(&mm,image,exception);
  jxl=JxlDecoderCreate(&mm.super);
  if (jxl == (JxlDecoder *) NULL)
    ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  /* Deliver image as-is. We provide autoOrient function if user requires it */
  if (JxlDecoderSetKeepOrientation(jxl, JXL_TRUE) != JXL_DEC_SUCCESS)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  if(!image_info->ping)
    {
      jxl_thread_runner=JxlThreadParallelRunnerCreate(NULL,(size_t) GetMagickResourceLimit(ThreadsResource));
      if (jxl_thread_runner == (void *) NULL)
        ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);
      if (JxlDecoderSetParallelRunner(jxl, JxlThreadParallelRunner, jxl_thread_runner)
          != JXL_DEC_SUCCESS)
        ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    }

  if (JxlDecoderSubscribeEvents(jxl,
                                (JxlDecoderStatus)(image_info->ping == MagickTrue
                                                   ? JXL_DEC_BASIC_INFO
                                                   : JXL_DEC_BASIC_INFO |
                                                   JXL_DEC_FULL_IMAGE |
                                                   JXL_DEC_COLOR_ENCODING)
                                ) != JXL_DEC_SUCCESS)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  in_buf=MagickAllocateResourceLimitedArray(unsigned char *,in_len,sizeof(*in_buf));
  if (in_buf == (unsigned char *) NULL)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  blob_len = GetBlobSize(image);

  status=JXL_DEC_NEED_MORE_INPUT;
  while (status != JXL_DEC_ERROR && status != JXL_DEC_SUCCESS)
    {
      switch (status)
        {
        case JXL_DEC_NEED_MORE_INPUT:
          { /* read something from blob */
            size_t
              remaining = JxlDecoderReleaseInput(jxl),
              count;

            if (remaining > 0)
              memmove(in_buf,in_buf+in_len-remaining,remaining);
            count=ReadBlob(image,in_len-remaining,in_buf+remaining);
            if (count == 0)
              ThrowJXLReaderException(CorruptImageError, UnexpectedEndOfFile, image);
            status = JxlDecoderSetInput(jxl,(const uint8_t *) in_buf, (size_t) count);
            if (blob_len > 0)
              {
                /* If file size is known pass the info about the last block,
                   to the decoder. Note that the call is currently optional */
                blob_len -= count;
                if (blob_len == 0)
                  JxlDecoderCloseInput(jxl);
              }
            break;
          }
        case JXL_DEC_BASIC_INFO:
          { /* got image information */
            JxlBasicInfo
              basic_info;

            JxlEncoderInitBasicInfo(&basic_info);

            status=JxlDecoderGetBasicInfo(jxl,&basic_info);
            if (status != JXL_DEC_SUCCESS)
              break;

            if (image->logging)
              {
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "Basic Info:\n"
                                      "    xsize=%u\n"
                                      "    ysize=%u \n"
                                      "    bits_per_sample=%u\n"
                                      "    exponent_bits_per_sample=%u\n"
                                      "    alpha_bits=%u\n"
                                      "    num_color_channels=%u",
                                      basic_info.xsize, basic_info.ysize,
                                      basic_info.bits_per_sample, basic_info.exponent_bits_per_sample,
                                      basic_info.alpha_bits, basic_info.num_color_channels);
              }

            if (basic_info.have_animation == 1)
              ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);

            image->columns=basic_info.xsize;
            image->rows=basic_info.ysize;
            image->depth=basic_info.bits_per_sample;
            if (basic_info.alpha_bits != 0)
              image->matte=MagickTrue;

            image->orientation=convert_orientation(basic_info.orientation);

            format.endianness=JXL_NATIVE_ENDIAN;
            format.align=0;
            if (basic_info.num_color_channels == 1)
              {
                if ((basic_info.bits_per_sample <= 8) && (!image->matte))
                  {
                    unsigned long
                      max_value_given_bits;

                    max_value_given_bits=MaxValueGivenBits(basic_info.bits_per_sample);
                    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                          "max_value_given_bits=%lu",max_value_given_bits);

                    if (!AllocateImageColormap(image,max_value_given_bits+1))
                      ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);
                  }
                grayscale=MagickTrue;
                format.num_channels=1;
                format.data_type=(basic_info.bits_per_sample <= 8 ? JXL_TYPE_UINT8 :
                                  (basic_info.bits_per_sample <= 16 ? JXL_TYPE_UINT16 :
                                   JXL_TYPE_FLOAT));
              }
            else if (basic_info.num_color_channels == 3)
              {
                format.num_channels=image->matte ? 4 : 3;
                format.data_type=(basic_info.bits_per_sample <= 8 ? JXL_TYPE_UINT8 :
                                  (basic_info.bits_per_sample <= 16 ? JXL_TYPE_UINT16 :
                                   JXL_TYPE_FLOAT));
              }
            else
              {
                ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);
              }
            break;
          }

        case JXL_DEC_COLOR_ENCODING:
          {
            /* check the colorspace that will be used for output buffer
             *
             * The JXL API does return the pixels in their original colorspace
             * which has a large number of possibilities with profiles etc.
             *
             * We need to try to convert this to the internel SRGB Colorspace
             * as best as possibly. Better to read a image somewhat bogus then
             * to error out.
             *
             * Handling is inspired by the JXL lib example for the GIMP-Plugin.
             */
            JxlColorEncoding
              color_encoding;

            status=JxlDecoderGetColorAsEncodedProfile(jxl,&format,
                                                      JXL_COLOR_PROFILE_TARGET_DATA,&color_encoding);
            if (status == JXL_DEC_ERROR)
              {
                status=JXL_DEC_SUCCESS;
                if (image->logging)
                  {
                    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                          "[%s] failed to get ColorEncoding assuming SRGB",
                                          image->filename);
                  }
              }
            else if (status == JXL_DEC_SUCCESS)
              {
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "Color Transfer Function: %s",
                                      JxlTransferFunctionAsString(color_encoding.transfer_function));
                switch (color_encoding.transfer_function) {
                case JXL_TRANSFER_FUNCTION_LINEAR:
                  isLinear=MagickTrue;
                  break;
                case JXL_TRANSFER_FUNCTION_709:
                  isLinear=MagickFalse;
                  break;
                case JXL_TRANSFER_FUNCTION_PQ:
                  isLinear=MagickFalse;
                  break;
                case JXL_TRANSFER_FUNCTION_HLG:
                  isLinear=MagickFalse;
                  break;
                case JXL_TRANSFER_FUNCTION_GAMMA:
                  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                        "Gamma: %g", color_encoding.gamma);
                  isLinear=MagickFalse;
                  break;
                case JXL_TRANSFER_FUNCTION_DCI:
                  isLinear=MagickFalse;
                  break;
                case JXL_TRANSFER_FUNCTION_SRGB:
                  isLinear=MagickFalse;
                  break;

                case JXL_TRANSFER_FUNCTION_UNKNOWN:
                default:
                  ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);
                }

                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "Color Space: %s",
                                      JxlColorSpaceAsString(color_encoding.color_space));

                switch (color_encoding.color_space) {
                case JXL_COLOR_SPACE_RGB:
                  if (color_encoding.white_point == JXL_WHITE_POINT_D65 &&
                      color_encoding.primaries == JXL_PRIMARIES_SRGB)
                    {
                      /* ok */
                    }
                  else if(!isLinear &&
                          color_encoding.white_point == JXL_WHITE_POINT_D65 &&
                          (color_encoding.primaries_green_xy[0] == 0.2100 ||
                           color_encoding.primaries_green_xy[1] == 0.7100))
                    {
                      /* Probably Adobe RGB */
                      ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);
                    }
                  else if (image->logging)
                    {
                      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                            "[%s] Unknown colorspace assume SRGB",
                                            image->filename);
                    }
                  break;
                case JXL_COLOR_SPACE_GRAY:
                  if (!grayscale)
                    ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);
                  break;
                case JXL_COLOR_SPACE_XYB:
                case JXL_COLOR_SPACE_UNKNOWN:
                default:
                  if (image->logging)
                    {
                      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                            "[%s] Unsupported/Unknown colorspace treat as SRGB",
                                            image->filename);
                    }
                  break;
                }
              }
            /*TODO: get ICC-profile and keep as metadata?*/
            break;
          }
        case JXL_DEC_NEED_IMAGE_OUT_BUFFER:
          { /* allocate output buffer */
            size_t
              out_len;

            status=JxlDecoderImageOutBufferSize(jxl,&format,&out_len);
            if (status != JXL_DEC_SUCCESS)
              break;

            out_buf=MagickAllocateResourceLimitedArray(unsigned char *,out_len,sizeof(*out_buf));
            if (out_buf == (unsigned char *) NULL)
              ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

            status=JxlDecoderSetImageOutBuffer(jxl,&format,out_buf,out_len);
            break;
          }
        case JXL_DEC_FULL_IMAGE:
          { /* got image */
            long
              x,
              y;

            PixelPacket
              *q;

            unsigned char
              *p;

            ImportPixelAreaOptions
              import_options;

            ImportPixelAreaInfo
              import_area_info;

            unsigned int
              quantum_size;

            QuantumType
              quantum_type;

            QuantumSampleType
              sample_type = UndefinedQuantumSampleType;

            MagickPassFail
              res=MagickPass;

            assert(out_buf != (unsigned char *)NULL);

            quantum_size = 0;
              switch (format.data_type)
                {
                case JXL_TYPE_FLOAT:
                  quantum_size = 32;
                  sample_type = FloatQuantumSampleType;
                  break;
                case JXL_TYPE_UINT8:
                  quantum_size = 8;
                  sample_type = UnsignedQuantumSampleType;
                  break;
                case JXL_TYPE_UINT16:
                  quantum_size = 16;
                  sample_type = UnsignedQuantumSampleType;
                  break;
                case JXL_TYPE_FLOAT16:
                  quantum_size = 16;
                  sample_type = FloatQuantumSampleType;
                  break;
                }

            if (grayscale)
              {
                if (image->matte)
                  quantum_type = GrayAlphaQuantum;
                else
                  quantum_type = GrayQuantum;
              }
            #if 0
            else if (cmyk)
              {
                if (image->matte)
                  quantum_type = CMYKAQuantum;
                else
                  quantum_type = CMYKQuantum;
              }
            #endif
            else
              {
                if (image->matte)
                  quantum_type = RGBAQuantum;
                else
                  quantum_type = RGBQuantum;
              }

            ImportPixelAreaOptionsInit(&import_options);
            import_options.sample_type = sample_type;
            import_options.endian = NativeEndian;

            p = out_buf;
            for (y=0; y < (long) image->rows; y++)
              {
                q=SetImagePixelsEx(image,0,y,image->columns,1,exception);
                if (q == (PixelPacket *) NULL)
                  {
                    res = MagickFail;
                    break;
                  }

                if ((res = ImportImagePixelArea(image,quantum_type,quantum_size,
                                                p,
                                                &import_options,&import_area_info))
                    != MagickPass)
                  break;
                // Promote linear image to sRGB (2.4 gamma).
                // We could also set image->gamma and return the original image.
#if 1
                if (isLinear)
                  {
                    for (x = 0 ; x < (long) image->columns ; x++)
                      {
                        linear2nonlinear_quantum(&q[x].red);
                        if (grayscale)
                          {
                            q[x].green = q[x].blue = q[x].red;
                          }
                        else
                          {
                            linear2nonlinear_quantum(&q[x].green);
                            linear2nonlinear_quantum(&q[x].blue);
                          }
                      }
                  }
#endif
                p += import_area_info.bytes_imported;

                if (!SyncImagePixels(image))
                  {
                    res = MagickFail;
                    break;
                  }
              }

            if (!res)
              status=JXL_DEC_ERROR;
            break;
          }
        default:
          /* unexpected status is error.
           * - JXL_DEC_SUCCESS should never happen here so it's also an error
           */
          status=JXL_DEC_ERROR;
          break;
        }
      if (status == JXL_DEC_ERROR)
        break;
      status = JxlDecoderProcessInput(jxl);
    }
  /* every break outside of success is some kind of error */
  if (status != JXL_DEC_SUCCESS) {
    /* no details available */
    ThrowJXLReaderException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
  }

  JXLReadCleanup();
  CloseBlob(image);
  return image;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e J X L I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WriteJXLImage() writes an image in the JXL image format.
%
%  The format of the WriteJXLImage method is:
%
%      MagickPassFail WriteJXLImage(const ImageInfo *image_info, Image *image)
%
%  A description of each parameter follows.
%
%    o image_info: the image info.
%
%    o image:  The image.
%
*/

#define JXLWriteCleanup() \
  if (jxl_thread_runner) JxlThreadParallelRunnerDestroy(jxl_thread_runner); \
  if (jxl_encoder) JxlEncoderDestroy(jxl_encoder); \
  MagickFreeResourceLimitedMemory(in_buf); \
  MagickFreeResourceLimitedMemory(out_buf); \

#define ThrowJXLWriterException(code_,reason_,image_) \
do { \
  JXLWriteCleanup();                          \
  ThrowWriterException(code_,reason_,image_); \
 } while(1)

static StorageType JxlDataTypeToDispatchStorageType(const JxlDataType data_type)
{
  StorageType storage_type = 0;

  switch (data_type)
    {
    case JXL_TYPE_FLOAT:
      storage_type = FloatPixel;
      break;
    case JXL_TYPE_UINT8:
      storage_type = CharPixel;
      break;
    case JXL_TYPE_UINT16:
      storage_type = ShortPixel;
      break;
    case JXL_TYPE_FLOAT16:
      storage_type = ShortPixel; /* FIXME: Not actually supported yet */
      break;
    }

  return storage_type;
}

static unsigned int WriteJXLImage(const ImageInfo *image_info,Image *image)
{
  MagickPassFail
    status;

  JxlEncoder
    *jxl_encoder = NULL;

  void
    *jxl_thread_runner = NULL;

  JxlEncoderFrameSettings
    *frame_settings = NULL; /* Deallocated when encoder is destroyed with JxlEncoderDestroy() */

  JxlEncoderStatus
    jxl_status;

  JxlBasicInfo
    basic_info;

  struct MyJXLMemoryManager
    memory_manager;

  ImageCharacteristics
    characteristics;

  size_t
    size_row;

  unsigned char
    *in_buf = NULL,
    *out_buf = NULL;

  JxlPixelFormat
    pixel_format;

  JxlColorEncoding
    color_encoding = {};

  memset(&pixel_format,0,sizeof(pixel_format));

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);

  /*
    Ensure that image is in desired output space
  */
  if ((image_info->type != UndefinedType) &&
      (image_info->type != OptimizeType))
    (void) SetImageType(image,image_info->type);
  else if (!IsCMYKColorspace(image->colorspace) &&
           (!IsRGBColorspace(image->colorspace)))
    (void) TransformColorspace(image,RGBColorspace);

  /*
    Analyze image to be written.
  */
  if (!GetImageCharacteristics(image,&characteristics,
                               (OptimizeType == image_info->type),
                               &image->exception))
    {
      return MagickFail;
    }

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Image characteristics: cmyk=%c, gray=%c, mono=%c,"
                        " opaque=%c, palette=%c",
                        (characteristics.cmyk ? 'y' : 'n'),
                        (characteristics.grayscale ? 'y' : 'n'),
                        (characteristics.monochrome ? 'y' : 'n'),
                        (characteristics.opaque ? 'y' : 'n'),
                        (characteristics.palette ? 'y' : 'n'));

  /*
    Open output image file.
  */
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == MagickFail)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);

  /* Init JXL-Decoder handles */
  MyJxlMemoryManagerInit(&memory_manager,image,&image->exception);
  jxl_encoder=JxlEncoderCreate(&memory_manager.super);
  if (jxl_encoder == (JxlEncoder *) NULL)
    ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  jxl_thread_runner=
    JxlThreadParallelRunnerCreate(NULL,
                                  (size_t) GetMagickResourceLimit(ThreadsResource));
  if (jxl_thread_runner == (void *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);
  if (JxlEncoderSetParallelRunner(jxl_encoder, JxlThreadParallelRunner, jxl_thread_runner)
      != JXL_ENC_SUCCESS)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  /* Use one color channel for grayscale image */
  if (characteristics.grayscale)
    pixel_format.num_channels = 1;
  else
    {
      image->storage_class=DirectClass;
      pixel_format.num_channels = characteristics.opaque ? 3 : 4;
    }

  /* Support writing integer depths 8 and 16 */
  if (image->depth <= 8)
    pixel_format.data_type = JXL_TYPE_UINT8;
  else if (image->depth <= 16)
    pixel_format.data_type = JXL_TYPE_UINT16;
  else if (image->depth <= 32)
    pixel_format.data_type = JXL_TYPE_FLOAT; /* or JXL_TYPE_FLOAT JXL_TYPE_UINT16 */
  else
    ThrowJXLWriterException(CoderError,ColorspaceModelIsNotSupported,image);

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Using JXL '%s' data type", JxlDataTypeAsString(pixel_format.data_type));

  /* Initialize JxlBasicInfo struct to default values. */
  JxlEncoderInitBasicInfo(&basic_info);
  /* Width of the image in pixels, before applying orientation. */
  basic_info.xsize = image->columns;
  /* Height of the image in pixels, before applying orientation. */
  basic_info.ysize = image->rows;

  /* JXL_TYPE_FLOAT requires a nominal range of 0 to 1 */

  switch (pixel_format.data_type)
    {
    case JXL_TYPE_FLOAT:
      basic_info.bits_per_sample = 32;
      break;
    case JXL_TYPE_UINT8:
      basic_info.bits_per_sample = 8;
      break;
    case JXL_TYPE_UINT16:
      basic_info.bits_per_sample = 16;
      break;
    case JXL_TYPE_FLOAT16:
      basic_info.bits_per_sample = 16;
      break;
    default:
      ThrowJXLWriterException(CoderError,DataStorageTypeIsNotSupported,image);
    }


  pixel_format.endianness = JXL_NATIVE_ENDIAN;
  pixel_format.align = 0;

  if (pixel_format.data_type == JXL_TYPE_FLOAT)
    basic_info.exponent_bits_per_sample = 8;

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Using %u bits per sample", basic_info.bits_per_sample);

  basic_info.num_color_channels = characteristics.grayscale ? 1 : 3;
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Using %u channel%s", basic_info.num_color_channels,
                        basic_info.num_color_channels > 1 ? "s" : "");

  if (!characteristics.opaque)
    basic_info.alpha_bits=basic_info.bits_per_sample;

  /* Set the global metadata of the image encoded by this encoder. */
  if ((jxl_status = JxlEncoderSetBasicInfo(jxl_encoder,&basic_info)) != JXL_ENC_SUCCESS)
    {
      /* TODO better error codes */
      if (jxl_status == JXL_ENC_ERROR)
        ThrowJXLWriterException(CoderError,NoDataReturned,image);
      else if (jxl_status == JXL_ENC_NOT_SUPPORTED)
        ThrowJXLWriterException(CoderError,UnsupportedBitsPerSample,image);
      else
        ThrowJXLWriterException(CoderFatalError,Default,image);
    }

  /* Set expected input colorspace */
  /* FIXME: For RGB we want to set JXL_COLOR_SPACE_RGB and for gray we want JXL_COLOR_SPACE_GRAY */
  basic_info.uses_original_profile = JXL_TRUE;
  JxlColorEncodingSetToSRGB(&color_encoding, pixel_format.num_channels < 3);
  if (JxlEncoderSetColorEncoding(jxl_encoder, &color_encoding) != JXL_ENC_SUCCESS)
    ThrowJXLWriterException(CoderFatalError,Default,image);

  frame_settings = JxlEncoderFrameSettingsCreate(jxl_encoder, NULL);
  if (image_info->quality == 100)
    {
      if (JxlEncoderSetFrameLossless(frame_settings,JXL_TRUE) != JXL_ENC_SUCCESS)
        ThrowJXLWriterException(CoderFatalError,Default,image);
    }
  else
    {
      /* same as cjxl.c: roughly similar to jpeg-quality for range 1-99 */
      if (image_info->quality >= 30)
        {
          if (JxlEncoderSetFrameDistance(frame_settings,
                                         0.1 + (100 - image_info->quality) * 0.09) != JXL_ENC_SUCCESS)
            ThrowJXLWriterException(CoderFatalError,Default,image);
        }
      else
        {
          if (JxlEncoderSetFrameDistance(frame_settings,
                                         6.4 + pow(2.5, (30 - image_info->quality) / 5.0f) / 6.25f) != JXL_ENC_SUCCESS)
            ThrowJXLWriterException(CoderFatalError,Default,image);
        }
    }
  /*
    Handle key/value for settings handled by JxlEncoderFrameSettingsSetOption()
  */
  {
    static const struct
    {
      const char key[14];
      JxlEncoderFrameSettingId fs_id;
    } int_frame_settings[]
        =
        {
         { "effort", JXL_ENC_FRAME_SETTING_EFFORT },
         { "decodingspeed", JXL_ENC_FRAME_SETTING_DECODING_SPEED },
        };

    unsigned int
      index;

    for (index = 0; index < ArraySize(int_frame_settings); index++)
      {
        const char *key = int_frame_settings[index].key;
        const char *value;
        if ((value=AccessDefinition(image_info,"jxl",key)))
          {
            int int_value =  MagickAtoI(value);
            if (JxlEncoderFrameSettingsSetOption(frame_settings, int_frame_settings[index].fs_id, int_value) != JXL_ENC_SUCCESS)
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "JXL does not support \"%s\" frame setting!", key);
            else
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Set \"%s\" to %d", key, int_value);
          }
      }
  }

  /* get & fill pixel buffer */
  size_row=MagickArraySize(MagickArraySize(image->columns,pixel_format.num_channels),(basic_info.bits_per_sample/8));
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "size_row = %zu", size_row);
  in_buf=MagickAllocateResourceLimitedArray(unsigned char *,image->rows,size_row);
  if (in_buf == (unsigned char *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "DispatchImage(0,0,%lu,%lu, %s)",
                        image->columns,image->rows,
                        characteristics.grayscale ? "I" : (characteristics.opaque ? "RGB" : "RGBA"));

  status=DispatchImage(image,0,0,image->columns,image->rows,
                       characteristics.grayscale ? "I" : (image->matte ? "RGBA" : "RGB"),
                       JxlDataTypeToDispatchStorageType(pixel_format.data_type),
                       in_buf,&image->exception);
  if (status == MagickFail)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  /* real encode */
  if (JxlEncoderAddImageFrame(frame_settings,&pixel_format,in_buf,
                              image->rows * size_row) != JXL_ENC_SUCCESS)
    /* TODO Better Error-code? */
    ThrowJXLWriterException(CoderError,NoDataReturned,image);

  /* Close any input to the encoder. No further input of any kind may
     be given to the encoder, but further JxlEncoderProcessOutput
     calls should be done to create the final output. */
  JxlEncoderCloseInput(jxl_encoder);

  out_buf=MagickAllocateResourceLimitedArray(unsigned char *,MaxBufferExtent,sizeof(*out_buf));
  if (out_buf == (unsigned char *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  jxl_status=JXL_ENC_NEED_MORE_OUTPUT;
  while (jxl_status == JXL_ENC_NEED_MORE_OUTPUT)
    {
      size_t
        avail_out,
        write_out;

      unsigned char
        *next_out;

      avail_out=MaxBufferExtent;
      next_out=out_buf;
      /* fprintf(stderr,"Before: next_out=%p, avail_out=%zu\n", next_out, avail_out); */
      jxl_status=JxlEncoderProcessOutput(jxl_encoder,&next_out,&avail_out);
      write_out=next_out-out_buf;
      /* fprintf(stderr,"After: next_out=%p, avail_out=%zu, write_out=%zu\n", next_out, avail_out, write_out); */

      if (WriteBlob(image,write_out,out_buf) != write_out)
        ThrowJXLWriterException(BlobError,UnableToWriteBlob,image);
    }
  if (jxl_status != JXL_ENC_SUCCESS)
    /* TODO Better Error-code? */
    ThrowJXLWriterException(CoderError,NoDataReturned,image);

  CloseBlob(image);

  JXLWriteCleanup();
  return MagickPass;
}

#endif /* HasJXL */


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r J X L I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterJXLImage adds attributes for the JXL image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format and a brief
%  description of the format.
%
%  The format of the RegisterJXLImage method is:
%
%      RegisterJXLImage(void)
%
*/
ModuleExport void RegisterJXLImage(void)
{
#if defined(HasJXL)
  static const char
    description[] = "JXL Image Format";

  static char
    version[20];

  MagickInfo
    *entry;

  unsigned int
    jxl_major,
    jxl_minor,
    jxl_revision;

  int encoder_version=(JxlDecoderVersion());
  jxl_major=(encoder_version >> 16) & 0xff;
  jxl_minor=(encoder_version >> 8) & 0xff;
  jxl_revision=encoder_version & 0xff;
  *version='\0';
  (void) snprintf(version,sizeof(version),
                  "jxl v%u.%u.%u", jxl_major,
                  jxl_minor, jxl_revision);

  entry=SetMagickInfo("JXL");
  entry->decoder=(DecoderHandler) ReadJXLImage;
  entry->encoder=(EncoderHandler) WriteJXLImage;
  entry->description=description;
  entry->adjoin=False;
  entry->seekable_stream=MagickTrue;
  if (*version != '\0')
    entry->version=version;
  entry->module="JXL";
  entry->coder_class=PrimaryCoderClass;
  (void) RegisterMagickInfo(entry);
#endif /* HasJXL */
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r J X L I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterJXLImage removes format registrations made by the
%  JXL module from the list of supported formats.
%
%  The format of the UnregisterJXLImage method is:
%
%      UnregisterJXLImage(void)
%
*/
ModuleExport void UnregisterJXLImage(void)
{
#if defined(HasJXL)
  (void) UnregisterMagickInfo("JXL");
#endif /* HasJXL */
}
