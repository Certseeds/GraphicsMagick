/*
% Copyright (C) 2003-2020 GraphicsMagick Group
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
%                            SSSSS   CCCC  TTTTT                              %
%                            SS     C        T                                %
%                             SSS   C        T                                %
%                               SS  C        T                                %
%                            SSSSS   CCCC    T                                %
%                                                                             %
%                                                                             %
%                   Read Scitex HandShake Image Format.                       %
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
  The Scitex HandShake data format is specified in the document

  HandShake Foreign File Transfer Protocol, Scitex Corporation, Ltd.,
  Revision A: April 1988, Document No. 788-37898A, Catalog No. 399Z37898

  http://www.oreilly.com/www/centers/gff/formats/scitex
/
*/


/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/blob.h"
#include "magick/pixel_cache.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/utility.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s S C T                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsSCT returns True if the image format type, identified by the
%  magick string, is SCT.
%
%  The format of the IsSCT method is:
%
%      unsigned int IsSCT(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsSCT returns True if the image format type is SCT.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsSCT(const unsigned char *magick,const size_t length)
{
  if (length < 2)
    return(False);
  if (LocaleNCompare((char *) magick,"CT",2) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d S C T I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadSCTImage reads a Scitex image file and returns it.  It allocates
%  the memory necessary for the new Image structure and returns a pointer to
%  the new image.
%
%  The format of the ReadSCTImage method is:
%
%      Image *ReadSCTImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadSCTImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/
static Image *ReadSCTImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  char
    buffer[768],
    magick[2];

  Image
    *image;

  long
    y;

  register long
    x;

  register PixelPacket
    *q;

  int
    c;

  unsigned int
    status;

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
    Read control block.
  */
  do
    {
      if (ReadBlob(image,80,(char *) buffer) != 80)
        break;
      if (ReadBlob(image,2,(char *) magick) != 2)
        break;
      if ((LocaleNCompare((char *) magick,"CT",2) != 0) &&
          (LocaleNCompare((char *) magick,"LW",2) != 0) &&
          (LocaleNCompare((char *) magick,"BM",2) != 0) &&
          (LocaleNCompare((char *) magick,"PG",2) != 0) &&
          (LocaleNCompare((char *) magick,"TX",2) != 0))
        ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
      if ((LocaleNCompare((char *) magick,"LW",2) == 0) ||
          (LocaleNCompare((char *) magick,"BM",2) == 0) ||
          (LocaleNCompare((char *) magick,"PG",2) == 0) ||
          (LocaleNCompare((char *) magick,"TX",2) == 0))
        ThrowReaderException(CoderError,OnlyContinuousTonePictureSupported,image);
      if (ReadBlob(image,174,(char *) buffer) != 174)
        break;
      if (ReadBlob(image,768,(char *) buffer) != 768)
        break;
      /*
        Read parameter block.
      */
      if (ReadBlob(image,32,(char *) buffer) != 32)
        break;
      if (ReadBlob(image,14,(char *) buffer) != 14)
        break;
      buffer[14]='\0';
      image->rows=MagickAtoL(buffer) & 0x7FFFFFFF;
      if (ReadBlob(image,14,(char *) buffer) != 14)
        break;
      buffer[14]='\0';
      image->columns=MagickAtoL(buffer) & 0x7FFFFFFF;
      if (ReadBlob(image,196,(char *) buffer) != 196)
        break;
      if (ReadBlob(image,768,(char *) buffer) != 768)
        break;
      image->colorspace=CMYKColorspace;
    }
  while (0);
  if (EOFBlob(image))
    ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
  if (image_info->ping)
    {
      CloseBlob(image);
      StopTimer(&image->timer);
      return(image);
    }

  if (CheckImagePixelLimits(image, exception) != MagickPass)
    ThrowReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);

  /*
    Convert SCT raster image to pixel packets.
  */
  for (y=0; y < (long) image->rows; y++)
  {
    q=SetImagePixelsEx(image,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      break;
    for (x=0; x < (long) image->columns; x++)
    {
      if ((c = ReadBlobByte(image)) == EOF)
        break;
      q->red=(Quantum) (MaxRGB-ScaleCharToQuantum(c));
      q++;
    }
    if ((image->columns % 2) != 0)
      if (ReadBlobByte(image) == EOF)  /* pad */
        break;
    q=GetImagePixelsEx(image,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      break;
    for (x=0; x < (long) image->columns; x++)
    {
      if ((c = ReadBlobByte(image)) == EOF)
        break;
      c &= 0xff;
      q->green=(Quantum) (MaxRGB-ScaleCharToQuantum(c));
      q++;
    }
    if ((image->columns % 2) != 0)
      if (ReadBlobByte(image) == EOF)  /* pad */
        break;
    q=GetImagePixelsEx(image,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      break;
    for (x=0; x < (long) image->columns; x++)
    {
      if ((c = ReadBlobByte(image)) == EOF)
        break;
      c &= 0xff;
      q->blue=(Quantum) (MaxRGB-ScaleCharToQuantum(c));
      q++;
    }
    if ((image->columns % 2) != 0)
      if (ReadBlobByte(image) == EOF)  /* pad */
        break;
    q=GetImagePixelsEx(image,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      break;
    for (x=0; x < (long) image->columns; x++)
    {
      if ((c = ReadBlobByte(image)) == EOF)
        break;
      c &= 0xff;
      q->opacity=(Quantum) (MaxRGB-ScaleCharToQuantum(c));
      q++;
    }
    if (!SyncImagePixelsEx(image,exception))
      break;
    if ((image->columns % 2) != 0)
      if (ReadBlobByte(image) == EOF)  /* pad */
        break;
    if (QuantumTick(y,image->rows))
      if (!MagickMonitorFormatted(y,image->rows,exception,LoadImageText,
                                  image->filename,
                                  image->columns,image->rows))
        break;
    if (EOFBlob(image))
      break;
  }
  if (EOFBlob(image))
    ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,
      image->filename);
  CloseBlob(image);
  StopTimer(&image->timer);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r S C T I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterSCTImage adds attributes for the SCT image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterSCTImage method is:
%
%      RegisterSCTImage(void)
%
*/
ModuleExport void RegisterSCTImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("SCT");
  entry->decoder=(DecoderHandler) ReadSCTImage;
  entry->magick=(MagickHandler) IsSCT;
  entry->adjoin=False;
  entry->description="Scitex HandShake";
  entry->module="SCT";
  entry->coder_class=UnstableCoderClass;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r S C T I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterSCTImage removes format registrations made by the
%  SCT module from the list of supported formats.
%
%  The format of the UnregisterSCTImage method is:
%
%      UnregisterSCTImage(void)
%
*/
ModuleExport void UnregisterSCTImage(void)
{
  (void) UnregisterMagickInfo("SCT");
}
