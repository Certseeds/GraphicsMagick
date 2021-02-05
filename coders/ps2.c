/*
% Copyright (C) 2003 - 2021 GraphicsMagick Group
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
%                            PPPP   SSSSS  22222                              %
%                            P   P  SS        22                              %
%                            PPPP    SSS    222                               %
%                            P         SS  22                                 %
%                            P      SSSSS  22222                              %
%                                                                             %
%                                                                             %
%                     Write Postscript Level II Format.                       %
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
#include "magick/analyze.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/pixel_cache.h"
#include "magick/color.h"
#include "magick/constitute.h"
#include "magick/compress.h"
#include "magick/enum_strings.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/tempfile.h"
#include "magick/utility.h"
#if defined(HasTIFF)
#define CCITTParam  "-1"
#else
#define CCITTParam  "0"
#endif

/*
  Forward declarations.
*/
static unsigned int
  WritePS2Image(const ImageInfo *,Image *);

#if defined(HasTIFF)
#if defined(HAVE_TIFFCONF_H)
#  include "tiffconf.h"
#endif
#include "tiffio.h"

#if defined(HAVE_STDINT_H) && (TIFFLIB_VERSION >= 20201219)
#  undef uint16
#  define uint16 uint16_t
#  undef uint32
#  define uint32 uint32_t
#endif /* TIFFLIB_VERSION */

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   H u f f m a n 2 D E n c o d e I m a g e                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method Huffman2DEncodeImage compresses an image via two-dimensional
%  Huffman-coding.
%
%  The format of the Huffman2DEncodeImage method is:
%
%      unsigned int Huffman2DEncodeImage(const ImageInfo *image_info,
%        Image *image)
%
%  A description of each parameter follows:
%
%    o status:  Method Huffman2DEncodeImage returns True if all the pixels are
%      compressed without error, otherwise False.
%
%    o image_info: The image info..
%
%    o image: The image.
%
*/
static unsigned int Huffman2DEncodeImage(const ImageInfo *image_info,
  Image *image)
{
  char
    filename[MaxTextExtent];

  Image
    *huffman_image;

  ImageInfo
    *clone_info;

  long
    count,
    j;

  register long
    i;

  TIFF
    *tiff;

  uint16
    fillorder;

  unsigned char
    *buffer;

  unsigned int
    status;

  unsigned long
    *byte_count,
    strip_size;

  /*
    Write image as CCITTFax4 TIFF image to a temporary file.
  */
  assert(image_info != (ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  huffman_image=CloneImage(image,0,0,True,&image->exception);
  if (huffman_image == (Image *) NULL)
    return(False);
  (void) SetImageType(huffman_image,BilevelType);
  if(!AcquireTemporaryFileName(filename))
    {
      DestroyImage(huffman_image);
      ThrowBinaryException(FileOpenError,UnableToCreateTemporaryFile,
        filename);
    }
  FormatString(huffman_image->filename,"tiff:%s",filename);
  clone_info=CloneImageInfo(image_info);
  clone_info->compression=Group4Compression;
  clone_info->type=BilevelType;
  (void) AddDefinitions(clone_info,"tiff:fill-order=msb2lsb",
                        &image->exception);
  status=WriteImage(clone_info,huffman_image);
  DestroyImageInfo(clone_info);
  DestroyImage(huffman_image);
  if (status == False)
    return(False);
  tiff=TIFFOpen(filename,"rb");
  if (tiff == (TIFF *) NULL)
    {
      (void) LiberateTemporaryFile(filename);
      ThrowBinaryException(FileOpenError,UnableToOpenFile,
        image_info->filename)
    }
  /*
    Allocate raw strip buffer.
  */
  (void) TIFFGetField(tiff,TIFFTAG_STRIPBYTECOUNTS,&byte_count);
  strip_size=byte_count[0];
  for (i=1; i < (long) TIFFNumberOfStrips(tiff); i++)
    if (byte_count[i] > strip_size)
      strip_size=byte_count[i];
  buffer=MagickAllocateResourceLimitedMemory(unsigned char *,strip_size);
  if (buffer == (unsigned char *) NULL)
    {
      TIFFClose(tiff);
      (void) LiberateTemporaryFile(filename);
      ThrowBinaryException(ResourceLimitError,MemoryAllocationFailed,
        (char *) NULL)
    }
  /*
    Compress runlength encoded to 2D Huffman pixels.
  */
  (void) TIFFGetFieldDefaulted(tiff,TIFFTAG_FILLORDER,&fillorder);
  for (i=0; i < (long) TIFFNumberOfStrips(tiff); i++)
  {
    Ascii85Initialize(image);
    count=TIFFReadRawStrip(tiff,(uint32) i,buffer,(long) byte_count[i]);
    if (fillorder == FILLORDER_LSB2MSB)
      TIFFReverseBits(buffer,count);
    for (j=0; j < count; j++)
      Ascii85Encode(image,(unsigned long) buffer[j]);
    Ascii85Flush(image);
  }
  MagickFreeResourceLimitedMemory(buffer);
  TIFFClose(tiff);
  (void) LiberateTemporaryFile(filename);
  return(True);
}
#else
static unsigned int Huffman2DEncodeImage(const ImageInfo *image_info,
  Image *image)
{
  ARG_NOT_USED(image_info);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  ThrowBinaryException(MissingDelegateError,TIFFLibraryIsNotAvailable,image->filename);
}
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r P S 2 I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterPS2Image adds attributes for the PS2 image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterPS2Image method is:
%
%      RegisterPS2Image(void)
%
*/
ModuleExport void RegisterPS2Image(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("EPS2");
  entry->encoder=(EncoderHandler) WritePS2Image;
  entry->adjoin=False;
  entry->seekable_stream=True;
  entry->description="Adobe Level II Encapsulated PostScript";
  entry->module="PS2";
  entry->coder_class=PrimaryCoderClass;
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("PS2");
  entry->encoder=(EncoderHandler) WritePS2Image;
  entry->seekable_stream=True;
  entry->description="Adobe Level II PostScript";
  entry->module="PS2";
  entry->coder_class=PrimaryCoderClass;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r P S 2 I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterPS2Image removes format registrations made by the
%  PS2 module from the list of supported formats.
%
%  The format of the UnregisterPS2Image method is:
%
%      UnregisterPS2Image(void)
%
*/
ModuleExport void UnregisterPS2Image(void)
{
  (void) UnregisterMagickInfo("EPS2");
  (void) UnregisterMagickInfo("PS2");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e P S 2 I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WritePS2Image translates an image to encapsulated Postscript
%  Level II for printing.  If the supplied geometry is null, the image is
%  centered on the Postscript page.  Otherwise, the image is positioned as
%  specified by the geometry.
%
%  The format of the WritePS2Image method is:
%
%      unsigned int WritePS2Image(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows:
%
%    o status: Method WritePS2Image return True if the image is printed.
%      False is returned if the image file cannot be opened for printing.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image: The address of a structure of type Image;  returned from
%      ReadImage.
%
%
*/
static unsigned int WritePS2Image(const ImageInfo *image_info,Image *image)
{
  char
    buffer[MaxTextExtent],
    date[MaxTextExtent],
    density[MaxTextExtent],
    page_geometry[MaxTextExtent],
    **labels;

  CompressionType
    compression;

  const ImageAttribute
    *attribute;

  double
    dx_resolution,
    dy_resolution,
    x_resolution,
    x_scale,
    y_resolution,
    y_scale;

  magick_off_t
    current,
    start,
    stop;

  int
    count,
    status;

  long
    j,
    y;

  RectangleInfo
    geometry;

  register const PixelPacket
    *p;

  register const IndexPacket
    *indexes;

  register long
    x;

  register long
    i;

  SegmentInfo
    bounds={0.0,0.0,0.0,0.0};

  size_t
    length;

  time_t
    timer;

  unsigned char
    *pixels;

  unsigned long
    number_pixels,
    page,
    scene,
    text_size;

  void
    *blob;

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
  compression=image->compression;
  if (image_info->compression != UndefinedCompression)
    compression=image_info->compression;
  switch (compression)
  {
#if !defined(HasJPEG)
    case JPEGCompression:
    {
      compression=RLECompression;
      ThrowException(&image->exception,MissingDelegateError,JPEGLibraryIsNotAvailable,image->filename);
      break;
    }
#endif
#if !defined(HasZLIB)
    case ZipCompression:
    {
      compression=RLECompression;
      ThrowException(&image->exception,MissingDelegateError,ZipLibraryIsNotAvailable,image->filename);
      break;
    }
#endif
    default:
      break;
  }
  page=1;
  scene=0;
  do
  {
    ImageCharacteristics
      characteristics;

    /*
      Scale image to size of Postscript page.
    */
    text_size=0;
    attribute=GetImageAttribute(image,"label");
    if (attribute != (const ImageAttribute *) NULL)
      text_size=(unsigned int)
        (MultilineCensus(attribute->value)*image_info->pointsize+12);
    SetGeometry(image,&geometry);
    geometry.y=(long) text_size;
    FormatString(page_geometry,"%lux%lu",image->columns,image->rows);
    if (image_info->page != (char *) NULL)
      (void) strlcpy(page_geometry,image_info->page,MaxTextExtent);
    else
      if ((image->page.width != 0) && (image->page.height != 0))
        (void) FormatString(page_geometry,"%lux%lu%+ld%+ld",image->page.width,
          image->page.height,image->page.x,image->page.y);
      else
        if (LocaleCompare(image_info->magick,"PS2") == 0)
          (void) strlcpy(page_geometry,PSPageGeometry,sizeof(page_geometry));
    (void) GetMagickGeometry(page_geometry,&geometry.x,&geometry.y,
       &geometry.width,&geometry.height);
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Image Resolution: %gx%g %s",
                          image->x_resolution,
                          image->y_resolution,
                          ResolutionTypeToString(image->units));
    /*
      Scale relative to dots-per-inch.
    */
    dx_resolution=72.0;
    dy_resolution=72.0;
    x_resolution=72.0;
    (void) strlcpy(density,PSDensityGeometry,sizeof(density));
    count=GetMagickDimension(density,&x_resolution,&y_resolution,NULL,NULL);
    if (count != 2)
      y_resolution=x_resolution;
    /*
      Use override resolution information if it appears to be valid.
    */
    if ((image_info->density != (char *) NULL) &&
        ((image_info->units == PixelsPerInchResolution) ||
         (image_info->units == PixelsPerCentimeterResolution)))
      {
        count=GetMagickDimension(image_info->density,&x_resolution,
          &y_resolution,NULL,NULL);
        if (count != 2)
          y_resolution=x_resolution;
        if (image_info->units == PixelsPerCentimeterResolution)
          {
            x_resolution *= 2.54;
            y_resolution *= 2.54;
          }
      }
    /*
      Use image resolution information if it appears to be valid.
    */
    else if ((image->x_resolution > 0.0) && (image->y_resolution > 0.0) &&
             ((image->units == PixelsPerInchResolution) ||
              (image->units == PixelsPerCentimeterResolution)))
      {
        x_resolution = image->x_resolution;
        y_resolution = image->y_resolution;
        if (image->units == PixelsPerCentimeterResolution)
          {
            x_resolution *= 2.54;
            y_resolution *= 2.54;
          }
      }
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Postscript Resolution: %gx%g DPI",
                          x_resolution,y_resolution);
    x_scale=(geometry.width*dx_resolution)/x_resolution;
    geometry.width=(unsigned long) (x_scale+0.5);
    y_scale=(geometry.height*dy_resolution)/y_resolution;
    geometry.height=(unsigned long) (y_scale+0.5);
    if (page == 1)
      {
        /*
          Output Postscript header.
        */
 #if defined(HAVE_CTIME_R)
        char time_buf[26];
#endif /* defined(HAVE_CTIME_R) */
       if (LocaleCompare(image_info->magick,"PS2") == 0)
          (void) strcpy(buffer,"%!PS-Adobe-3.0\n");
        else
          (void) strcpy(buffer,"%!PS-Adobe-3.0 EPSF-3.0\n");
        (void) WriteBlobString(image,buffer);
        (void) WriteBlobString(image,"%%Creator: (GraphicsMagick)\n");
        FormatString(buffer,"%%%%Title: (%.1024s)\n",image->filename);
        (void) WriteBlobString(image,buffer);
        timer=time((time_t *) NULL);
#if defined(HAVE_CTIME_R)
        (void) strlcpy(date,ctime_r(&timer,time_buf),MaxTextExtent);
#else
        (void) strlcpy(date,ctime(&timer),MaxTextExtent); /* Thread-unsafe version */
#endif /* defined(HAVE_CTIME_R) */
        date[strlen(date)-1]='\0';
        FormatString(buffer,"%%%%CreationDate: (%.1024s)\n",date);
        (void) WriteBlobString(image,buffer);
        bounds.x1=geometry.x;
        bounds.y1=geometry.y;
        bounds.x2=geometry.x+(size_t) geometry.width;
        bounds.y2=geometry.y+(size_t) geometry.height+text_size;
        if (image_info->adjoin && (image->next != (Image *) NULL))
          (void) strcpy(buffer,"%%BoundingBox: (atend)\n");
        else
          FormatString(buffer,"%%%%BoundingBox: %g %g %g %g\n",
            floor(bounds.x1+0.5),floor(bounds.y1+0.5),ceil(bounds.x2-0.5),
            ceil(bounds.y2-0.5));
        (void) WriteBlobString(image,buffer);
        attribute=GetImageAttribute(image,"label");
        if (attribute != (const ImageAttribute *) NULL)
          (void) WriteBlobString(image,
            "%%DocumentNeededResources: font Helvetica\n");
        (void) WriteBlobString(image,"%%LanguageLevel: 2\n");
        if (LocaleCompare(image_info->magick,"PS2") != 0)
          (void) WriteBlobString(image,"%%Pages: 1\n");
        else
          {
            (void) WriteBlobString(image,"%%Orientation: Portrait\n");
            (void) WriteBlobString(image,"%%PageOrder: Ascend\n");
            if (!image_info->adjoin)
              (void) strcpy(buffer,"%%Pages: 1\n");
            else
              FormatString(buffer,"%%%%Pages: %lu\n",(unsigned long)
                image_list_length);
            (void) WriteBlobString(image,buffer);
          }
        (void) WriteBlobString(image,"%%EndComments\n");
        (void) WriteBlobString(image,"\n%%BeginDefaults\n");
        (void) WriteBlobString(image,"%%EndDefaults\n\n");
        /*
          Output Postscript commands.
        */
        {
          const char * ps_compress;

          switch (compression)
          {
          case NoCompression: ps_compress="ASCII85Decode"; break;
            case JPEGCompression: ps_compress="DCTDecode"; break;
            case LZWCompression: ps_compress="LZWDecode"; break;
            case FaxCompression: ps_compress="ASCII85Decode"; break;
            default: ps_compress="RunLengthDecode"; break;
          }
          (void) WriteBlobString(image,
                       "%%BeginProlog\n"
                       "%\n"
                       "% Display a color image.  The image is displayed in color on\n"
                       "% Postscript viewers or printers that support color, otherwise\n"
                       "% it is displayed as grayscale.\n"
                       "%\n"
                       "/DirectClassImage\n");
          FormatString(buffer,
                       "{\n"
                       "  %%\n"
                       "  %% Display a DirectClass image.\n"
                       "  %%\n"
                       "  colorspace 0 eq\n"
                       "  {\n"
                       "    /DeviceRGB setcolorspace\n"
                       "    <<\n"
                       "      /ImageType 1\n"
                       "      /Width columns\n"
                       "      /Height rows\n"
                       "      /BitsPerComponent 8\n"
                       "      /Decode [0 1 0 1 0 1]\n"
                       "      /ImageMatrix [columns 0 0 rows neg 0 rows]\n"
                       "      compression 0 gt\n"
                       "      { /DataSource pixel_stream /%.1024s filter }\n"
                       "      { /DataSource pixel_stream /%.1024s filter } ifelse\n"
                       "    >> image\n"
                       "  }\n",
                       ps_compress, ps_compress);
          (void) WriteBlobString(image,buffer);
          FormatString(buffer,
                       "  {\n"
                       "    /DeviceCMYK setcolorspace\n"
                       "    <<\n"
                       "      /ImageType 1\n"
                       "      /Width columns\n"
                       "      /Height rows\n"
                       "      /BitsPerComponent 8\n"
                       "      /Decode [1 0 1 0 1 0 1 0]\n"
                       "      /ImageMatrix [columns 0 0 rows neg 0 rows]\n"
                       "      compression 0 gt\n"
                       "      { /DataSource pixel_stream /%.1024s filter }\n"
                       "      { /DataSource pixel_stream /%.1024s filter } ifelse\n"
                       "    >> image\n"
                       "  } ifelse\n"
                       "} bind def\n"
                       "\n",
                       ps_compress, ps_compress);
          (void) WriteBlobString(image,buffer);
          FormatString(buffer,
                       "/PseudoClassImage\n"
                       "{\n"
                       "  %%\n"
                       "  %% Display a PseudoClass image.\n"
                       "  %%\n"
                       "  %% Parameters:\n"
                       "  %%   colors: number of colors in the colormap.\n"
                       "  %%\n"
                       "  currentfile buffer readline pop\n"
                       "  token pop /colors exch def pop\n"
                       "  colors 0 eq\n"
                       "  {\n"
                       "    %%\n"
                       "    %% Image is grayscale.\n"
                       "    %%\n"
                       "    currentfile buffer readline pop\n"
                       "    token pop /bits exch def pop\n"
                       "    /DeviceGray setcolorspace\n"
                       "    <<\n"
                       "      /ImageType 1\n"
                       "      /Width columns\n"
                       "      /Height rows\n"
                       "      /BitsPerComponent bits\n"
                       "      /Decode [0 1]\n"
                       "      /ImageMatrix [columns 0 0 rows neg 0 rows]\n"
                       "      compression 0 gt\n"
                       "      { /DataSource pixel_stream /%.1024s filter }\n"
                       "      {\n"
                       "        /DataSource pixel_stream /%.1024s filter\n"
                       "        <<\n"
                       "           /K "CCITTParam"\n"
                       "           /Columns columns\n"
                       "           /Rows rows\n"
                       "        >> /CCITTFaxDecode filter\n"
                       "      } ifelse\n"
                       "    >> image\n"
                       "  }\n",
                       ps_compress, ps_compress);
          (void) WriteBlobString(image,buffer);
          FormatString(buffer,
                       "  {\n"
                       "    %%\n"
                       "    %% Parameters:\n"
                       "    %%   colormap: red, green, blue color packets.\n"
                       "    %%\n"
                       "    /colormap colors 3 mul string def\n"
                       "    currentfile colormap readhexstring pop pop\n"
                       "    currentfile buffer readline pop\n"
                       "    [ /Indexed /DeviceRGB colors 1 sub colormap ] setcolorspace\n"
                       "    <<\n"
                       "      /ImageType 1\n"
                       "      /Width columns\n"
                       "      /Height rows\n"
                       "      /BitsPerComponent 8\n"
                       "      /Decode [0 255]\n"
                       "      /ImageMatrix [columns 0 0 rows neg 0 rows]\n"
                       "      compression 0 gt\n"
                       "      { /DataSource pixel_stream /%.1024s filter }\n"
                       "      { /DataSource pixel_stream /%.1024s filter } ifelse\n"
                       "    >> image\n"
                       "  } ifelse\n"
                       "} bind def\n"
                       "\n",
                       ps_compress, ps_compress);
          (void) WriteBlobString(image,buffer);
          (void) WriteBlobString(image,
                       "/DisplayImage\n"
                       "{\n"
                       "  %\n"
                       "  % Display a DirectClass or PseudoClass image.\n"
                       "  %\n"
                       "  % Parameters:\n"
                       "  %   x & y translation.\n"
                       "  %   x & y scale.\n"
                       "  %   label pointsize.\n"
                       "  %   image label.\n"
                       "  %   image columns & rows.\n"
                       "  %   class: 0-DirectClass or 1-PseudoClass.\n"
                       "  %   colorspace: 0-RGB or 1-CMYK.\n"
                       "  %   compression: 0-RLECompression or 1-NoCompression.\n"
                       "  %   hex color packets.\n"
                       "  %\n"
                       "  gsave\n"
                       "  /buffer 512 string def\n"
                       "  /pixel_stream currentfile def\n"
                       "\n"
                       "  currentfile buffer readline pop\n"
                       "  token pop /x exch def\n"
                       "  token pop /y exch def pop\n"
                       "  x y translate\n"
                       "  currentfile buffer readline pop\n"
                       "  token pop /x exch def\n"
                       "  token pop /y exch def pop\n"
                       "  currentfile buffer readline pop\n"
                       "  token pop /pointsize exch def pop\n"
                       "  /Helvetica findfont pointsize scalefont setfont\n"
               );
        }
        attribute=GetImageAttribute(image,"label");
        if (attribute != (const ImageAttribute *) NULL)
          for (j=(long) MultilineCensus(attribute->value)-1; j >= 0; j--)
          {
            (void) WriteBlobString(image,"  /label 512 string def\n");
            (void) WriteBlobString(image,"  currentfile label readline pop\n");
            FormatString(buffer,"  0 y %g add moveto label show pop\n",
              j*image_info->pointsize+12);
            (void) WriteBlobString(image,buffer);
          }
            (void) WriteBlobString(image,
                                   "  x y scale\n"
                                   "  currentfile buffer readline pop\n"
                                   "  token pop /columns exch def\n"
                                   "  token pop /rows exch def pop\n"
                                   "  currentfile buffer readline pop\n"
                                   "  token pop /class exch def pop\n"
                                   "  currentfile buffer readline pop\n"
                                   "  token pop /colorspace exch def pop\n"
                                   "  currentfile buffer readline pop\n"
                                   "  token pop /compression exch def pop\n"
                                   "  class 0 gt { PseudoClassImage } { DirectClassImage } ifelse\n"
                                   "  grestore\n");
        if (LocaleCompare(image_info->magick,"PS2") == 0)
          (void) WriteBlobString(image,"  showpage\n");
        (void) WriteBlobString(image,"} bind def\n");
        (void) WriteBlobString(image,"%%EndProlog\n");
      }
    FormatString(buffer,"%%%%Page:  1 %lu\n",page++);
    (void) WriteBlobString(image,buffer);
    FormatString(buffer,"%%%%PageBoundingBox: %ld %ld %ld %ld\n",geometry.x,
      geometry.y,geometry.x+(long) geometry.width,geometry.y+(long)
      (geometry.height+text_size));
    (void) WriteBlobString(image,buffer);
    if (geometry.x < bounds.x1)
      bounds.x1=geometry.x;
    if (geometry.y < bounds.y1)
      bounds.y1=geometry.y;
    if ((geometry.x+(size_t) geometry.width-1) > bounds.x2)
      bounds.x2=geometry.x+(size_t) geometry.width-1;
    if ((geometry.y+((size_t) geometry.height+text_size)-1) > bounds.y2)
      bounds.y2=geometry.y+((size_t) geometry.height+text_size)-1;
    attribute=GetImageAttribute(image,"label");
    if (attribute != (const ImageAttribute *) NULL)
      (void) WriteBlobString(image,"%%PageResources: font Times-Roman\n");
    if (LocaleCompare(image_info->magick,"PS2") != 0)
      (void) WriteBlobString(image,"userdict begin\n");
    start=TellBlob(image);
    if (start < 0)
      ThrowWriterException(BlobError,UnableToObtainOffset,image);
    FormatString(buffer,"%%%%BeginData:%13ld %s Bytes\n",0L,
      compression == NoCompression ? "ASCII" : "Binary");
    (void) WriteBlobString(image,buffer);
    stop=TellBlob(image);
    if (stop < 0)
      ThrowWriterException(BlobError,UnableToObtainOffset,image);
    (void) WriteBlobString(image,"DisplayImage\n");
    /*
      Output image data.
    */
    FormatString(buffer,"%ld %ld\n%g %g\n%f\n",geometry.x,geometry.y,
      x_scale,y_scale,image_info->pointsize);
    (void) WriteBlobString(image,buffer);
    labels=(char **) NULL;
    attribute=GetImageAttribute(image,"label");
    if (attribute != (const ImageAttribute *) NULL)
      labels=StringToList(attribute->value);
    if (labels != (char **) NULL)
      {
        for (i=0; labels[i] != (char *) NULL; i++)
        {
          FormatString(buffer,"%.1024s \n",labels[i]);
          (void) WriteBlobString(image,buffer);
          MagickFreeMemory(labels[i]);
        }
        MagickFreeMemory(labels);
      }
    number_pixels=image->columns*image->rows;

    /*
      Analyze image to be written.
    */
    (void) GetImageCharacteristics(image,&characteristics,
                                   (OptimizeType == image_info->type),
                                   &image->exception);
    if ((compression == FaxCompression) ||
        ((image_info->type != TrueColorType) &&
         (characteristics.grayscale)))
      {
        FormatString(buffer,"%lu %lu\n1\n%d\n",image->columns,image->rows,
          (int) (image->colorspace == CMYKColorspace));
        (void) WriteBlobString(image,buffer);
        FormatString(buffer,"%d\n",(int) (compression != FaxCompression));
        (void) WriteBlobString(image,buffer);
        (void) WriteBlobString(image,"0\n");
        FormatString(buffer,"%d\n",compression == FaxCompression ? 1 : 8);
        (void) WriteBlobString(image,buffer);
        switch (compression)
        {
          case FaxCompression:
          {
            if (LocaleCompare(CCITTParam,"0") == 0)
              {
                (void) HuffmanEncodeImage(image_info,image);
                break;
              }
            (void) Huffman2DEncodeImage(image_info,image);
            break;
          }
          case JPEGCompression:
          {
            /*
              Write image in JPEG format.
            */
            blob=ImageToJPEGBlob(image,image_info,&length,&image->exception);
            if (blob == (char *) NULL)
              ThrowWriterException2(CoderError,image->exception.reason,image);
            (void) WriteBlob(image,length,blob);
            MagickFreeMemory(blob);
            break;
          }
          case RLECompression:
          default:
          {
            register unsigned char
              *q;

            /*
              Allocate pixel array.
            */
            length=number_pixels;
            pixels=MagickAllocateResourceLimitedMemory(unsigned char *,length);
            if (pixels == (unsigned char *) NULL)
              ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,
                image);
            /*
              Dump Runlength encoded pixels.
            */
            q=pixels;
            for (y=0; y < (long) image->rows; y++)
            {
              p=AcquireImagePixels(image,0,y,image->columns,1,
                &image->exception);
              if (p == (const PixelPacket *) NULL)
                break;
              for (x=0; x < (long) image->columns; x++)
              {
                *q++=ScaleQuantumToChar(PixelIntensityToQuantum(p));
                p++;
              }
              if (image->previous == (Image *) NULL)
                if (QuantumTick(y,image->rows))
                  {
                    status=MagickMonitorFormatted(y,image->rows,
                                                  &image->exception,
                                                  SaveImageText,
                                                  image->filename,
                                                  image->columns,image->rows);
                    if (status == False)
                      break;
                  }
            }
            if (compression == LZWCompression)
              status=LZWEncodeImage(image,length,pixels);
            else
              status=PackbitsEncodeImage(image,length,pixels);
            MagickFreeResourceLimitedMemory(pixels);
            if (!status)
              {
                CloseBlob(image);
                return(False);
              }
            break;
          }
          case NoCompression:
          {
            /*
              Dump uncompressed PseudoColor packets.
            */
            Ascii85Initialize(image);
            for (y=0; y < (long) image->rows; y++)
            {
              p=AcquireImagePixels(image,0,y,image->columns,1,
                &image->exception);
              if (p == (const PixelPacket *) NULL)
                break;
              for (x=0; x < (long) image->columns; x++)
              {
                Ascii85Encode(image,
                  ScaleQuantumToChar(PixelIntensityToQuantum(p)));
                p++;
              }
              if (image->previous == (Image *) NULL)
                if (QuantumTick(y,image->rows))
                  {
                    status=MagickMonitorFormatted(y,image->rows,
                                                  &image->exception,
                                                  SaveImageText,
                                                  image->filename,
                                                  image->columns,image->rows);
                    if (status == False)
                      break;
                  }
            }
            Ascii85Flush(image);
            break;
          }
        }
      }
    else
      if ((image->storage_class == DirectClass) || (image->colors > 256) ||
          (compression == JPEGCompression))
        {
          FormatString(buffer,"%lu %lu\n0\n%d\n",image->columns,image->rows,
            (int) (image->colorspace == CMYKColorspace));
          (void) WriteBlobString(image,buffer);
          FormatString(buffer,"%d\n",(int) (compression == NoCompression));
          (void) WriteBlobString(image,buffer);
          switch (compression)
          {
            case JPEGCompression:
            {
              /*
                Write image in JPEG format.
              */
              blob=ImageToJPEGBlob(image,image_info,&length,&image->exception);
              if (blob == (char *) NULL)
                ThrowWriterException2(CoderError,image->exception.reason,image);
              (void) WriteBlob(image,length,blob);
              MagickFreeMemory(blob);
              break;
            }
            case RLECompression:
            default:
            {
              register unsigned char
                *q;

              /*
                Allocate pixel array.
              */
              length=MagickArraySize(image->colorspace == CMYKColorspace ? 4 : 3,
                number_pixels);
              pixels=MagickAllocateResourceLimitedMemory(unsigned char *,length);
              if (pixels == (unsigned char *) NULL)
                ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);
              /*
                Dump Packbit encoded pixels.
              */
              q=pixels;
              for (y=0; y < (long) image->rows; y++)
              {
                p=AcquireImagePixels(image,0,y,image->columns,1,
                  &image->exception);
                if (p == (const PixelPacket *) NULL)
                  break;
                for (x=0; x < (long) image->columns; x++)
                {
                  if (image->matte && (p->opacity == TransparentOpacity))
                    {
                      *q++=ScaleQuantumToChar(MaxRGB);
                      *q++=ScaleQuantumToChar(MaxRGB);
                      *q++=ScaleQuantumToChar(MaxRGB);
                    }
                  else
                    if (image->colorspace != CMYKColorspace)
                      {
                        *q++=ScaleQuantumToChar(p->red);
                        *q++=ScaleQuantumToChar(p->green);
                        *q++=ScaleQuantumToChar(p->blue);
                      }
                    else
                      {
                        *q++=ScaleQuantumToChar(p->red);
                        *q++=ScaleQuantumToChar(p->green);
                        *q++=ScaleQuantumToChar(p->blue);
                        *q++=ScaleQuantumToChar(p->opacity);
                      }
                  p++;
                }
                if (image->previous == (Image *) NULL)
                  if (QuantumTick(y,image->rows))
                    {
                      status=MagickMonitorFormatted(y,image->rows,
                                                    &image->exception,
                                                    SaveImageText,
                                                    image->filename,
                                                    image->columns,image->rows);
                      if (status == False)
                        break;
                    }
              }
              if (compression == LZWCompression)
                status=LZWEncodeImage(image,length,pixels);
              else
                status=PackbitsEncodeImage(image,length,pixels);
              if (!status)
                {
                  CloseBlob(image);
                  return(False);
                }
              MagickFreeResourceLimitedMemory(pixels);
              break;
            }
            case NoCompression:
            {
              /*
                Dump uncompressed DirectColor packets.
              */
              Ascii85Initialize(image);
              for (y=0; y < (long) image->rows; y++)
              {
                p=AcquireImagePixels(image,0,y,image->columns,1,
                  &image->exception);
                if (p == (const PixelPacket *) NULL)
                  break;
                for (x=0; x < (long) image->columns; x++)
                {
                  if (image->matte && (p->opacity == TransparentOpacity))
                    {
                      Ascii85Encode(image,ScaleQuantumToChar(MaxRGB));
                      Ascii85Encode(image,ScaleQuantumToChar(MaxRGB));
                      Ascii85Encode(image,ScaleQuantumToChar(MaxRGB));
                    }
                  else
                    if (image->colorspace != CMYKColorspace)
                      {
                        Ascii85Encode(image,ScaleQuantumToChar(p->red));
                        Ascii85Encode(image,ScaleQuantumToChar(p->green));
                        Ascii85Encode(image,ScaleQuantumToChar(p->blue));
                      }
                    else
                      {
                        Ascii85Encode(image,ScaleQuantumToChar(p->red));
                        Ascii85Encode(image,ScaleQuantumToChar(p->green));
                        Ascii85Encode(image,ScaleQuantumToChar(p->blue));
                        Ascii85Encode(image,ScaleQuantumToChar(p->opacity));
                      }
                  p++;
                }
                if (image->previous == (Image *) NULL)
                  if (QuantumTick(y,image->rows))
                    {
                      status=MagickMonitorFormatted(y,image->rows,
                                                    &image->exception,
                                                    SaveImageText,
                                                    image->filename,
                                                    image->columns,image->rows);
                      if (status == False)
                        break;
                    }
              }
              Ascii85Flush(image);
              break;
            }
          }
        }
      else
        {
          /*
            Dump number of colors and colormap.
          */
          FormatString(buffer,"%lu %lu\n1\n%d\n",image->columns,image->rows,
            (int) (image->colorspace == CMYKColorspace));
          (void) WriteBlobString(image,buffer);
          FormatString(buffer,"%d\n",(int) (compression == NoCompression));
          (void) WriteBlobString(image,buffer);
          FormatString(buffer,"%u\n",image->colors);
          (void) WriteBlobString(image,buffer);
          for (i=0; i < (long) image->colors; i++)
          {
            FormatString(buffer,"%02X%02X%02X\n",
              ScaleQuantumToChar(image->colormap[i].red),
              ScaleQuantumToChar(image->colormap[i].green),
              ScaleQuantumToChar(image->colormap[i].blue));
            (void) WriteBlobString(image,buffer);
          }
          switch (compression)
          {
            case RLECompression:
            default:
            {
              register unsigned char
                *q;

              /*
                Allocate pixel array.
              */
              length=number_pixels;
              pixels=MagickAllocateResourceLimitedMemory(unsigned char *,length);
              if (pixels == (unsigned char *) NULL)
                ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);
              /*
                Dump Runlength encoded pixels.
              */
              q=pixels;
              for (y=0; y < (long) image->rows; y++)
              {
                p=AcquireImagePixels(image,0,y,image->columns,1,
                  &image->exception);
                if (p == (const PixelPacket *) NULL)
                  break;
                indexes=AccessImmutableIndexes(image);
                for (x=0; x < (long) image->columns; x++)
                  *q++=indexes[x];
                if (image->previous == (Image *) NULL)
                  if (QuantumTick(y,image->rows))
                    {
                      status=MagickMonitorFormatted(y,image->rows,
                                                    &image->exception,
                                                    SaveImageText,
                                                    image->filename,
                                                    image->columns,image->rows);
                      if (status == False)
                        break;
                    }
              }
              if (compression == LZWCompression)
                status=LZWEncodeImage(image,length,pixels);
              else
                status=PackbitsEncodeImage(image,length,pixels);
              MagickFreeResourceLimitedMemory(pixels);
              if (!status)
                {
                  CloseBlob(image);
                  return(False);
                }
              break;
            }
            case NoCompression:
            {
              /*
                Dump uncompressed PseudoColor packets.
              */
              Ascii85Initialize(image);
              for (y=0; y < (long) image->rows; y++)
              {
                p=AcquireImagePixels(image,0,y,image->columns,1,
                  &image->exception);
                if (p == (const PixelPacket *) NULL)
                  break;
                indexes=AccessImmutableIndexes(image);
                for (x=0; x < (long) image->columns; x++)
                  Ascii85Encode(image,indexes[x]);
                if (image->previous == (Image *) NULL)
                  if (QuantumTick(y,image->rows))
                    {
                      status=MagickMonitorFormatted(y,image->rows,
                                                    &image->exception,
                                                    SaveImageText,
                                                    image->filename,
                                                    image->columns,image->rows);
                      if (status == False)
                        break;
                    }
              }
              Ascii85Flush(image);
              break;
            }
          }
        }
    (void) WriteBlobByte(image,'\n');
    current=TellBlob(image);
    if (current < 0)
      ThrowWriterException(BlobError,UnableToObtainOffset,image);
    length=current-stop;
    stop=TellBlob(image);
    if (stop < 0)
      ThrowWriterException(BlobError,UnableToObtainOffset,image);
    if (SeekBlob(image,start,SEEK_SET) != start)
      ThrowWriterException(BlobError,UnableToSeekToOffset,image);
    FormatString(buffer,"%%%%BeginData:%13ld %s Bytes\n",(long) length,
      compression == NoCompression ? "ASCII" : "Binary");
    (void) WriteBlobString(image,buffer);
    if (SeekBlob(image,stop,SEEK_SET) != stop)
      ThrowWriterException(BlobError,UnableToSeekToOffset,image);
    (void) WriteBlobString(image,"%%EndData\n");
    if (LocaleCompare(image_info->magick,"PS2") != 0)
      (void) WriteBlobString(image,"end\n");
    (void) WriteBlobString(image,"%%PageTrailer\n");
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
  (void) WriteBlobString(image,"%%Trailer\n");
  if (page > 1)
    {
      FormatString(buffer,"%%%%BoundingBox: %g %g %g %g\n",floor(bounds.x1+0.5),
        floor(bounds.y1+0.5),ceil(bounds.x2-0.5),ceil(bounds.y2-0.5));
      (void) WriteBlobString(image,buffer);
    }
  (void) WriteBlobString(image,"%%EOF\n");
  CloseBlob(image);
  return(True);
}
