/*
% Copyright (C) 2019 GraphicsMagick Group
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%               BBBB   RRRR    AAA   IIIII  L      L      EEEEE               %
%               B   B  R   R  A   A    I    L      L      E                   %
%               BBBB   RRRR   AAAAA    I    L      L      EEE                 %
%               B   B  R R    A   A    I    L      L      E                   %
%               BBBB   R  R   A   A  IIIII  LLLLL  LLLLL  EEEEE               %
%                                                                             %
%                                                                             %
%                          Read/Write Braille Format                          %
%                                                                             %
%                               Samuel Thibault                               %
%                                February 2008                                %
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
#include "magick/magick.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"

/*
  Forward declarations.
*/
static unsigned int
  WriteBRAILLEImage(const ImageInfo *,Image *);

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r B R A I L L E I m a g e                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  RegisterBRAILLEImage() adds values for the Braille format to
%  the list of supported formats.  The values include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterBRAILLEImage method is:
%
%      size_t RegisterBRAILLEImage(void)
%
*/
ModuleExport void RegisterBRAILLEImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("BRF");
  entry->encoder=(EncoderHandler) WriteBRAILLEImage;
  entry->adjoin=False;
  entry->description="BRF ASCII Braille format";
  entry->module="BRAILLE";
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("UBRL");
  entry->encoder=(EncoderHandler) WriteBRAILLEImage;
  entry->adjoin=False;
  entry->description="Unicode Text format";
  entry->module="BRAILLE";
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("UBRL6");
  entry->encoder=(EncoderHandler) WriteBRAILLEImage;
  entry->adjoin=False;
  entry->description="Unicode Text format 6dot";
  entry->module="BRAILLE";
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("ISOBRL");
  entry->encoder=(EncoderHandler) WriteBRAILLEImage;
  entry->adjoin=False;
  entry->description="ISO/TR 11548-1 format";
  entry->module="BRAILLE";
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("ISOBRL6");
  entry->encoder=(EncoderHandler) WriteBRAILLEImage;
  entry->adjoin=False;
  entry->description="ISO/TR 11548-1 format 6dot";
  entry->module="BRAILLE";
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r B R A I L L E I m a g e                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  UnregisterBRAILLEImage() removes format registrations made by the
%  BRAILLE module from the list of supported formats.
%
%  The format of the UnregisterBRAILLEImage method is:
%
%      UnregisterBRAILLEImage(void)
%
*/
ModuleExport void UnregisterBRAILLEImage(void)
{
  (void) UnregisterMagickInfo("BRF");
  (void) UnregisterMagickInfo("UBRL");
  (void) UnregisterMagickInfo("UBRL6");
  (void) UnregisterMagickInfo("ISOBRL");
  (void) UnregisterMagickInfo("ISOBRL6");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e B R A I L L E I m a g e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WriteBRAILLEImage() writes an image to a file in the Braille format.
%
%  The format of the WriteBRAILLEImage method is:
%
%      unsigned int WriteBRAILLEImage(const ImageInfo *image_info,
%        Image *image)
%
%  A description of each parameter follows.
%
%    o image_info: The image info.
%
%    o image:  The image.
%
*/
static unsigned int WriteBRAILLEImage(const ImageInfo *image_info,
  Image *image)
{
  char
    buffer[MaxTextExtent];

  IndexPacket
    polarity;

  int
    unicode = 0,
    iso_11548_1 = 0;

  unsigned int
    status;

  register const IndexPacket
    *indexes;

  register const PixelPacket
    *p;

  register unsigned long
    x;

  unsigned long
    cell_height = 4;

  unsigned long
    y;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image != (Image *) NULL);
  if (LocaleCompare(image_info->magick,"UBRL") == 0)
    unicode=1;
  else if (LocaleCompare(image_info->magick,"UBRL6") == 0)
    {
      unicode=1;
      cell_height=3;
    }
  else if (LocaleCompare(image_info->magick,"ISOBRL") == 0)
    iso_11548_1=1;
  else if (LocaleCompare(image_info->magick,"ISOBRL6") == 0)
    {
      iso_11548_1=1;
      cell_height=3;
    }
  else
    cell_height=3;
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    return(status);
  if (!iso_11548_1)
    {
      if (image->page.x != 0)
        {
          (void) FormatString(buffer,"X: %.20g\n",(double)
            image->page.x);
          (void) WriteBlobString(image,buffer);
        }
      if (image->page.y != 0)
        {
          (void) FormatString(buffer,"Y: %.20g\n",(double)
            image->page.y);
          (void) WriteBlobString(image,buffer);
        }
      (void) FormatString(buffer,"Width: %.20g\n",(double)
        (image->columns+(image->columns % 2)));
      (void) WriteBlobString(image,buffer);
      (void) FormatString(buffer,"Height: %.20g\n",(double)
        image->rows);
      (void) WriteBlobString(image,buffer);
      (void) WriteBlobString(image,"\n");
    }
  (void) SetImageType(image,BilevelType);
  polarity=PixelIntensityToQuantum(&image->colormap[0]) >= (MaxRGB/2);
  if (image->colors == 2)
    polarity=PixelIntensityToQuantum(&image->colormap[0]) >=
      PixelIntensityToQuantum(&image->colormap[1]);
  for (y=0; y < image->rows; y+=cell_height)
  {
    if ((y+cell_height) > image->rows)
      cell_height = (image->rows-y);
    p=AcquireImagePixels(image,0,y,image->columns,cell_height,&image->exception);
    if (p == (const PixelPacket *) NULL)
      break;
    indexes=AccessImmutableIndexes(image);
    for (x=0; x < image->columns; x+=2)
    {
      unsigned char cell = 0;
      unsigned long two_columns = x+1 < image->columns;

      do
      {
#define do_cell(dx,dy,bit) do { \
        cell |= (indexes[x+dx+dy*image->columns] == polarity) << bit; \
} while (0)

        do_cell(0,0,0);
        if (two_columns)
          do_cell(1,0,3);
        if (cell_height < 2)
          break;

        do_cell(0,1,1);
        if (two_columns)
          do_cell(1,1,4);
        if (cell_height < 3)
          break;

        do_cell(0,2,2);
        if (two_columns)
          do_cell(1,2,5);
        if (cell_height < 4)
          break;

        do_cell(0,3,6);
        if (two_columns)
          do_cell(1,3,7);
      } while(0);

      if (unicode)
        {
          unsigned char utf8[3];
          /* Unicode text */
          utf8[0] = (unsigned char) (0xe0|((0x28>>4)&0x0f));
          utf8[1] = 0x80|((0x28<<2)&0x3f)|(cell>>6);
          utf8[2] = 0x80|(cell&0x3f);
          (void) WriteBlob(image,3,utf8);
        }
      else if (iso_11548_1)
        {
          /* ISO/TR 11548-1 binary */
          (void) WriteBlobByte(image,cell);
        }
      else
        {
          /* BRF */
          static const unsigned char iso_to_brf[64] = {
            ' ', 'A', '1', 'B', '\'', 'K', '2', 'L',
            '@', 'C', 'I', 'F', '/', 'M', 'S', 'P',
            '"', 'E', '3', 'H', '9', 'O', '6', 'R',
            '^', 'D', 'J', 'G', '>', 'N', 'T', 'Q',
            ',', '*', '5', '<', '-', 'U', '8', 'V',
            '.', '%', '[', '$', '+', 'X', '!', '&',
            ';', ':', '4', '\\', '0', 'Z', '7', '(',
            '_', '?', 'W', ']', '#', 'Y', ')', '='
          };
          (void) WriteBlobByte(image,iso_to_brf[cell]);
        }
    }
    if (iso_11548_1 == 0)
      (void) WriteBlobByte(image,'\n');
  }
  (void) CloseBlob(image);
  return(MagickTrue);
}
