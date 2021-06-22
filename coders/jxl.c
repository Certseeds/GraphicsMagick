/*
% Copyright (C) 2021 GraphicsMagick Group
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
%                     Read/Write Google JPEG-XL Image Format.                 %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Status: Only support basic images (no animations) with grayscale/SRGB colorspace
* Note that JXL is a C++ library so does require linking with a c++ compiler.
*
* Currently tested vs libjxl-0.3.7 on linux only, likely will have build problems
* on other platforms. Also note the amount of third-party-libs required!
*/

#include "magick/studio.h"
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

#define FOR_PIXEL_PACKETS \
  for (y=0; y < (long)image->rows; y++) \
    { \
      q=SetImagePixelsEx(image,0,y,image->columns,1,exception); \
      if (q == (PixelPacket *) NULL) \
        return MagickFail; \
      for (x=0; x < (long)image->columns; x++)
#define END_FOR_PIXEL_PACKETS \
      if (!SyncImagePixels(image)) \
        return MagickFail; \
    } \

static MagickBool fill_pixels_char(Image *image, ExceptionInfo *exception,
  unsigned char *p)
{
  long
    x,
    y;

  PixelPacket
    *q;

  if (image->matte) {
    FOR_PIXEL_PACKETS
      {
        SetRedSample(q,ScaleCharToQuantum(*p++));
        SetGreenSample(q,ScaleCharToQuantum(*p++));
        SetBlueSample(q,ScaleCharToQuantum(*p++));
        SetOpacitySample(q,MaxRGB-ScaleCharToQuantum(*p++));
	q++;
      }
    END_FOR_PIXEL_PACKETS
  } else {
    FOR_PIXEL_PACKETS
      {
        SetRedSample(q,ScaleCharToQuantum(*p++));
        SetGreenSample(q,ScaleCharToQuantum(*p++));
        SetBlueSample(q,ScaleCharToQuantum(*p++));
        SetOpacitySample(q,OpaqueOpacity);
	q++;
      }
    END_FOR_PIXEL_PACKETS
  }

  return MagickTrue;
}

static MagickBool fill_pixels_char_grayscale(Image *image, ExceptionInfo *exception,
  unsigned char *p)
{
  long
    x,
    y;

  PixelPacket
    *q;

  IndexPacket
    index;

  for (y=0; y < (long)image->rows; y++)
    {
      register IndexPacket
        *indexes;

      q=SetImagePixelsEx(image,0,y,image->columns,1,exception);
      if (q == (PixelPacket *) NULL)
        return MagickFail;

      indexes=AccessMutableIndexes(image);
      if (indexes == NULL)
        return MagickFail;

      for (x=0; x < (long)image->columns; x++) {
        index=(IndexPacket)(*p++);
        VerifyColormapIndex(image,index);
        indexes[x]=index;
        *q++=image->colormap[index];
      }
      if (!SyncImagePixels(image))
        return MagickFail;
    }
  return MagickTrue;
}



/** The JXL API is not quite clear on who they returns JXL_TYPE_FLOAT.
 *  While the encode clearly states that JXL_TYPE_FLOAT is linear SRGB
 *  And JXL_TYPE_UNIT8 is non-linear its not that clear for decode.
 *  However it looks like it's implicit in at least some Situation
 *  that the same rule applys to decode.
 *  Therefore convert all linear values to internal non-linear SRGB
 *  for the Quantums.
 *  Formula from wikipedia:
 *	https://en.wikipedia.org/wiki/SRGB
 */
static float linear2nonlinear(float p)
{
    if(p < 0.0031308) {
	return p * 12.92;
    } else {
	return 1.055 * powf(p, 1.0/2.4) - 0.055;
    }
}

static MagickBool fill_pixels_float(Image *image, ExceptionInfo *exception,
  float *p)
{
  long
    x,
    y;

  PixelPacket
    *q;

  if (image->matte) {
    FOR_PIXEL_PACKETS
      {
        SetRedSample(q,RoundFloatToQuantum(linear2nonlinear(*p++)));
        SetGreenSample(q,RoundFloatToQuantum(linear2nonlinear(*p++)));
        SetBlueSample(q,RoundFloatToQuantum(linear2nonlinear(*p++)));
        SetOpacitySample(q,MaxRGB-RoundFloatToQuantum(linear2nonlinear(*p++)));
	q++;
      }
    END_FOR_PIXEL_PACKETS
  } else {
    FOR_PIXEL_PACKETS
      {
        SetRedSample(q,RoundFloatToQuantum(linear2nonlinear(*p++)));
        SetGreenSample(q,RoundFloatToQuantum(linear2nonlinear(*p++)));
        SetBlueSample(q,RoundFloatToQuantum(linear2nonlinear(*p++)));
        SetOpacitySample(q,OpaqueOpacity);
	q++;
      }
    END_FOR_PIXEL_PACKETS
  }

  return MagickTrue;
}

#define JXLReadCleanup() \
  if(jxl_thread_runner) JxlThreadParallelRunnerDestroy(jxl_thread_runner); \
  if(jxl) JxlDecoderDestroy(jxl); \
  MagickFreeResourceLimitedMemory(in_buf); \
  MagickFreeResourceLimitedMemory(out_buf); \


#define ThrowJXLReaderException(code_,reason_,image_) \
{ \
  JXLReadCleanup() \
  ThrowReaderException(code_,reason_,image_); \
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

  size_t
    in_len = MaxBufferExtent;

  unsigned char
    *in_buf = NULL,
    *out_buf = NULL;

  MagickBool
    grayscale = MagickFalse;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);

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

  jxl_thread_runner=JxlThreadParallelRunnerCreate(NULL,(size_t) GetMagickResourceLimit(
    ThreadsResource));
  if (jxl_thread_runner == (void *) NULL)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);
  if (JxlDecoderSetParallelRunner(jxl, JxlThreadParallelRunner, jxl_thread_runner)
        != JXL_DEC_SUCCESS)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  if (JxlDecoderSubscribeEvents(jxl,
        (JxlDecoderStatus)(image_info->ping == MagickTrue
          ? JXL_DEC_BASIC_INFO
          : JXL_DEC_BASIC_INFO | JXL_DEC_FULL_IMAGE | JXL_DEC_COLOR_ENCODING)
      ) != JXL_DEC_SUCCESS)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);


  in_buf=MagickAllocateResourceLimitedArray(unsigned char *,in_len,sizeof(*in_buf));
  if (in_buf == (unsigned char *) NULL)
    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

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
        break;
      }
      case JXL_DEC_BASIC_INFO:
      { /* got image information */
        JxlBasicInfo
          basic_info;

        status=JxlDecoderGetBasicInfo(jxl,&basic_info);
        if (status != JXL_DEC_SUCCESS)
          break;

        if (basic_info.have_animation == 1)
          ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);

	
        image->columns=basic_info.xsize;
        image->rows=basic_info.ysize;
        image->depth=basic_info.bits_per_sample;
        if (basic_info.alpha_bits != 0)
          image->matte=MagickTrue;

        image->orientation=convert_orientation(basic_info.orientation);

	memset(&format,0,sizeof(format));

        if (basic_info.num_color_channels == 1 && image->depth == 8) {
	  if (!AllocateImageColormap(image,1 << image->depth))
	    ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);
	  grayscale = MagickTrue;
	  format.num_channels=1;
        } else if (basic_info.num_color_channels != 3) {
          ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);
        } else
	  format.num_channels=image->matte ? 4 : 3;

        format.endianness = JXL_NATIVE_ENDIAN;
        format.data_type=(image->depth > 8) ? JXL_TYPE_FLOAT : JXL_TYPE_UINT8;
        break;
      }

      case JXL_DEC_COLOR_ENCODING:
      {
	/* check the colorspace that will be used for output buffer*/
	JxlColorEncoding
	  color_encoding;

	status=JxlDecoderGetColorAsEncodedProfile(jxl,&format,
	    JXL_COLOR_PROFILE_TARGET_DATA,&color_encoding);
	if(status == JXL_DEC_ERROR)
	  /* The lib can't give us an exact color profile so just use the
	     image-pixels more or less plain hoping that the default will match. */
	  status = JXL_DEC_SUCCESS;
	else if (status == JXL_DEC_SUCCESS)
          {
	    if(color_encoding.color_space != JXL_COLOR_SPACE_RGB && color_encoding.color_space != JXL_COLOR_SPACE_GRAY)
	      /* are other values even relevant? */
	      ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);
	    if(color_encoding.transfer_function == JXL_TRANSFER_FUNCTION_LINEAR
		&& format.data_type == JXL_TYPE_FLOAT) {
	      /* expected combination: Linear SRGB, will be converted */
	    } else if(color_encoding.transfer_function == JXL_TRANSFER_FUNCTION_SRGB
		&& format.data_type == JXL_TYPE_UINT8) {
	      /* expected combination: SRGB */
	    } else
	      /* are the other possible values/combinations even relevant? */
	      ThrowJXLReaderException(CoderError, ImageTypeNotSupported, image);
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

        out_buf=MagickAllocateResourceLimitedArray(unsigned char *,out_len,sizeof(*in_buf));
        if (out_buf == (unsigned char *) NULL)
          ThrowJXLReaderException(ResourceLimitError,MemoryAllocationFailed,image);

        status=JxlDecoderSetImageOutBuffer(jxl,&format,out_buf,out_len);
	break;
      }
      case JXL_DEC_FULL_IMAGE:
      { /* got image */
        assert(out_buf != (unsigned char *)NULL);
        if (!grayscale && format.data_type == JXL_TYPE_UINT8) {
          if (fill_pixels_char(image, exception, out_buf) == MagickFail) {
            status = JXL_DEC_ERROR;
          }
        } else if(!grayscale) {
          if (fill_pixels_float(image, exception, (float*)out_buf) == MagickFail) {
            status = JXL_DEC_ERROR;
          }
        } else if(grayscale) {
	  if (fill_pixels_char_grayscale(image, exception, out_buf) == MagickFail) {
            status = JXL_DEC_ERROR;
          }
	}
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
  if(status != JXL_DEC_SUCCESS) {
    /* no details available */
    ThrowReaderException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
  }

  JXLReadCleanup()
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
  if(jxl_thread_runner) JxlThreadParallelRunnerDestroy(jxl_thread_runner); \
  if(jxl) JxlEncoderDestroy(jxl); \
  MagickFreeResourceLimitedMemory(in_buf); \
  MagickFreeResourceLimitedMemory(out_buf); \

#define ThrowJXLWriterException(code_,reason_,image_) \
{ \
  JXLWriteCleanup() \
  ThrowWriterException(code_,reason_,image_); \
}


static unsigned int WriteJXLImage(const ImageInfo *image_info,Image *image)
{
  MagickPassFail
    status;

  JxlEncoder
    *jxl = NULL;

  JxlEncoderOptions
    *encoder_options;

  void
    *jxl_thread_runner = NULL;

  JxlEncoderStatus
    jxl_status;

  struct MyJXLMemoryManager
    mm;

  const char
    *value;

  size_t
    size_row;

  unsigned char
    *in_buf = NULL,
    *out_buf = NULL;

  MagickBool
    grayscale = MagickFalse;

  JxlPixelFormat
    format;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);

  /*
    Open output image file.
  */
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == MagickFail)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);

  /* Init JXL-Decoder handles */
  MyJxlMemoryManagerInit(&mm,image,&image->exception);
  jxl=JxlEncoderCreate(&mm.super);
  if (jxl == (JxlEncoder *) NULL)
    ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  jxl_thread_runner=JxlThreadParallelRunnerCreate(NULL,(size_t) GetMagickResourceLimit(
    ThreadsResource));
  if (jxl_thread_runner == (void *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);
  if (JxlEncoderSetParallelRunner(jxl, JxlThreadParallelRunner, jxl_thread_runner)
        != JXL_ENC_SUCCESS)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  grayscale = IsGrayColorspace(image_info->colorspace);
  if(grayscale)
    format.num_channels = 1;
  else
    {
      (void) TransformColorspace(image,RGBColorspace);
      image->storage_class=DirectClass;
      format.num_channels = image->matte ? 4 : 3;
    }
  if(image->depth <= 8)
    format.data_type = JXL_TYPE_UINT8;
  else if(image->depth <= 16)
    format.data_type = JXL_TYPE_UINT16;
  else
    {
      ThrowJXLWriterException(CoderError,ColorspaceModelIsNotSupported,image);
      // TODO JXL_TYPE_FLOAT requires linear-SRGB colorspace
    }

  JxlBasicInfo
    basic_info;
  memset(&basic_info, 0, sizeof(basic_info));
  basic_info.xsize = image->columns;
  basic_info.ysize = image->rows;
  if(image->depth == 8)
    basic_info.bits_per_sample = 8;
  else
    {
      basic_info.bits_per_sample=32;
      basic_info.exponent_bits_per_sample=8;
    }
  if (image->matte)
    basic_info.alpha_bits=basic_info.bits_per_sample;

  if (JxlEncoderSetBasicInfo(jxl,&basic_info) != JXL_ENC_SUCCESS)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  encoder_options=JxlEncoderOptionsCreate(jxl,(JxlEncoderOptions *) NULL);
  if (encoder_options == (JxlEncoderOptions *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);
  if (image_info->quality == 100)
    JxlEncoderOptionsSetLossless(encoder_options,JXL_TRUE);
  else
    {
      /* same as cjxl.c: roughly similar to jpeg-quality for range 1-99 */
      if(image_info->quality >= 30) {
        JxlEncoderOptionsSetDistance(encoder_options,
	    0.1 + (100 - image_info->quality) * 0.09);
      } else {
	JxlEncoderOptionsSetDistance(encoder_options, 
	    6.4 + pow(2.5, (30 - image_info->quality) / 5.0f) / 6.25f);
      }
    }
  if ((value=AccessDefinition(image_info,"jxl","effort")))
    JxlEncoderOptionsSetEffort(encoder_options, MagickAtoI(value));
  if ((value=AccessDefinition(image_info,"jxl","decodingspeed")))
    JxlEncoderOptionsSetDecodingSpeed(encoder_options, MagickAtoI(value));

  /* get & fill pixel buffer */
  size_row=image->columns * format.num_channels *
    ((format.data_type == JXL_TYPE_FLOAT) ? sizeof(float) : sizeof(char));
  in_buf=MagickAllocateResourceLimitedArray(unsigned char *,image->rows,size_row);
  if (in_buf == (unsigned char *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);
  status=DispatchImage(image,0,0,image->columns,image->rows,
    grayscale ? "I" : (image->matte ? "RGBA" : "RGB"),
    format.data_type ==  JXL_TYPE_UINT8 ? CharPixel : ShortPixel,
    in_buf,&image->exception);
  if (status == MagickFail)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  /* real encode */
  if(JxlEncoderAddImageFrame(encoder_options,&format,in_buf,
    image->rows * size_row) != JXL_ENC_SUCCESS)
    // TODO Better Error-code?
    ThrowJXLWriterException(CoderError,NoDataReturned,image);

  out_buf=MagickAllocateResourceLimitedArray(unsigned char *,MaxBufferExtent,sizeof(*out_buf));
  if (out_buf == (unsigned char *) NULL)
    ThrowJXLWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  jxl_status=JXL_ENC_NEED_MORE_OUTPUT;

  while (jxl_status == JXL_ENC_NEED_MORE_OUTPUT)
    {
      size_t
	count;

      unsigned char
	*p;

      count=MaxBufferExtent;
      p=out_buf;
      jxl_status=JxlEncoderProcessOutput(jxl,&p,&count);
      (void) WriteBlob(image,MaxBufferExtent-count,out_buf);
    }
  if(jxl_status != JXL_ENC_SUCCESS)
    // TODO Better Error-code?
    ThrowJXLWriterException(CoderError,NoDataReturned,image);

  CloseBlob(image);

  JXLWriteCleanup();
  return MagickPass;
}

#endif


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

  *version='\0';

  int encoder_version=(JxlDecoderVersion());
  jxl_major=(encoder_version >> 16) & 0xff;
  jxl_minor=(encoder_version >> 8) & 0xff;
  jxl_revision=encoder_version & 0xff;
  (void) sprintf(version,
                  "jxl v%u.%u.%u", jxl_major,
                  jxl_minor, jxl_revision);

  entry=SetMagickInfo("JXL");
#if defined(HasJXL)
  entry->decoder=(DecoderHandler) ReadJXLImage;
  entry->encoder=(EncoderHandler) WriteJXLImage;
#endif
  entry->description=description;
  entry->adjoin=False;
  entry->seekable_stream=MagickTrue;
  if (*version != '\0')
    entry->version=version;
  entry->module="JXL";
  entry->coder_class=PrimaryCoderClass;
  (void) RegisterMagickInfo(entry);
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
  (void) UnregisterMagickInfo("JXL");
}
