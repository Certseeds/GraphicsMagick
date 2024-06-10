/*
% Copyright (C) 2024-2024 GraphicsMagick Group
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                             AAA    AAA   IIIII                              %
%                            A   A  A   A    I                                %
%                            AAAAA  AAAAA    I                                %
%                            A   A  A   A    I                                %
%                            A   A  A   A  IIIII                              %
%                                                                             %
%                                                                             %
%                        Read/Write AAI X Image Format                        %
%                                                                             %
%                              Software Design                                %
%                                   Cristy                                    %
%                                 July 1992                                   %
%                              Jaroslav Fojtik                                %
%                                   2024                                      %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

#include "magick/studio.h"
#include "magick/blob.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"


#define ThrowAAIReaderException(code_,reason_,image_)   \
  {                                                     \
    MagickFreeResourceLimitedMemory(pixels);                           \
    ThrowReaderException(code_,reason_,image_);         \
  }
#define AAI_WIDTH_LIMIT 65536UL  /* Artificially limit width to 64K pixels */
#define AAI_HEIGHT_LIMIT 65536UL /* Artificially limit height to 64K pixels */


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d A A I I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadAAIImage() reads an AAI Dune image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadAAIImage method is:
%
%      Image *ReadAAIImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image_info: the image info.
%
%    o exception: return any errors or warnings in this structure.
*/
static Image *ReadAAIImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  Image *image;
  long y;
  register long x;
  magick_uint32_t height, width;
  unsigned int status;
  unsigned char *pixels = (unsigned char *) NULL;
  register unsigned char *p;
  register PixelPacket *q;

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  image = AllocateImage(image_info);
  status = OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFail)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  /*
    Read AAI image.
  */
  width = ReadBlobLSBLong(image);
  height = ReadBlobLSBLong(image);
  if (EOFBlob(image))
    ThrowAAIReaderException(CorruptImageError,UnexpectedEndOfFile,image);

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "AAI dimensions %ux%u",(unsigned)width,(unsigned)height);

  /*
    Impose a maximum width and height limit in order to avoid
    incredibly huge allocations.
  */
  if ((width > AAI_WIDTH_LIMIT) || (height > AAI_HEIGHT_LIMIT))
    ThrowAAIReaderException(CoderError,ImageColumnOrRowSizeIsNotSupported,image);

  do
  {	/* Convert AAI raster image to pixel packets. */
    size_t  row_bytes;

    image->columns=width;
    image->rows=height;
    image->depth=8;
    if (image_info->ping && (image_info->subrange != 0))
      if (image->scene >= (image_info->subimage+image_info->subrange-1))
        break;
    if (CheckImagePixelLimits(image, exception) != MagickPass)
      ThrowAAIReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);
    pixels=MagickAllocateResourceLimitedArray(unsigned char *,image->columns,4);
    if (pixels == (unsigned char *) NULL)
      ThrowAAIReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    row_bytes=(size_t) 4*image->columns;
    for (y=0; y < (long) image->rows; y++)
    {
      if (ReadBlob(image,row_bytes,pixels) != row_bytes)
        ThrowAAIReaderException(CorruptImageError,UnexpectedEndOfFile,image);
      p=pixels;
      q=SetImagePixels(image,0,y,image->columns,1);
      if (q == (PixelPacket *) NULL)
        {
          status=MagickFail;
          break;
        }
      for (x=0; x < (long) image->columns; x++)
      {
        q->blue=ScaleCharToQuantum(*p++);
        q->green=ScaleCharToQuantum(*p++);
        q->red=ScaleCharToQuantum(*p++);        
        if(*p==254) *p=255;	/* Full transparency is 254 in AAI. */
        q->opacity=(Quantum) (MaxRGB-ScaleCharToQuantum(*p++));        
        image->matte|=(q->opacity != OpaqueOpacity);
        q++;
      }
      if (!SyncImagePixels(image))
        {
          status=MagickFail;
          break;
        }
      if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,
                                      LoadImageText,image->filename,
                                      image->columns,image->rows))
            {
              status=MagickFail;
              break;
            }
    }
    MagickFreeResourceLimitedMemory(pixels);

    if (MagickFail == status)
      break;

    StopTimer(&image->timer);

    /*
      Proceed to next image.
    */
    if (image_info->subrange != 0)
      if (image->scene >= (image_info->subimage+image_info->subrange-1))
        break;
    width = ReadBlobLSBLong(image);
    height = ReadBlobLSBLong(image);
    if (!(EOFBlob(image)) && (width <= AAI_WIDTH_LIMIT) &&
        (height <= AAI_HEIGHT_LIMIT))
      {
        /*
          Allocate next image structure.
        */
        AllocateNextImage(image_info,image);
        if (image->next == (Image *) NULL)
          {
            DestroyImageList(image);
            return((Image *) NULL);
          }
        image=SyncNextImageInList(image);
        status=MagickMonitorFormatted(TellBlob(image),GetBlobSize(image),
                                      exception,LoadImagesText,image->filename);
        if (status == MagickFail)
          break;
      }
  } while (!(EOFBlob(image)));
  while (image->previous != (Image *) NULL)
    image=image->previous;
  CloseBlob(image);

  if (MagickFail == status)
    {
      DestroyImageList(image);
      image=(Image *) NULL;
    }

  return(image);
}


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e A A I I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteAAIImage writes an image to a file in AAI X image format.
%
%  The format of the WriteAAIImage method is:
%
%      unsigned int WriteAAIImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteAAIImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/
static unsigned int WriteAAIImage(const ImageInfo *image_info,Image *image)
{
  register const PixelPacket
    *p;

  register long
    x,
    y;

  register unsigned char
    *q;

  unsigned char
    *pixels;

  unsigned int
    status;

  unsigned long
    scene;

  size_t
    image_list_length;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  image_list_length=GetImageListLength(image);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  scene=0;
  do
  {
    /*
      Write AAI header.
    */
    (void) TransformColorspace(image,RGBColorspace);
    (void) WriteBlobLSBLong(image,image->columns);
    (void) WriteBlobLSBLong(image,image->rows);
    /*
      Allocate memory for pixels.
    */
    pixels=MagickAllocateResourceLimitedMemory(unsigned char *,image->columns*sizeof(PixelPacket));
    if (pixels == (unsigned char *) NULL)
      ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);
    /*
      Convert MIFF to AAI raster pixels.
    */
    for(y=0; y < (long) image->rows; y++)
    {
      p=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
      if (p == (PixelPacket *) NULL)
        break;
      q=pixels;
      for (x=0; x < (long) image->columns; x++)
      {
        *q++=ScaleQuantumToChar(p->blue);        
        *q++=ScaleQuantumToChar(p->green);
        *q++=ScaleQuantumToChar(p->red);
        *q=ScaleQuantumToChar(
          MaxRGB-(image->matte ? p->opacity : OpaqueOpacity));
        if(*q==255) *q=254;		/* 255 is not alloved in AAI */
        q++;
        p++;
      }
      (void) WriteBlob(image,q-pixels,(char *) pixels);
      if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                      SaveImageText,image->filename,
                                      image->columns,image->rows))
            break;
    }
    MagickFreeResourceLimitedMemory(pixels);
    if (image->next == (Image *) NULL)
      break;
    image=SyncNextImageInList(image);
    status=MagickMonitorFormatted(scene++,image_list_length,
                                  &image->exception,SaveImagesText,
                                  image->filename);
    if (status == False)
      break;
  } while (image_info->adjoin);
  if (image_info->adjoin)
    while (image->previous != (Image *) NULL)
      image=image->previous;
  status &= CloseBlob(image);
  return(status);
}


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r A A I I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterAAIImage adds attributes for the AAI image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterAAIImage method is:
%
%      RegisterAAIImage(void)
%
*/
ModuleExport void RegisterAAIImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("AAI");
  entry->decoder=(DecoderHandler) ReadAAIImage;
  entry->encoder=(EncoderHandler) WriteAAIImage;
  entry->description="AAI Dune image";
  entry->module="AAI";
  entry->coder_class=UnstableCoderClass;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r A A I I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnRegisterAAIImage removes format registrations made by the
%  AAI module from the list of supported formats.
%
%  The format of the UnRegisterAAIImage method is:
%
%      UnRegisterAAIImage(void)
%
*/
ModuleExport void UnregisterAAIImage(void)
{
  (void) UnregisterMagickInfo("AAI");
}
