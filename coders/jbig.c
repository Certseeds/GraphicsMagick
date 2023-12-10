/*
% Copyright (C) 2003 - 2023 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
% Copyright 1991-1999 E. I. du Pont de Nemours and Company
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                        JJJJJ  BBBB   IIIII   GGGG                           %
%                          J    B   B    I    G                               %
%                          J    BBBB     I    G  GG                           %
%                        J J    B   B    I    G   G                           %
%                        JJJ    BBBB   IIIII   GGG                            %
%                                                                             %
%                                                                             %
%                       Read/Write JBIG Image Format.                         %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/constitute.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/resource.h"
#include "magick/utility.h"

/*
  Forward declarations.
*/
#if defined(HasJBIG)
static unsigned int
  WriteJBIGImage(const ImageInfo *,Image *);
#endif

#if defined(HasJBIG)
#include "jbig.h"
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d J B I G I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadJBIGImage reads a JBIG image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadJBIGImage method is:
%
%      Image *ReadJBIGImage(const ImageInfo *image_info,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadJBIGImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/
static Image *ReadJBIGImage(const ImageInfo *image_info,
                            ExceptionInfo *exception)
{
#define MaxBufferSize  8192

  Image
    *image;

  int
    status;

  size_t
    length;

  unsigned long
    y;

  register PixelPacket
    *q;

  register unsigned char
    *p;

  size_t
    count;

  struct jbg_dec_state
    jbig_info;

  unsigned char
    *buffer;

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  image=AllocateImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == False)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  /*
    Initialize JBIG toolkit.
  */
  jbg_dec_init(&jbig_info);

  /*
    Attempt to set maximum image dimensions based on resource limits.

    This does work in normal cases, but in other cases the first call
    to jbg_dec_in() takes a very long time, and it returns large image
    dimensions anyway.
  */
  {
    magick_int64_t
      width_limit,
      height_limit,
      pixels_limit;

    width_limit = GetMagickResourceLimit(WidthResource);
    height_limit = GetMagickResourceLimit(HeightResource);
    pixels_limit = GetMagickResourceLimit(PixelsResource);

    if (MagickResourceInfinity != width_limit)
      if ((image->columns == 0) || (image->columns > (unsigned long) width_limit))
        image->columns = (unsigned long) width_limit;

    if (MagickResourceInfinity != height_limit)
      if ((image->rows == 0) || (image->rows > (unsigned long) height_limit))
        image->rows = (unsigned long) height_limit;

    if ((MagickResourceInfinity != pixels_limit) &&
        ((magick_int64_t) (image->columns*image->rows)) > pixels_limit)
      {
        magick_int64_t max_dimension = sqrt((double) pixels_limit);
        image->columns = (unsigned long) max_dimension;
        image->rows = (unsigned long) max_dimension;
      }

    if (image->logging)
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "JBIG: Setting maximum dimensions %lux%lu",
                            image->columns, image->rows);
    jbg_dec_maxsize(&jbig_info,(unsigned long) image->columns,
                    (unsigned long) image->rows);
  }

  image->depth=1;
  /*
    Read JBIG file.
  */
  buffer=MagickAllocateMemory(unsigned char *,MaxBufferSize);
  if (buffer == (unsigned char *) NULL)
    ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);
  status=JBG_EAGAIN;
  /* FIXME: Should handle JBG_EOK_INTR for multi-resolution support */
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "JBIG: Entering jbg_dec_in() decode loop...");
  do
    {
      length=(long) ReadBlob(image,MaxBufferSize,(char *) buffer);
      if (length == 0)
        break;
      p=buffer;
      count=0;
      while ((length > 0) && (status == JBG_EAGAIN))
        {
          status=jbg_dec_in(&jbig_info,p,length,&count);
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "JBIG: jbg_dec_in() returns 0x%02x (\"%s\")",
                                  status, jbg_strerror(status));
          p+=count;
          length-=count;
        }
    } while (status == JBG_EAGAIN);
  if (JBG_EOK != status)
    {
      jbg_dec_free(&jbig_info);
      MagickFreeMemory(buffer);
      ThrowReaderException(CorruptImageError,CorruptImage,image);
    }
  /*
    Create colormap.
  */
  image->columns=jbg_dec_getwidth(&jbig_info);
  image->rows=jbg_dec_getheight(&jbig_info);
  if ((image_info->type != GrayscaleType) &&
      (image_info->type != TrueColorType))
    {
      if (!AllocateImageColormap(image,2))
        {
          MagickFreeMemory(buffer);

        }
      image->colormap[0].red=0;
      image->colormap[0].green=0;
      image->colormap[0].blue=0;
      image->colormap[1].red=MaxRGB;
      image->colormap[1].green=MaxRGB;
      image->colormap[1].blue=MaxRGB;
    }
  image->x_resolution=300;
  image->y_resolution=300;
  image->is_grayscale=MagickTrue;
  image->is_monochrome=MagickTrue;
  image->colorspace=GRAYColorspace;
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "JBIG: %lux%lu, resolution %gx%g",
                          image->columns, image->rows,
                          image->x_resolution,image->y_resolution);
  if (image_info->ping)
    {
      jbg_dec_free(&jbig_info);
      MagickFreeMemory(buffer);
      CloseBlob(image);
      return(image);
    }
  if (CheckImagePixelLimits(image, exception) != MagickPass)
    {
      jbg_dec_free(&jbig_info);
      MagickFreeMemory(buffer);
      ThrowReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);
    }
  /*
    Convert bitmap image to pixel packets.
  */
  {
    ImportPixelAreaOptions
      import_options;

    ImportPixelAreaInfo
      import_info;

    ImportPixelAreaOptionsInit(&import_options);
    import_options.grayscale_miniswhite=MagickTrue;
    p=jbg_dec_getimage(&jbig_info,0);
    for (y=0; y < image->rows; y++)
      {
        q=SetImagePixels(image,0,y,image->columns,1);
        if (q == (PixelPacket *) NULL)
          break;
        if (!ImportImagePixelArea(image,GrayQuantum,1,p,&import_options,&import_info))
          break;
        p+=import_info.bytes_imported;
        if (!SyncImagePixels(image))
          break;
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,LoadImageText,
                                      image->filename,
                                      image->columns,image->rows))
            break;
      }
  }
  /*
    Free scale resource.
  */
  jbg_dec_free(&jbig_info);
  MagickFreeMemory(buffer);
  CloseBlob(image);
  image->is_grayscale=MagickTrue;
  image->is_monochrome=MagickTrue;
  StopTimer(&image->timer);
  return(image);
}
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r J B I G I m a g e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterJBIGImage adds attributes for the JBIG image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterJBIGImage method is:
%
%      RegisterJBIGImage(void)
%
*/
ModuleExport void RegisterJBIGImage(void)
{
  static const char
    description[]="Joint Bi-level Image experts Group interchange format";

  static const char
    version[]="JBIG-Kit " JBG_VERSION " (" JBG_LICENCE " license)";

  MagickInfo
    *entry;

  entry=SetMagickInfo("BIE");
#if defined(HasJBIG)
  entry->decoder=(DecoderHandler) ReadJBIGImage;
  entry->encoder=(EncoderHandler) WriteJBIGImage;
#endif
  entry->adjoin=False;
  entry->description=description;
    entry->version=version;
  entry->module="JBIG";
  entry->coder_class=StableCoderClass;
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("JBG");
#if defined(HasJBIG)
  entry->decoder=(DecoderHandler) ReadJBIGImage;
  entry->encoder=(EncoderHandler) WriteJBIGImage;
#endif
  entry->description=description;
  entry->version=version;
  entry->module="JBIG";
  entry->coder_class=StableCoderClass;
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("JBIG");
#if defined(HasJBIG)
  entry->decoder=(DecoderHandler) ReadJBIGImage;
  entry->encoder=(EncoderHandler) WriteJBIGImage;
#endif
  entry->description=description;
  entry->version=version;
  entry->module="JBIG";
  entry->coder_class=UnstableCoderClass;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r J B I G I m a g e                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterJBIGImage removes format registrations made by the
%  JBIG module from the list of supported formats.
%
%  The format of the UnregisterJBIGImage method is:
%
%      UnregisterJBIGImage(void)
%
*/
ModuleExport void UnregisterJBIGImage(void)
{
  (void) UnregisterMagickInfo("BIE");
  (void) UnregisterMagickInfo("JBG");
  (void) UnregisterMagickInfo("JBIG");
}

#if defined(HasJBIG)
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e J B I G I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteJBIGImage writes an image in the JBIG encoded image format.
%
%  The format of the WriteJBIGImage method is:
%
%      unsigned int WriteJBIGImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteJBIGImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/

static void JBIGEncode(unsigned char *pixels,size_t length,void *data)
{
  Image
    *image;

  image=(Image *) data;
  (void) WriteBlob(image,length,pixels);
}

static unsigned int WriteJBIGImage(const ImageInfo *image_info,Image *image)
{
  double
    jbig_lib_version;

  unsigned long
    y;

  register const PixelPacket
    *p;

  register unsigned char
    *q;

  struct jbg_enc_state
    jbig_info;

  unsigned char
    *pixels;

  size_t
    bytes_per_row;

  unsigned int
    status;

  unsigned long
    scene;

  size_t
    image_list_length;

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  image_list_length=GetImageListLength(image);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  jbig_lib_version=strtod(JBG_VERSION, (char **)NULL);
  scene=0;
  do
  {
    /*
      Ensure that image is in an RGB space.
    */
    (void) TransformColorspace(image,RGBColorspace);
    /*
      Allocate pixel data.
    */
    bytes_per_row=((image->columns+7) >> 3);
    pixels=MagickAllocateResourceLimitedArray(unsigned char *,bytes_per_row,image->rows);
    if (pixels == (unsigned char *) NULL)
      ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);
    /*
      Convert pixels to a bitmap.
    */
    {
      ExportPixelAreaOptions
        export_options;

      ExportPixelAreaInfo
        export_info;

      ExportPixelAreaOptionsInit(&export_options);
      export_options.grayscale_miniswhite=MagickTrue;
      q=pixels;
      for (y=0; y < image->rows; y++)
        {
          p=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
          if (p == (const PixelPacket *) NULL)
            break;
          if (ExportImagePixelArea(image,GrayQuantum,1,q,
                                   &export_options,&export_info) == MagickFail)
            break;
          q+=export_info.bytes_exported;
          if (image->previous == (Image *) NULL)
            if (QuantumTick(y,image->rows))
              if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                          SaveImageText,image->filename,
                                          image->columns,image->rows))
                break;
        }
    }
    /*
      Initialize JBIG info structure.
    */
    jbg_enc_init(&jbig_info,image->columns,image->rows,1,&pixels,
      (void (*)(unsigned char *,size_t,void *)) JBIGEncode,image);
    if (image_info->subimage != 0)
      jbg_enc_layers(&jbig_info,(int) image_info->subimage);
    else
      {
        long
          sans_offset;

        unsigned long
          x_resolution,
          y_resolution;

        x_resolution=640;
        y_resolution=480;
        sans_offset=0;
        if (image_info->density != (char *) NULL)
          (void) GetGeometry(image_info->density,&sans_offset,&sans_offset,
            &x_resolution,&y_resolution);
        (void) jbg_enc_lrlmax(&jbig_info,x_resolution,y_resolution);
      }
    (void) jbg_enc_lrange(&jbig_info,-1,-1);
    jbg_enc_options(&jbig_info, /* Encoder state */
                    JBG_ILEAVE| JBG_SMID, /* Order */
                    JBG_TPDON | JBG_TPBON | JBG_DPON, /* Options */
                    /* Lines per stripe in resolution layer 0. (was -1)*/
                    (jbig_lib_version < 1.6 ? -1 : 0),
                    -1, /* mx */
                    -1); /* my */
    /*
      Write JBIG image.
    */
    jbg_enc_out(&jbig_info);
    jbg_enc_free(&jbig_info);
    MagickFreeResourceLimitedMemory(pixels);
    if (image->next == (Image *) NULL)
      break;
    image=SyncNextImageInList(image);
    if (!MagickMonitorFormatted(scene++,image_list_length,
                                &image->exception,SaveImagesText,
                                image->filename))
      break;
  } while (image_info->adjoin);
  if (image_info->adjoin)
    while (image->previous != (Image *) NULL)
      image=image->previous;
  status &= CloseBlob(image);
  return(status);
}
#endif
