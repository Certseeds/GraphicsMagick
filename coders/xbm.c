/*
% Copyright (C) 2003-2018 GraphicsMagick Group
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
%                            X   X  BBBB   M   M                              %
%                             X X   B   B  MM MM                              %
%                              X    BBBB   M M M                              %
%                             X X   B   B  M   M                              %
%                            X   X  BBBB   M   M                              %
%                                                                             %
%                                                                             %
%                 Read/Write X Windows System Bitmap Format.                  %
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
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"

/*
  Forward declarations.
*/
static unsigned int
  WriteXBMImage(const ImageInfo *,Image *);

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s X B M                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsXBM returns True if the image format type, identified by the
%  magick string, is XBM.
%
%  The format of the IsXBM method is:
%
%      unsigned int IsXBM(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsXBM returns True if the image format type is XBM.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsXBM(const unsigned char *magick,const size_t length)
{
  if (length < 7)
    return(False);
  if (LocaleNCompare((char *) magick,"#define",7) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d X B M I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadXBMImage reads an X11 bitmap image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadXBMImage method is:
%
%      Image *ReadXBMImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadXBMImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/

static int XBMInteger(Image *image,const unsigned int max_digits, short int *hex_digits)
{
  unsigned int
    digits;

  int
    c,
    value;

  /*
    Read hex value in form 0xhh or 0xhhhh from text which may look
    like ", 0x7f".  FIXME: This implementation is non-validating.
  */

  value=0;
  digits=0U;
  for ( digits=0U; digits <= max_digits+1; )
  {
    c=ReadBlobByte(image);
    if (c == EOF)
      {
        value=(-1);
        break;
      }
    c&=0xff;
    if (isxdigit(c))
      {
        value=(value << 4)+hex_digits[c];
        digits++;
        continue;
      }
    if ((hex_digits[c]) < 0 && digits)
      break;
  }
  /* The '0' in '0x' is currently counted as a digit */
  if (digits > max_digits+1)
    value=(-1);
  return(value);
}

static Image *ReadXBMImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  char
    buffer[MaxTextExtent],
    name[MaxTextExtent];

  Image
    *image;

  register IndexPacket
    *indexes;

  register size_t
    bytes_per_line,
    i;

  unsigned long
    x,
    y;

  long
    columns_signed,
    rows_signed;

  register PixelPacket
    *q;

  register unsigned char
    *p;

  unsigned char
    *data;

  unsigned int
    bit,
    byte,
    padding,
    version;

  int
    value;

  short int
    hex_digits[256];

  MagickPassFail
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
    Read X bitmap header.
  */
  (void) memset(buffer,0,sizeof(buffer));
  name[0]='\0';
  columns_signed=0;
  rows_signed=0;
  while (ReadBlobString(image,buffer) != (char *) NULL)
    if (sscanf(buffer,"#define %s %ld",name,&columns_signed) == 2)
      if ((strlen(name) >= 6) &&
          (LocaleCompare(name+strlen(name)-6,"_width") == 0))
          break;
  while (ReadBlobString(image,buffer) != (char *) NULL)
    if (sscanf(buffer,"#define %s %ld",name,&rows_signed) == 2)
      if ((strlen(name) >= 7) &&
          (LocaleCompare(name+strlen(name)-7,"_height") == 0))
          break;
  if (EOFBlob(image))
      ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
  if ((columns_signed <= 0) || (rows_signed <= 0))
    ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
  image->columns=(unsigned long) columns_signed;
  image->rows=(unsigned long) rows_signed;
  image->depth=8;
  image->storage_class=PseudoClass;
  image->colors=2;
  /*
    Scan until hex digits.
  */
  version=11;
  while (ReadBlobString(image,buffer) != (char *) NULL)
  {
    if (sscanf(buffer,"static short %s = {",name) == 1)
      version=10;
    else
      if (sscanf(buffer,"static unsigned char %s = {",name) == 1)
        version=11;
      else
        if (sscanf(buffer,"static char %s = {",name) == 1)
          version=11;
        else
          continue;
    p=(unsigned char *) strrchr(name,'_');
    if (p == (unsigned char *) NULL)
      p=(unsigned char *) name;
    else
      p++;
    if (LocaleCompare("bits[]",(char *) p) == 0)
      break;
  }
  if (EOFBlob(image))
    ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);

  /*
    Initialize image structure.
  */
  if (!AllocateImageColormap(image,image->colors))
    ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);
  /*
    Initialize colormap.
  */
  image->colormap[0].red=MaxRGB;
  image->colormap[0].green=MaxRGB;
  image->colormap[0].blue=MaxRGB;
  image->colormap[1].red=0;
  image->colormap[1].green=0;
  image->colormap[1].blue=0;
  if (image_info->ping)
    {
      CloseBlob(image);
      return(image);
    }
  if (CheckImagePixelLimits(image, exception) != MagickPass)
      ThrowReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);
  /*
    Allocate temporary storage for X bitmap image
  */
  padding=0;
  if ((image->columns % 16) && ((image->columns % 16) < 9)  && (version == 10))
    padding=1;
  bytes_per_line=(image->columns+7)/8+padding;
  data=MagickAllocateArray(unsigned char *,image->rows,bytes_per_line);
  if (data == (unsigned char *) NULL)
    ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);
  /*
    Initialize hex values.
  */
  for (i = 0; i < sizeof(hex_digits)/sizeof(hex_digits[0]); i++)
    hex_digits[i]=(-1);
  hex_digits['0']=0;
  hex_digits['1']=1;
  hex_digits['2']=2;
  hex_digits['3']=3;
  hex_digits['4']=4;
  hex_digits['5']=5;
  hex_digits['6']=6;
  hex_digits['7']=7;
  hex_digits['8']=8;
  hex_digits['9']=9;
  hex_digits['A']=10;
  hex_digits['B']=11;
  hex_digits['C']=12;
  hex_digits['D']=13;
  hex_digits['E']=14;
  hex_digits['F']=15;
  hex_digits['a']=10;
  hex_digits['b']=11;
  hex_digits['c']=12;
  hex_digits['d']=13;
  hex_digits['e']=14;
  hex_digits['f']=15;
  hex_digits['x']=0;
  hex_digits[' ']=(-1);
  hex_digits[',']=(-1);
  hex_digits['}']=(-1);
  hex_digits['\n']=(-1);
  hex_digits['\t']=(-1);
  /*
    Read hex image data.
  */
  p=data;
  if (version == 10)
    for (i=0; i < (bytes_per_line*image->rows); (i+=2))
    {
      value=XBMInteger(image,4,hex_digits);
      if (value < 0)
        {
          MagickFreeMemory(data);
          ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
        }
      *p++=(unsigned char) value;
      if (!padding || ((i+2) % bytes_per_line))
        *p++=(unsigned char) (value >> 8);
    }
  else
    for (i=0; i < (bytes_per_line*image->rows); i++)
    {
      value=XBMInteger(image,2,hex_digits);
      if (value < 0)
        {
          MagickFreeMemory(data);
          ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
        }
      *p++=(unsigned char) value;
    }
  /*
    Convert X bitmap image to pixel packets.
  */
  p=data;
  for (y=0; y < image->rows; y++)
  {
    q=SetImagePixels(image,0,y,image->columns,1);
    if (q == (PixelPacket *) NULL)
      break;
    indexes=AccessMutableIndexes(image);
    bit=0U;
    byte=0U;
    for (x=0; x < image->columns; x++)
    {
      if (bit == 0U)
        byte=(*p++);
      indexes[x]=byte & 0x01 ? 0x01 : 0x00;
      bit++;
      byte>>=1U;
      if (bit == 8U)
        bit=0U;
    }
    if (!SyncImagePixels(image))
      break;
    if (QuantumTick(y,image->rows))
      if (!MagickMonitorFormatted(y,image->rows,exception,
                                  LoadImageText,image->filename,
                                  image->columns,image->rows))
         break;
  }
  MagickFreeMemory(data);
  (void) SyncImage(image);
  CloseBlob(image);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r X B M I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterXBMImage adds attributes for the XBM image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterXBMImage method is:
%
%      RegisterXBMImage(void)
%
*/
ModuleExport void RegisterXBMImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("XBM");
  entry->decoder=(DecoderHandler) ReadXBMImage;
  entry->encoder=(EncoderHandler) WriteXBMImage;
  entry->magick=(MagickHandler) IsXBM;
  entry->adjoin=False;
  entry->description="X Windows system bitmap (black/white)";
  entry->module="XBM";
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r X B M I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterXBMImage removes format registrations made by the
%  XBM module from the list of supported formats.
%
%  The format of the UnregisterXBMImage method is:
%
%      UnregisterXBMImage(void)
%
*/
ModuleExport void UnregisterXBMImage(void)
{
  (void) UnregisterMagickInfo("XBM");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e X B M I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Procedure WriteXBMImage writes an image to a file in the X bitmap format.
%
%  The format of the WriteXBMImage method is:
%
%      unsigned int WriteXBMImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteXBMImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/
static unsigned int WriteXBMImage(const ImageInfo *image_info,Image *image)
{
  char
    basename[MaxTextExtent],
    buffer[MaxTextExtent];

  int
    y;

  register const PixelPacket
    *p;

  register long
    x;

  register const IndexPacket
    *indexes;

  unsigned char
    bit,
    byte,
    polarity;

  unsigned int
    status;

  unsigned long
    count;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  (void) TransformColorspace(image,RGBColorspace);
  /*
    Write X bitmap header.
  */
  GetPathComponent(image->filename,BasePath,basename);
  FormatString(buffer,"#define %.1024s_width %lu\n",basename,image->columns);
  (void) WriteBlob(image,strlen(buffer),buffer);
  FormatString(buffer,"#define %.1024s_height %lu\n",basename,image->rows);
  (void) WriteBlob(image,strlen(buffer),buffer);
  FormatString(buffer,"static char %.1024s_bits[] = {\n",basename);
  (void) WriteBlob(image,strlen(buffer),buffer);
  (void) strcpy(buffer," ");
  (void) WriteBlob(image,strlen(buffer),buffer);
  /*
    Convert MIFF to X bitmap pixels.
  */
  (void) SetImageType(image,BilevelType);
  polarity=(PixelIntensityToQuantum(&image->colormap[0]) < (MaxRGB/2));
  if (image->colors == 2)
    polarity=(PixelIntensityToQuantum(&image->colormap[0]) <
              PixelIntensityToQuantum(&image->colormap[1]));
  bit=0;
  byte=0;
  count=0;
  x=0;
  y=0;
  (void) strcpy(buffer," ");
  (void) WriteBlob(image,strlen(buffer),buffer);
  for (y=0; y < (long) image->rows; y++)
  {
    p=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
    if (p == (const PixelPacket *) NULL)
      break;
    indexes=AccessImmutableIndexes(image);
    for (x=0; x < (long) image->columns; x++)
    {
      byte>>=1;
      if (indexes[x] != polarity)
        byte|=0x80;
      bit++;
      if (bit == 8)
        {
          /*
            Write a bitmap byte to the image file.
          */
          FormatString(buffer,"0x%02X, ",(unsigned int) (byte & 0xff));
          (void) WriteBlob(image,strlen(buffer),buffer);
          count++;
          if (count == 12)
            {
              (void) strcpy(buffer,"\n  ");
              (void) WriteBlob(image,strlen(buffer),buffer);
              count=0;
            };
          bit=0;
          byte=0;
        }
        p++;
      }
    if (bit != 0)
      {
        /*
          Write a bitmap byte to the image file.
        */
        byte>>=(8-bit);
        FormatString(buffer,"0x%02X, ",(unsigned int) (byte & 0xff));
        (void) WriteBlob(image,strlen(buffer),buffer);
        count++;
        if (count == 12)
          {
            (void) strcpy(buffer,"\n  ");
            (void) WriteBlob(image,strlen(buffer),buffer);
            count=0;
          };
        bit=0;
        byte=0;
      };
    if (QuantumTick(y,image->rows))
      if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                  SaveImageText,image->filename,
                                  image->columns,image->rows))
        break;
  }
  (void) strcpy(buffer,"};\n");
  (void) WriteBlob(image,strlen(buffer),buffer);
  CloseBlob(image);
  return(True);
}
