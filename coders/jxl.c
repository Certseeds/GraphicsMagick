/*
% Copyright (C) 2023 GraphicsMagick Group
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
* Libjxl requires the full uncompressed image in memory in order to compress,
* so it requires a lot of memory when writing.
*
* Features which work:
*
*   * Gray and RGB images
*   * 8, and 16 bit integer samples
*   * 16 and 32-bit float samples
*   * Store/Read ICC, EXIF, and XMP profiles
*   * Resource-limited memory allocator
*
* Features still to be completed:
*
*   * Multiple frames / animations
*   * Premultiplied alpha
*   * Alpha bits != RGB sample bits
*   * CMYK layers
*   * Progressive images
*   * Progress monitor
*   * Linear images (needs improvement)
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

#define MaxBufferExtent 65536

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

static QuantumSampleType JxlDataTypeToQuantumSampleType(const JxlDataType data_type)
{
  QuantumSampleType
    sample_type = UndefinedQuantumSampleType;

  switch (data_type)
    {
    case JXL_TYPE_FLOAT:
      sample_type = FloatQuantumSampleType;
      break;
    case JXL_TYPE_UINT8:
      sample_type = UnsignedQuantumSampleType;
      break;
    case JXL_TYPE_UINT16:
      sample_type = UnsignedQuantumSampleType;
      break;
    case JXL_TYPE_FLOAT16:
      sample_type = FloatQuantumSampleType;
      break;
    }
  return sample_type;
}

static unsigned int JxlDataTypeToQuantumSize(const JxlDataType data_type)
{
  unsigned int
    quantum_size = 0;

  switch (data_type)
    {
    case JXL_TYPE_FLOAT:
      quantum_size = 32;
      break;
    case JXL_TYPE_UINT8:
      quantum_size = 8;
      break;
    case JXL_TYPE_UINT16:
      quantum_size = 16;
      break;
    case JXL_TYPE_FLOAT16:
      quantum_size = 16;
      break;
    }
  return quantum_size;
}

static const char *JxlExtraChannelTypeAsString(const JxlExtraChannelType extra_channel_type)
{
  const char *str = "Unknown";

  /* Defined in jxl/codestream_header.h */
  switch (extra_channel_type)
    {
    case JXL_CHANNEL_ALPHA:
      str = "Alpha";
      break;
    case JXL_CHANNEL_DEPTH:
      str = "Depth";
      break;
    case JXL_CHANNEL_SPOT_COLOR:
      str = "SpotColor";
      break;
    case JXL_CHANNEL_SELECTION_MASK:
      str = "SelectionMask";
      break;
    case JXL_CHANNEL_BLACK:
      str = "Black";
      break;
    case JXL_CHANNEL_CFA:
      str = "CFA";
      break;
    case JXL_CHANNEL_THERMAL:
      str = "Thermal";
      break;
    case JXL_CHANNEL_RESERVED0:
      str = "RESERVED0";
      break;
    case JXL_CHANNEL_RESERVED1:
      str = "RESERVED1";
      break;
    case JXL_CHANNEL_RESERVED2:
      str = "RESERVED2";
      break;
    case JXL_CHANNEL_RESERVED3:
      str = "RESERVED3";
      break;
    case JXL_CHANNEL_RESERVED4:
      str = "RESERVED4";
      break;
    case JXL_CHANNEL_RESERVED5:
      str = "RESERVED5";
      break;
    case JXL_CHANNEL_RESERVED6:
      str = "RESERVED6";
      break;
    case JXL_CHANNEL_RESERVED7:
      str = "RESERVED7";
      break;
    case JXL_CHANNEL_UNKNOWN:
      str = "Unknown";
      break;
    case JXL_CHANNEL_OPTIONAL:
      str = "Optional";
      break;
    }

  return str;
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


#define JXLReadCleanup()                                \
  MagickFreeResourceLimitedMemory(out_buf);             \
  MagickFreeResourceLimitedMemory(in_buf);              \
  MagickFreeResourceLimitedMemory(exif_profile);        \
  MagickFreeResourceLimitedMemory(xmp_profile);         \
  if (jxl_thread_runner)                                \
    JxlThreadParallelRunnerDestroy(jxl_thread_runner);  \
  if (jxl_decoder)                                      \
    JxlDecoderDestroy(jxl_decoder);


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
    *jxl_decoder = NULL;

  void
    *jxl_thread_runner = NULL;

  JxlDecoderStatus
    status;

  JxlPixelFormat
    pixel_format;

  JxlExtraChannelInfo
    extra_channel_info[5];

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

  unsigned char
    *exif_profile = NULL,
    *xmp_profile = NULL;

  size_t
    exif_size = 0,
    exif_pad = 2,
    xmp_size = 0;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);

  memset(&pixel_format,0,sizeof(pixel_format));

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
  jxl_decoder=JxlDecoderCreate(&mm.super);
  if (jxl_decoder == (JxlDecoder *) NULL)
    ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  /* Deliver image as-is. We provide autoOrient function if user requires it */
  if (JxlDecoderSetKeepOrientation(jxl_decoder, JXL_TRUE) != JXL_DEC_SUCCESS)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  /* Apply any pre-multiplied alpha for us so we don't need to do it. */
  (void) JxlDecoderSetUnpremultiplyAlpha(jxl_decoder, JXL_TRUE);

  if(!image_info->ping)
    {
      jxl_thread_runner=JxlThreadParallelRunnerCreate(NULL,(size_t) GetMagickResourceLimit(ThreadsResource));
      if (jxl_thread_runner == (void *) NULL)
        ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);
      if (JxlDecoderSetParallelRunner(jxl_decoder, JxlThreadParallelRunner, jxl_thread_runner)
          != JXL_DEC_SUCCESS)
        ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    }

  if (JxlDecoderSubscribeEvents(jxl_decoder,
                                (JxlDecoderStatus)(image_info->ping == MagickTrue
                                                   ? (JXL_DEC_BASIC_INFO |
                                                      JXL_DEC_BOX)
                                                   : (JXL_DEC_BASIC_INFO |
                                                      JXL_DEC_FULL_IMAGE |
                                                      JXL_DEC_COLOR_ENCODING |
                                                      JXL_DEC_BOX))
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
              remaining = JxlDecoderReleaseInput(jxl_decoder),
              count;

            if (remaining > 0)
              memmove(in_buf,in_buf+in_len-remaining,remaining);
            count=ReadBlob(image,in_len-remaining,in_buf+remaining);
            if (count == 0)
              ThrowJXLReaderException(CorruptImageError, UnexpectedEndOfFile, image);
            status = JxlDecoderSetInput(jxl_decoder,(const uint8_t *) in_buf, (size_t) count);
            if (blob_len > 0)
              {
                /* If file size is known pass the info about the last block,
                   to the decoder. Note that the call is currently optional */
                blob_len -= count;
                if (blob_len == 0)
                  JxlDecoderCloseInput(jxl_decoder);
              }
            break;
          }
        case JXL_DEC_BASIC_INFO:
          { /* got image information */
            JxlBasicInfo
              basic_info;

            JxlEncoderInitBasicInfo(&basic_info);

            status=JxlDecoderGetBasicInfo(jxl_decoder,&basic_info);
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
                                      "    num_color_channels=%u\n"
                                      "    have_animation=%s",
                                      basic_info.xsize, basic_info.ysize,
                                      basic_info.bits_per_sample, basic_info.exponent_bits_per_sample,
                                      basic_info.alpha_bits, basic_info.num_color_channels,
                                      basic_info.have_animation == JXL_FALSE ? "False" : "True");
              }
            if (basic_info.num_extra_channels)
              {
                size_t index;
                (void) memset(extra_channel_info,0,sizeof(extra_channel_info));
                for (index = 0 ;index < Min(basic_info.num_extra_channels,
                                            ArraySize(extra_channel_info));
                     index++)
                  {
                    JxlExtraChannelInfo* ecip=&extra_channel_info[index];
                    status=JxlDecoderGetExtraChannelInfo(jxl_decoder,
                                                         index,
                                                         ecip);
                    if (JXL_DEC_SUCCESS == status)
                      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                            "Extra Channel Info[%lu]:\n"
                                            "    type=%s\n"
                                            "    bits_per_sample=%u\n"
                                            "    exponent_bits_per_sample=%u\n"
                                            "    dim_shift=%u\n"
                                            "    name_length=%u\n"
                                            "    alpha_premultiplied=%s\n"
                                            "    spot_color=%f,%f,%f,%f\n"
                                            "    cfa_channel=%u"
                                          ,
                                            (unsigned long) index,
                                            JxlExtraChannelTypeAsString(ecip->type),
                                            ecip->bits_per_sample,
                                            ecip->exponent_bits_per_sample,
                                            ecip->dim_shift,
                                            ecip->name_length,
                                            ecip->alpha_premultiplied == JXL_FALSE ? "False" : "True",
                                            ecip->spot_color[0],ecip->spot_color[1],
                                            ecip->spot_color[2],ecip->spot_color[3],
                                            ecip->cfa_channel);
                  }
              }

            if (basic_info.have_animation == 1)
              ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);

            image->columns=basic_info.xsize;
            image->rows=basic_info.ysize;
            image->depth=basic_info.bits_per_sample;
            if (basic_info.alpha_bits != 0)
              image->matte=MagickTrue;

            image->orientation=convert_orientation(basic_info.orientation);

            pixel_format.endianness=JXL_NATIVE_ENDIAN;
            pixel_format.align=0;
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
                pixel_format.num_channels=1;
                pixel_format.data_type=(basic_info.bits_per_sample <= 8 ? JXL_TYPE_UINT8 :
                                  (basic_info.bits_per_sample <= 16 ? JXL_TYPE_UINT16 :
                                   JXL_TYPE_FLOAT));
              }
            else if (basic_info.num_color_channels == 3)
              {
                pixel_format.num_channels=image->matte ? 4 : 3;
                pixel_format.data_type=(basic_info.bits_per_sample <= 8 ? JXL_TYPE_UINT8 :
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

            status=JxlDecoderGetColorAsEncodedProfile(jxl_decoder,
#if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0)
                                                      &pixel_format,
#endif /* if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0) */
                                                      JXL_COLOR_PROFILE_TARGET_DATA,
                                                      &color_encoding);
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
                /*
                  Transfer function if have_gamma is 0
                 */
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

                /*
                  Color space of the image data.
                 */
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
            /*
              Get original ICC-profile and store as metadata
            */
            {
              size_t
                profile_size;

              if (JxlDecoderGetICCProfileSize(jxl_decoder,
#if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0)
                                              &pixel_format,
#endif /* if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0) */
                                              JXL_COLOR_PROFILE_TARGET_ORIGINAL,
                                              &profile_size)
                  == JXL_DEC_SUCCESS)
                {
                  unsigned char
                    *profile;

                  if ((profile=MagickAllocateResourceLimitedMemory(unsigned char *,profile_size))
                      != NULL)
                    {
                      if (JxlDecoderGetColorAsICCProfile(jxl_decoder,
#if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0)
                                                         &pixel_format,
#endif /* if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0) */
                                                         JXL_COLOR_PROFILE_TARGET_ORIGINAL,
                                                         profile,
                                                         profile_size)
                          == JXL_DEC_SUCCESS)
                        {
                          (void) SetImageProfile(image,"ICM",profile,profile_size);
                        }
                      MagickFreeResourceLimitedMemory(profile);
                    }
                }
            }
            break;
          }
        case JXL_DEC_NEED_IMAGE_OUT_BUFFER:
          { /* allocate output buffer */
            size_t
              out_len;

            status=JxlDecoderImageOutBufferSize(jxl_decoder,&pixel_format,&out_len);
            if (status != JXL_DEC_SUCCESS)
              break;

            out_buf=MagickAllocateResourceLimitedArray(unsigned char *,out_len,sizeof(*out_buf));
            if (out_buf == (unsigned char *) NULL)
              ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

            status=JxlDecoderSetImageOutBuffer(jxl_decoder,&pixel_format,out_buf,out_len);
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
              sample_type;

            MagickPassFail
              res=MagickPass;

            assert(out_buf != (unsigned char *)NULL);

            quantum_size = JxlDataTypeToQuantumSize(pixel_format.data_type);
            sample_type = JxlDataTypeToQuantumSampleType(pixel_format.data_type);

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
          case JXL_DEC_BOX:
            {
              do
                {
                  JxlBoxType
                    type; /* A 4 character string which is not null terminated! */

                  magick_uint64_t
                    profile_size = 0;

                  unsigned char
                    *profile;

                  /* Release buffer to get box data */
                  (void) JxlDecoderReleaseBoxBuffer(jxl_decoder);

                  /* Get the 4-character box typename */
                  if (JxlDecoderGetBoxType(jxl_decoder,type,JXL_FALSE) != JXL_DEC_SUCCESS)
                    break;

                  /* Get the size of the box as it appears in the container file, not decompressed. */
                  if (JxlDecoderGetBoxSizeRaw(jxl_decoder, &profile_size) != JXL_DEC_SUCCESS)
                    break;

                  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                        "JXL Box of type \"%c%c%c%c\" and %lu bytes",
                                        type[0],type[1],type[2],type[3], (unsigned long) profile_size);

                  /* Ignore tiny profiles */
                  if (profile_size < 12)
                    break;

                  /* Discard raw box size and type bytes */
                  profile_size -= 8;

                  if (LocaleNCompare(type,"Exif",sizeof(type)) == 0)
                    {
                      /*
                        Allocate EXIF profile box buffer (plus a bit more)
                      */
                      if ((profile=MagickAllocateResourceLimitedClearedMemory(unsigned char *,
                                                                              profile_size+exif_pad))
                          != NULL)
                        {
                          if (JxlDecoderSetBoxBuffer(jxl_decoder,profile+exif_pad,profile_size)
                              == JXL_DEC_SUCCESS)
                            {
                              exif_profile=profile;
                              exif_size=profile_size;
                            }
                        }
                    }
                  if (LocaleNCompare(type,"xml ",sizeof(type)) == 0)
                    {
                      /*
                        Allocate XMP profile box buffer
                      */
                      if ((profile=MagickAllocateResourceLimitedMemory(unsigned char *,profile_size))
                          != NULL)
                        {
                          if (JxlDecoderSetBoxBuffer(jxl_decoder,profile,profile_size) == JXL_DEC_SUCCESS)
                            {
                              xmp_profile=profile;
                              xmp_size=profile_size;
                            }
                        }
                    }
                } while(0);
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
      status = JxlDecoderProcessInput(jxl_decoder);
    }
  /* Release buffer to get box data in the buffers which were passed */
  (void) JxlDecoderReleaseBoxBuffer(jxl_decoder);
  if (exif_profile != NULL)
    {
      /*
        Read Exif profile

        The EXIF box starts with a 4-byte offset to
        the TIFF header (and may be 0).

        The EXIF profile blob needs to be prefixed
        with "Exif\0\0" prior to the TIFF header.

        The buffer provided to libjxl is offset to allow adding our
        header.
      */
      unsigned char *p = exif_profile;
      magick_uint32_t exif_profile_offset;

      /* Big-endian offset decoding */
      exif_profile_offset = p[exif_pad+0] << 24 |
                            p[exif_pad+1] << 16 |
                            p[exif_pad+2] << 8 |
                            p[exif_pad+3];

#if 0
      fprintf(stderr,
              "BOX-1: %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\n",
              p[0], p[1],p[2], p[3], p[4], p[5], p[6], p[7],  p[8],  p[9],  p[10],  p[11]);
#endif

      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "EXIF Box: Size %lu, Offset %u",
                            (unsigned long) exif_size, exif_profile_offset);

      /*
        If the TIFF header offset is not zero, then need to
        move the TIFF data forward to the correct offset.
      */
      exif_size -= 4;
      if (exif_profile_offset > 0 && exif_profile_offset < exif_size)
        {
          exif_size -= exif_profile_offset;

          /* Strip any EOI marker if payload starts with a JPEG marker */
          if (exif_size > 2 &&
              (memcmp(p+exif_pad+4,"\xff\xd8",2) == 0 ||
               memcmp(p+exif_pad+4,"\xff\xe1",2) == 0) &&
              memcmp(p+exif_pad+4+exif_size-2,"\xff\xd9",2) == 0)
            exif_size -= 2;

          (void) memmove(p+exif_pad+4,p+exif_pad+4+exif_profile_offset,exif_size);
        }

      p[0]='E';
      p[1]='x';
      p[2]='i';
      p[3]='f';
      p[4]='\0';
      p[5]='\0';

#if 0
      fprintf(stderr,
              "BOX-2: %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\n",
              p[0], p[1],p[2], p[3], p[4], p[5], p[6], p[7],  p[8],  p[9],  p[10],  p[11]);
#endif
      (void) SetImageProfile(image,"EXIF",exif_profile,exif_size+exif_pad+4);

      MagickFreeResourceLimitedMemory(exif_profile);
    }
  if (xmp_profile != NULL)
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "XMP Box: Size %lu", (unsigned long) exif_size);
      (void) SetImageProfile(image,"XMP",xmp_profile,xmp_size);
      MagickFreeResourceLimitedMemory(xmp_profile);
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

  /* Use the same number of threads as used for OpenMP */
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

  /* Support writing integer depths 8, 16, and 32 */
  /* FIXME: Provide an option to write JXL_TYPE_FLOAT16 or really any
     desired type here */
  if (image->depth <= 8)
    pixel_format.data_type = JXL_TYPE_UINT8;
  else if (image->depth <= 16)
    pixel_format.data_type = JXL_TYPE_UINT16; /* or JXL_TYPE_FLOAT16 JXL_TYPE_UINT16  */
  else if (image->depth <= 32)
    pixel_format.data_type = JXL_TYPE_FLOAT; /* or JXL_TYPE_UINT16 */
  else
    ThrowJXLWriterException(CoderError,ColorspaceModelIsNotSupported,image);

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Using JXL '%s' data type",
                        JxlDataTypeAsString(pixel_format.data_type));

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
  else if (pixel_format.data_type == JXL_TYPE_FLOAT16)
    basic_info.exponent_bits_per_sample = 5;

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Using %u bits per sample", basic_info.bits_per_sample);

  basic_info.num_color_channels = characteristics.grayscale ? 1 : 3;
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Using %u color channel%s", basic_info.num_color_channels,
                        basic_info.num_color_channels > 1 ? "s" : "");

  if (!characteristics.opaque)
    basic_info.alpha_bits=basic_info.bits_per_sample;

  /*
    Set the feature level of the JPEG XL codestream. Valid values are 5 and
    10, or -1 (to choose automatically). Using the minimum required level, or
    level 5 in most cases, is recommended for compatibility with all decoders.

    See <jxl/encode.h> for more details.
  */
  if ((jxl_status = JxlEncoderSetCodestreamLevel(jxl_encoder,-1)) != JXL_ENC_SUCCESS)
    {
    };
  if (image->logging)
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Basic Info:\n"
                            "    xsize=%u\n"
                            "    ysize=%u \n"
                            "    bits_per_sample=%u\n"
                            "    exponent_bits_per_sample=%u\n"
                            "    alpha_bits=%u\n"
                            "    num_color_channels=%u\n"
                            "    have_animation=%s",
                            basic_info.xsize, basic_info.ysize,
                            basic_info.bits_per_sample, basic_info.exponent_bits_per_sample,
                            basic_info.alpha_bits, basic_info.num_color_channels,
                            basic_info.have_animation == JXL_FALSE ? "False" : "True");
    }
  /* Set the global metadata of the image encoded by this encoder. */
  if ((jxl_status = JxlEncoderSetBasicInfo(jxl_encoder,&basic_info)) != JXL_ENC_SUCCESS)
    {
      /* TODO better error codes */
      if (jxl_status == JXL_ENC_ERROR)
        ThrowJXLWriterException(CoderError,NoDataReturned,image);
#if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0)
      /* JXL_ENC_NOT_SUPPORTED was removed for 0.9.0, although API docs still mention it. */
      else if (jxl_status == JXL_ENC_NOT_SUPPORTED)
        ThrowJXLWriterException(CoderError,UnsupportedBitsPerSample,image);
#endif /* if JPEGXL_NUMERIC_VERSION < JPEGXL_COMPUTE_NUMERIC_VERSION(0,9,0) */
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

  /* FIXME: Add metadata boxes */
  do
  {
    const unsigned char
      *exif,
      *xmp;

    size_t
      exif_length,
      xmp_length;

    exif=GetImageProfile(image,"EXIF",&exif_length);
    xmp=GetImageProfile(image,"XMP",&xmp_length);

    if (!((exif != (const unsigned char *) NULL) ||
          (xmp != (const unsigned char *) NULL)))
      break;

    (void) JxlEncoderUseBoxes(jxl_encoder);

    #define ExifNamespace  "Exif\0\0"
    if ((exif != (const unsigned char *) NULL) && (exif_length > 6) &&
        (exif[0] == 'E' && exif[1] == 'x' && exif[2] == 'i' &&
         exif[3] == 'f' && exif[4] == '\0' && exif[5] == '\0'))
      {
        /*
          The contents of this box must be prepended by a 4-byte tiff
          header offset, which may be 4 zero bytes in case the tiff
          header follows immediately.  We will make the header follow
          immediately.

          The EXIF profile blob is prefixed with "Exif\0\0" but the
          EXIF box needs to start with "\0\0\0\0" to indicate that the
          TIFF header follows immediately.
        */
        unsigned char *exif_b = MagickAllocateResourceLimitedMemory(unsigned char *,
                                                                    exif_length-2U);
        if (exif_b != (unsigned char *) NULL)
          {
            (void) memset(exif_b,0,4U);
            (void) memcpy(exif_b+4U,exif+6U,exif_length-6U);

            (void) JxlEncoderAddBox(jxl_encoder,"Exif",exif_b,exif_length-2U,0);
            MagickFreeResourceLimitedMemory(exif_b);
          }
      }

    if (xmp != (const unsigned char *) NULL)
      (void) JxlEncoderAddBox(jxl_encoder,"xml ",xmp,xmp_length,0);

    (void) JxlEncoderCloseBoxes(jxl_encoder);

  } while(0);

  /* get & fill pixel buffer */
  size_row=MagickArraySize(MagickArraySize(image->columns,pixel_format.num_channels),
                           (basic_info.bits_per_sample/8));
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "size_row = %" MAGICK_SIZE_T_F "u", (MAGICK_SIZE_T) size_row);
  in_buf=MagickAllocateResourceLimitedArray(unsigned char *,image->rows,size_row);
  if (in_buf == (unsigned char *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  /*
    Export image pixels to allocated buffer.
  */
  {
    long
      y;

    const PixelPacket
      *q;

    unsigned char
      *p;

    unsigned int
      quantum_size;

    QuantumType
      quantum_type;

    QuantumSampleType
      sample_type;

    ExportPixelAreaOptions
      export_options;

    ExportPixelAreaInfo
      export_info;

    quantum_size = JxlDataTypeToQuantumSize(pixel_format.data_type);
    sample_type = JxlDataTypeToQuantumSampleType(pixel_format.data_type);

    if (pixel_format.num_channels == 1)
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

    ExportPixelAreaOptionsInit(&export_options);
    export_options.sample_type = sample_type;
    export_options.endian = NativeEndian;

    p = in_buf;
    for (y=0; y < (long) image->rows; y++)
      {
        q=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
        if (q == (const PixelPacket *) NULL)
          {
            status = MagickFail;
            break;
          }

        if ((status = ExportImagePixelArea(image,quantum_type,quantum_size,
                                           p,&export_options,&export_info))
            != MagickPass)
          break;

        p += export_info.bytes_exported;
      }
    if (status == MagickFail)
      ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);
  }

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
