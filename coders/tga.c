/*
% Copyright (C) 2003 - 2023 GraphicsMagick Group
% Copyright (C) 2002 - 2022 ImageMagick Studio
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
%                            TTTTT   GGGG   AAA                               %
%                              T    G      A   A                              %
%                              T    G  GG  AAAAA                              %
%                              T    G   G  A   A                              %
%                              T     GGG   A   A                              %
%                                                                             %
%                                                                             %
%                   Read/Write Truevision Targa Image Format.                 %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
%                              Jaroslav Fojtik                                %
%                                   2022                                      %
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
#include "magick/colormap.h"
#include "magick/enum_strings.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"

/*
  Forward declarations.
*/
static unsigned int
  WriteTGAImage(const ImageInfo *,Image *);


#define TGAColormap 1U         /* Colormapped image data */
#define TGARGB 2U              /* Truecolor image data */
#define TGAMonochrome 3U       /* Monochrome image data */
#define TGARLEColormap  9U     /* Colormapped image data (encoded) */
#define TGARLERGB  10U         /* Truecolor image data (encoded) */
#define TGARLEMonochrome  11U  /* Monochrome image data (encoded) */

typedef struct _TGAInfo
{
  unsigned int
    id_length,       /* (U8) Size of Image ID field (starting after header) */
    colormap_type,   /* (U8) Color map type */
    image_type;      /* (U8) Image type code */

  unsigned int
    colormap_index,  /* (U16) Color map origin */
    colormap_length; /* (U16) Color map length */

  unsigned int
    colormap_size;   /* (U8) Color map entry depth */

  unsigned int
    x_origin,        /* (U16) X origin of image */
    y_origin,        /* (U16) Y orgin of image */
    width,           /* (U16) Width of image */
    height;          /* (U16) Height of image */

  unsigned int
    bits_per_pixel,  /* (U8) Image pixel size */
    attributes;      /* (U8) Image descriptor byte (see below) */
} TGAInfo;

/*
  Image descriptor byte decode:

  Bits 0 through 3 specify the number of attribute bits per pixel.

  Bits 5 and 4 contain the image origin location.  These bits are used
  to indicate the order in which pixel data is transferred from the
  file to the screen.  Bit 4 is for left-to-right ordering, and bit 5
  is for top-to-bottom ordering as shown below:

    00 (0) - Bottom Left
    10 (2) - Top Left
    01 (1) - Bottom Right
    11 (3) - Top Right

    Screen destination  | Image Origin
    of first pixel      | Bit 5 | Bit 4
    --------------------+-------+------
    Bottom left         |   0   |   0
    Bottom right        |   0   |   1
    Top left            |   1   |   0
    Top right           |   1   |   1
*/


typedef struct _TGAFooter
{
  magick_uint32_t ExtensionOffset;
  magick_uint32_t DeveloperDirOffset;
  char Signature[16+1];               /* 16 official bytes + zero terminator. */
  char Dot;
  char Terminator;
} TGAFooter;


typedef struct _TGADevel
{
    magick_uint16_t ExtensionSize;
    char Author[41];
    char Comments[324+1];
    magick_uint16_t TimeStamp[6];
    magick_uint16_t JobTime[3];
    char JobNameID[41+1];                       /* The last byte must be a binary zero. */
    char SoftwareID[41];
    magick_uint16_t VersionNumber;
    unsigned char VersionLetter;
    unsigned char KeyColor[4];                  /* A:R:G:B */
    magick_uint16_t AspectRatio[2];
    magick_uint16_t Gamma[2];
    magick_uint32_t ColorCorrectionOffset;
    magick_uint32_t PostageStampOffset;
    magick_uint32_t ScanLineOffset;
    unsigned char AttributesType;       /* 0: no Alpha; 1 undefined useless data in the Alpha;
                                           2: undefined data in the Alpha might be retained;
                                           3 useful Alpha channel; 4: pre-multiplied Alpha */
    /* Scan Line Table - Field 25 (Variable) */
    /* Postage Stamp Image - Field 26 (Variable) */
    /* Color Correction Table - Field 27 (2K Bytes) */
} TGADevel;


static void LogTGAInfo(const TGAInfo *tga_info)
{
  OrientationType orientation = UndefinedOrientation;
  unsigned int attribute_bits;

  attribute_bits = tga_info->attributes & 0xf;

  switch((tga_info->attributes >> 4) & 3)
    {
    case 0:
      orientation=BottomLeftOrientation;
      break;
    case 1:
      orientation=BottomRightOrientation;
      break;
    case 2:
      orientation=TopLeftOrientation;
      break;
    case 3:
      orientation=TopRightOrientation;
      break;
    }

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Targa Header:\n"
                        "    ImageType  : %s\n"
                        "    CMapType   : %u\n"
                        "    CMapStart  : %u\n"
                        "    CMapLength : %u\n"
                        "    CMapDepth  : %u\n"
                        "    XOffset    : %u\n"
                        "    YOffset    : %u\n"
                        "    Width      : %u\n"
                        "    Height     : %u\n"
                        "    PixelDepth : %u\n"
                        "    Attributes : 0x%.2x (AttributeBits: %u, Orientation: %s)",
                        ((tga_info->image_type == TGAColormap) ? "Colormapped" :
                         (tga_info->image_type == TGARGB) ? "TrueColor" :
                         (tga_info->image_type == TGAMonochrome) ? "Monochrome" :
                         (tga_info->image_type == TGARLEColormap) ? "Colormapped-RLE" :
                         (tga_info->image_type == TGARLERGB) ? "Truecolor-RLE" :
                         (tga_info->image_type == TGARLEMonochrome) ? "Monochrome-RLE" :
                         "Unknown"),
                        (unsigned int) tga_info->colormap_type,   /* Colormap type */
                        (unsigned int) tga_info->colormap_index,  /* Index of first colormap entry to use */
                        (unsigned int) tga_info->colormap_length, /* # of elements in colormap */
                        (unsigned int) tga_info->colormap_size,   /* Bits in each palette entry */
                        tga_info->x_origin, tga_info->y_origin,
                        tga_info->width, tga_info->height,
                        (unsigned int) tga_info->bits_per_pixel,
                        tga_info->attributes,attribute_bits,OrientationTypeToString(orientation));
}


static void LogTGAFooter(const TGAFooter *ptga_footer)
{
 (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Targa Footer:\n"
                        "    ExtensionOffset     : %u\n"
                        "    DeveloperDirOffset : %u\n"
                        "    Signature           : %s",
                               ptga_footer->ExtensionOffset,
                               ptga_footer->DeveloperDirOffset,
                               ptga_footer->Signature);
}


static void LogTGADevel(const TGADevel *ptga_devel)
{
 (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Targa Extension Area:\n"
                        "    Extension Size      : %u\n"
                        "    Author Name         : %s\n"
                        "    Author Comments     : %s\n"
                        "    Date/Time Stamp     : %u/%u/%u %u:%u:%u\n"
                        "    Job Name/ID         : %s\n"
                        "    Job Time            : %u:%u:%u\n"
                        "    Software ID         : %s\n"
                        "    Software Version    : %u.%u\n"
                        "    Key Color           : A=%u R=%u G=%u B=%u\n"
                        "    Pixel Aspect Ratio  : %u x %u\n"
                        "    Gamma               : %u x %u\n"
                        "    Color Correction Offset: %u\n"
                        "    Postage Stamp Offset: %u\n"
                        "    Scan Line Offset    : %u\n"
                        "    Attributes Type     : %u",
                               ptga_devel->ExtensionSize,
                               ptga_devel->Author,
                               ptga_devel->Comments,
                               ptga_devel->TimeStamp[0], ptga_devel->TimeStamp[1], ptga_devel->TimeStamp[2],
                               ptga_devel->TimeStamp[3], ptga_devel->TimeStamp[4], ptga_devel->TimeStamp[5],
                               ptga_devel->JobNameID,
                               ptga_devel->JobTime[0], ptga_devel->JobTime[1], ptga_devel->JobTime[2],
                               ptga_devel->SoftwareID,
                               ptga_devel->VersionNumber, (unsigned)ptga_devel->VersionLetter,
                               ptga_devel->KeyColor[0], ptga_devel->KeyColor[1], ptga_devel->KeyColor[2], ptga_devel->KeyColor[3],
                               ptga_devel->AspectRatio[0], ptga_devel->AspectRatio[1],
                               ptga_devel->Gamma[0], ptga_devel->Gamma[1],
                               ptga_devel->ColorCorrectionOffset,
                               ptga_devel->PostageStampOffset,
                               ptga_devel->ScanLineOffset,
                               (unsigned)ptga_devel->AttributesType);
}


static int LoadHeaderTGA(TGAInfo *tga_info, Image *image)
{
  tga_info->id_length = ReadBlobByte(image);
  tga_info->colormap_type = ReadBlobByte(image);
  tga_info->image_type = ReadBlobByte(image);

  tga_info->colormap_index = ReadBlobLSBShort(image);
  tga_info->colormap_length = ReadBlobLSBShort(image) & 0xFFFF;
  tga_info->colormap_size = ReadBlobByte(image);
  tga_info->x_origin = ReadBlobLSBShort(image);
  tga_info->y_origin = ReadBlobLSBShort(image);
  tga_info->width = ReadBlobLSBShort(image) & 0xFFFF;
  tga_info->height = ReadBlobLSBShort(image) & 0xFFFF;
  tga_info->bits_per_pixel = ReadBlobByte(image);
  tga_info->attributes = ReadBlobByte(image);
  return 0;
}



static int ValidateHeaderTGA(const TGAInfo *tga_info)
{
  if (((tga_info->image_type != TGAColormap) &&
       (tga_info->image_type != TGARGB) &&
       (tga_info->image_type != TGAMonochrome) &&
       (tga_info->image_type != TGARLEColormap) &&
       (tga_info->image_type != TGARLERGB) &&
       (tga_info->image_type != TGARLEMonochrome)) ||
      (((tga_info->image_type == TGAColormap) ||
        (tga_info->image_type == TGARLEColormap)) &&
       (tga_info->colormap_type == 0))) return -1;
  return 0;
}


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d T G A I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadTGAImage reads a Truevision TGA image file and returns it.
%  It allocates the memory necessary for the new Image structure and returns
%  a pointer to the new image.
%
%  The format of the ReadTGAImage method is:
%
%      Image *ReadTGAImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadTGAImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
*/
static Image *ReadTGAImage(const ImageInfo *image_info, ExceptionInfo *exception)
{
  Image
    *image;

  unsigned int
    index;

  long
    y;

  PixelPacket
    pixel;

  register IndexPacket
    *indexes;

  register long
    i,
    x;

  register PixelPacket
    *q;

  TGAInfo
    tga_info;

  TGAFooter
    tga_footer;

  TGADevel
    tga_devel;

  unsigned char
    runlength;

  unsigned int
    alpha_bits,
    status;

  unsigned long
    base,
    flag,
    offset,
    real,
    skip;

  unsigned int
    is_grayscale=MagickFalse;

  unsigned char
    readbuffer[4];

  char
    CommentAndBuffer[256];

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  image = AllocateImage(image_info);
  status = OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFalse)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);

  /*
    Read TGA footer - if exists.
  */
  memset(&tga_footer, 0, sizeof(tga_footer));
  memset(&tga_devel, 0, sizeof(tga_devel));
  if (BlobIsSeekable(image))
    {
      if (SeekBlob(image,-26, SEEK_END) >= 3+15)
        {
          status = MagickTrue;
          tga_footer.ExtensionOffset = ReadBlobLSBLong(image);
          tga_footer.DeveloperDirOffset = ReadBlobLSBLong(image);
          if (ReadBlob(image, 16, tga_footer.Signature) != 16)
            status=MagickFail;
          else
            {
              if ((tga_footer.Dot=ReadBlobByte(image)) != '.')
                status=MagickFail;
              if ((tga_footer.Terminator=ReadBlobByte(image)) != 0)
                status=MagickFail;
            }

          if (status == MagickTrue)
            {
              if (image->logging)
                LogTGAFooter(&tga_footer);
              if (strncmp(tga_footer.Signature,"TRUEVISION-XFILE",16))
                status=MagickFail;
            }
          if (status != MagickTrue)  /* Footer is invalid. */
            {
              memset(&tga_footer, 0, sizeof(tga_footer));
            }

          if (tga_footer.ExtensionOffset > 3)
            {
              if (SeekBlob(image,tga_footer.ExtensionOffset,SEEK_SET) == tga_footer.ExtensionOffset)
                {
                  tga_devel.ExtensionSize = ReadBlobLSBShort(image);
                  if (tga_devel.ExtensionSize >= 495)
                    {
                      if (ReadBlob(image, 41, tga_devel.Author) != 41)
                        status=MagickFail;
                      if (tga_devel.Author[40] != 0)
                        tga_devel.Author[40]=0;
                      if (ReadBlob(image, 324, tga_devel.Comments) != 324)
                        status=MagickFail;
                      if (tga_devel.Comments[323] != 0)
                        tga_devel.Comments[323]=0;
                      for (i=0; i<6; i++)
                        {
                          tga_devel.TimeStamp[i] = ReadBlobLSBShort(image);
                        }
                      if (ReadBlob(image, 41, tga_devel.JobNameID) != 41)
                        status=MagickFail;
                      if (tga_devel.JobNameID[40] != 0)
                        tga_devel.JobNameID[40]=0;
                      for (i=0; i<3; i++)
                        {
                          tga_devel.JobTime[i] = ReadBlobLSBShort(image);
                        }
                      if (ReadBlob(image, 41, tga_devel.SoftwareID) != 41)
                        status=MagickFail;
                      if (tga_devel.SoftwareID[40] != 0)
                        tga_devel.SoftwareID[40]=0;
                      tga_devel.VersionNumber = ReadBlobLSBShort(image);
                      tga_devel.VersionLetter = ReadBlobByte(image);
                      if (ReadBlob(image, 4, tga_devel.KeyColor) != 4)
                        status=MagickFail;
                      for (i=0; i<2; i++)
                        {
                          tga_devel.AspectRatio[i] = ReadBlobLSBShort(image);
                        }
                      for (i=0; i<2; i++)
                        {
                          tga_devel.Gamma[i] = ReadBlobLSBShort(image);
                        }
                      tga_devel.ColorCorrectionOffset = ReadBlobLSBLong(image);
                      tga_devel.PostageStampOffset = ReadBlobLSBLong(image);
                      tga_devel.ScanLineOffset = ReadBlobLSBLong(image);
                      tga_devel.AttributesType = ReadBlobByte(image);

                      if (image->logging)
                        LogTGADevel(&tga_devel);
                      if (status == MagickTrue)    /* TGA devel is valid */
                        {
                          if (tga_devel.Comments[0] != 0)
                            SetImageAttribute(image, "TGA:file.comment", tga_devel.Comments);
                          if (tga_devel.Author[0] != 0)
                            SetImageAttribute(image, "creator", tga_devel.Author);
                          if (tga_devel.SoftwareID[0] != 0)
                            SetImageAttribute(image, "software", tga_devel.SoftwareID);
                          if (tga_devel.JobNameID[0] != 0)
                            SetImageAttribute(image, "TGA:file.JobName", tga_devel.JobNameID);
                        }
                      else
                        {
                          tga_devel.ExtensionSize = 0;      /* Invalidate TGA developper area. */
                        }
                    }
                }
            }
        }

      status = MagickTrue;
      if (SeekBlob(image,0,SEEK_SET) != 0)
        {
          ThrowReaderException(BlobError,UnableToSeekToOffset,image);
        }
    }

  /*
    Read TGA header information.
  */
  if (LoadHeaderTGA(&tga_info, image) < 0)
    ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);

  if (ValidateHeaderTGA(&tga_info) < 0)
    ThrowReaderException(CorruptImageError,ImproperImageHeader,image);

  do
    {
      if (image->logging)
        LogTGAInfo(&tga_info);

      if (EOFBlob(image))
        ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);

      /*
        Validate depth.
      */
      if (!(((tga_info.bits_per_pixel > 1) && (tga_info.bits_per_pixel < 17)) ||
            (tga_info.bits_per_pixel == 24 ) || (tga_info.bits_per_pixel == 32) ||
            (tga_info.bits_per_pixel == 1 && tga_info.image_type == TGAMonochrome) ))
        ThrowReaderException(CoderError,DataStorageTypeIsNotSupported,image);

      /*
        Initialize image structure.
      */
      alpha_bits = (tga_info.attributes & 0x0FU);
      image->matte = ((alpha_bits > 0) || (tga_info.bits_per_pixel == 32));
      if (image->matte)
        {
          if (tga_footer.ExtensionOffset > 3 && tga_devel.ExtensionSize >= 495) /* Valid footer and extended area. */
            {                                       /* Please note that alpha channel could contain a garbage. */
              if (tga_devel.AttributesType < 3 || tga_devel.AttributesType > 4)
                image->matte = MagickFalse;       /* The attribute instruct NOT to use alpha channel. */
            }
        }
      image->columns = tga_info.width;
      image->rows = tga_info.height;
      if ((tga_info.image_type != TGAColormap) && (tga_info.image_type != TGARLEColormap))
        {
          /*
            TrueColor Quantum Depth
          */
          image->depth=((tga_info.bits_per_pixel <= 8) ? 8 :
                        (tga_info.bits_per_pixel <= 16) ? 5 : 8);
        }
      else
        {
          /*
            ColorMapped Palette Entry Quantum Depth
          */
          image->depth=((tga_info.colormap_size <= 8) ? 8 :
                        (tga_info.colormap_size <= 16) ? 5 : 8);
        }

      image->storage_class=DirectClass;

      if ((tga_info.image_type == TGAColormap) ||
          (tga_info.image_type == TGAMonochrome) ||
          (tga_info.image_type == TGARLEColormap) ||
          (tga_info.image_type == TGARLEMonochrome))
        {
          if ((tga_info.bits_per_pixel == 1) || (tga_info.bits_per_pixel == 8))
            {
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),"Setting PseudoClass");
              image->storage_class=PseudoClass;
            }
          else
            {
              ThrowReaderException(CoderError,DataStorageTypeIsNotSupported,image);
            }
        }

      if ((tga_info.image_type == TGARLEColormap) ||
          (tga_info.image_type == TGARLEMonochrome))
        image->compression=RLECompression;

      is_grayscale=((tga_info.image_type == TGAMonochrome) ||
                    (tga_info.image_type == TGARLEMonochrome));

      if (image->storage_class == PseudoClass)
        {
          if (tga_info.colormap_type != 0)
            {
              image->colors=tga_info.colormap_length;
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Using existing colormap with %u colors.",image->colors);
              if (tga_info.bits_per_pixel==1 && image->colors<=1)
                ThrowReaderException(CoderError,ColorTypeNotSupported,image);
            }
          else
            {
              /*
                Apply grayscale colormap.
              */
              image->colors=(0x01U << tga_info.bits_per_pixel);
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Applying grayscale colormap with %u colors.",image->colors);
            }
          if (!AllocateImageColormap(image,image->colors))
            ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,
                                 image);
        }

      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "StorageClass=%s Matte=%s Depth=%u Grayscale=%s",
                            ((image->storage_class == DirectClass) ? "DirectClass" : "PseduoClass"),
                            MagickBoolToString(image->matte), image->depth,
                            MagickBoolToString(is_grayscale));

      if (tga_info.id_length != 0)
        {
          /*
            TGA image comment.
          */
          if (ReadBlob(image,tga_info.id_length,CommentAndBuffer) != tga_info.id_length)
            ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
          CommentAndBuffer[tga_info.id_length]='\0';
          (void) SetImageAttribute(image,"comment",CommentAndBuffer);
        }
      (void) memset(&pixel,0,sizeof(PixelPacket));
      pixel.opacity=TransparentOpacity;
      if (tga_info.colormap_type != 0)
        {
          /*
            Read TGA raster colormap.
          */
          for (i=0; i < (long) image->colors; i++)
            {
              switch (tga_info.colormap_size)
                {
                case 8:
                default:
                  {
                    /*
                      Gray scale.
                    */
                    pixel.red=ScaleCharToQuantum(ReadBlobByte(image));
                    pixel.green=pixel.red;
                    pixel.blue=pixel.red;
                    break;
                  }
                case 15:
                case 16:
                  {
                    /*
                      5 bits each of red green and blue.
                    */
                    const magick_uint16_t packet = ReadBlobLSBShort(image);
                    pixel.red = (packet >> 10) & 0x1f;
                    pixel.red = ScaleCharToQuantum(ScaleColor5to8(pixel.red));
                    pixel.green = (packet >> 5) & 0x1f;
                    pixel.green = ScaleCharToQuantum(ScaleColor5to8(pixel.green));
                    pixel.blue = packet & 0x1f;
                    pixel.blue = ScaleCharToQuantum(ScaleColor5to8(pixel.blue));
                    break;
                  }
                case 24:
                case 32:                        /* TODO: J.Fojtik - is this true? 32 bits, but only 24 bits read. Possible bug! */
                  {
                    /*
                      8 bits each of blue, green and red.
                    */
                    if (ReadBlob(image, 3, readbuffer) != 3)
                      ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
                    pixel.blue = ScaleCharToQuantum(readbuffer[0]);
                    pixel.green = ScaleCharToQuantum(readbuffer[1]);
                    pixel.red = ScaleCharToQuantum(readbuffer[2]);
                    break;
                  }
                }
              image->colormap[i]=pixel;
            }
        }
      if (EOFBlob(image))
        ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
      if (image_info->ping && (image_info->subrange != 0))
        if (image->scene >= (image_info->subimage+image_info->subrange-1))
          break;

      if (CheckImagePixelLimits(image, exception) != MagickPass)
        ThrowReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);

      /*
        Convert TGA pixels to pixel packets.
      */
      base=0;
      flag=0;
      skip=MagickFalse;
      real=0;
      index=0;
      runlength=0;
      offset=0;
      pixel.opacity=OpaqueOpacity;
      for (y=0; y < (long) image->rows; y++)
        {
          real=offset;
          if (((tga_info.attributes & 0x20) >> 5) == 0)
            real=image->rows-real-1;
          q=SetImagePixels(image,0,(long) real,image->columns,1);
          if (q == (PixelPacket *) NULL)
            break;
          indexes=AccessMutableIndexes(image);
          for (x=0; x < (long)image->columns; x++)
            {
              if ((tga_info.image_type == TGARLEColormap) ||
                  (tga_info.image_type == TGARLERGB) ||
                  (tga_info.image_type == TGARLEMonochrome))  /* J.F. THIS WILLL NOT WORK! Some image sample should be obtained. */
                {
                  if (runlength != 0)
                    {
                      runlength--;
                      skip=flag != 0;
                    }
                  else
                    {
                      if (ReadBlob(image,1,(char *) &runlength) != 1)
                        {
                          status=MagickFail;
                          break;
                        }
                      flag=runlength & 0x80;
                      if (flag != 0)
                        runlength-=128;
                      skip=MagickFalse;
                    }
                }
              if (!skip)
                switch (tga_info.bits_per_pixel)
                  {
                  case 1:
                    if ((x&7) == 0)     // Read byte every 8th bit.
                      index = ReadBlobByte(image);
                    else
                      index <<= 1;
                    if (image->storage_class == PseudoClass)
                      {
                        pixel = image->colormap[indexes[x] = ((index & 128) ? 1 : 0)];
                      }
                    else
                      {
                        pixel.blue=pixel.green=pixel.red = (index & 128) ? MaxRGB : 0;
                      }
                    break;

                  case 8:
                  default:
                    {
                      /*
                        Gray scale.
                      */
                      index = ReadBlobByte(image);
                      if (image->storage_class == PseudoClass)
                        {
                          VerifyColormapIndex(image,index);
                          pixel=image->colormap[index];
                          indexes[x] = index;
                        }
                      else
                        {
                          pixel.blue=pixel.green=pixel.red=ScaleCharToQuantum(index);
                        }
                      break;
                    }
                  case 15:
                  case 16:
                    {
                      /*
                        5 bits each of red green and blue.
                      */
                      const magick_uint16_t packet = ReadBlobLSBShort(image);

                      pixel.red = (packet >> 10) & 0x1f;
                      pixel.red = ScaleCharToQuantum(ScaleColor5to8(pixel.red));
                      pixel.green = (packet >> 5) & 0x1f;
                      pixel.green = ScaleCharToQuantum(ScaleColor5to8(pixel.green));
                      pixel.blue = packet & 0x1f;
                      pixel.blue = ScaleCharToQuantum(ScaleColor5to8(pixel.blue));
                      if (image->matte)
                        {
                          if ((packet >> 15) & 0x01)
                            pixel.opacity=OpaqueOpacity;
                          else
                            pixel.opacity=TransparentOpacity;
                        }

                      if (image->storage_class == PseudoClass)
                        {
                          index=(IndexPacket) (packet & 0x7fff);
                          VerifyColormapIndex(image,index);
                        }
                      break;
                    }
                  case 24:
                    /*
                      8 bits each of blue green and red.
                    */
                    if (ReadBlob(image, 3, readbuffer) != 3)
                      {
                        status=MagickFail;
                        break;
                      }
                    pixel.blue = ScaleCharToQuantum(readbuffer[0]);
                    pixel.green = ScaleCharToQuantum(readbuffer[1]);
                    pixel.red = ScaleCharToQuantum(readbuffer[2]);
                    break;
                  case 32:
                    {
                      /*
                        8 bits each of blue green and red.
                      */
                      if (ReadBlob(image, 4, readbuffer) != 4)
                        {
                          status=MagickFail;
                          break;
                        }
                      pixel.blue = ScaleCharToQuantum(readbuffer[0]);
                      pixel.green = ScaleCharToQuantum(readbuffer[1]);
                      pixel.red = ScaleCharToQuantum(readbuffer[2]);
                      pixel.opacity = ScaleCharToQuantum(255-readbuffer[3]);
                      break;
                    }
                  }
              else      /* skip==true - Duplicate index on RLE repeat. */
                {
                  if (image->storage_class == PseudoClass)
                    indexes[x] = index;
                }

              if (EOFBlob(image))
                status = MagickFail;
              if (status == MagickFail)
                ThrowReaderException(CorruptImageError,UnableToReadImageData,image);
              *q++=pixel;
            }
          /*
            FIXME: Need to research what case was expected to be
            tested here.  This test case can never be true and so it
            is commented out for the moment.

            if (((unsigned char) (tga_info.attributes & 0xc0) >> 6) == 4)
            offset+=4;
            else
          */
          if (((unsigned char) (tga_info.attributes & 0xc0) >> 6) == 2)
            offset+=2;
          else
            offset++;
          if (offset >= image->rows)
            {
              base++;
              offset=base;
            }
          if (!SyncImagePixels(image))
            break;
          image->is_grayscale=is_grayscale;
          if (image->previous == (Image *) NULL)
            if (QuantumTick(y,image->rows))
              if (!MagickMonitorFormatted(y,image->rows,exception,
                                          LoadImageText,image->filename,
                                          image->columns,image->rows))
                break;
        }
      if (EOFBlob(image))
        {
          ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,
                         image->filename);
          break;
        }
      StopTimer(&image->timer);

      /*
        Proceed to next image.
      */
      if (image_info->subrange != 0)
        if (image->scene >= (image_info->subimage+image_info->subrange-1))
          break;

      if (LoadHeaderTGA(&tga_info, image) < 0)
        {
          status = MagickFalse;
        }
      else
        {
          status = (ValidateHeaderTGA(&tga_info)<0) ? MagickFalse : MagickTrue;
        }
      if (!EOFBlob(image) && (status == MagickTrue))
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
          image = SyncNextImageInList(image);
          if (!MagickMonitorFormatted(TellBlob(image),GetBlobSize(image),
                                      exception,LoadImagesText,
                                      image->filename))
            break;
        }
    } while (status == MagickTrue);
  while (image->previous != (Image *) NULL)
    image=image->previous;
  CloseBlob(image);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r T G A I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterTGAImage adds attributes for the TGA image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterTGAImage method is:
%
%      RegisterTGAImage(void)
%
*/
ModuleExport void RegisterTGAImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("ICB");
  entry->decoder=(DecoderHandler) ReadTGAImage;
  entry->encoder=(EncoderHandler) WriteTGAImage;
  entry->description="Truevision Targa image";
  entry->module="TGA";
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("TGA");
  entry->decoder=(DecoderHandler) ReadTGAImage;
  entry->encoder=(EncoderHandler) WriteTGAImage;
  entry->description="Truevision Targa image";
  entry->module="TGA";
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("VDA");
  entry->decoder=(DecoderHandler) ReadTGAImage;
  entry->encoder=(EncoderHandler) WriteTGAImage;
  entry->description="Truevision Targa image";
  entry->module="TGA";
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("VST");
  entry->decoder=(DecoderHandler) ReadTGAImage;
  entry->encoder=(EncoderHandler) WriteTGAImage;
  entry->description="Truevision Targa image";
  entry->module="TGA";
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r T G A I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterTGAImage removes format registrations made by the
%  TGA module from the list of supported formats.
%
%  The format of the UnregisterTGAImage method is:
%
%      UnregisterTGAImage(void)
%
*/
ModuleExport void UnregisterTGAImage(void)
{
  (void) UnregisterMagickInfo("ICB");
  (void) UnregisterMagickInfo("TGA");
  (void) UnregisterMagickInfo("VDA");
  (void) UnregisterMagickInfo("VST");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e T G A I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteTGAImage writes a image in the Truevision Targa rasterfile
%  format.
%
%  The format of the WriteTGAImage method is:
%
%      unsigned int WriteTGAImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteTGAImage return MagickTrue if the image is written.
%      MagickFalse is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/
static unsigned int WriteTGAImage(const ImageInfo *image_info,Image *image)
{
  const ImageAttribute
    *attribute;

  size_t
    count;

  long
    y;

  register const PixelPacket
    *p;

  /* register const IndexPacket
       *indexes; */

  register long
    x;

  register long
    i;

  register unsigned char
    *q;

  TGAInfo
    tga_info;

  unsigned char
    *tga_pixels;

  unsigned int
    write_grayscale,
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
  if (status == MagickFalse)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  scene=0;
  do
    {
      ImageCharacteristics
        characteristics;

      write_grayscale=MagickFalse;

      /*
        If requested output is grayscale, then write grayscale.
      */
      if ((image_info->type == GrayscaleType) ||
          (image_info->type == GrayscaleMatteType))
        write_grayscale=MagickTrue;

      /*
        Convert colorspace to an RGB-compatible type.
      */
      (void) TransformColorspace(image,RGBColorspace);

      /*
        Analyze image to be written.
      */
      (void) GetImageCharacteristics(image,&characteristics,
                                     (OptimizeType == image_info->type),
                                     &image->exception);

      /*
        If some other type has not been requested and the image is
        grayscale, then write a grayscale image unless the image
        contains an alpha channel.
      */
      if (((image_info->type != TrueColorType) &&
           (image_info->type != TrueColorMatteType) &&
           (image_info->type != PaletteType) &&
           (image->matte == MagickFalse)) &&
          (characteristics.grayscale))
        write_grayscale=MagickTrue;

      /*
        If there are too many colors for colormapped output or the
        image contains an alpha channel, then promote to TrueColor.
      */
      if (((write_grayscale == MagickFalse) &&
           (image->storage_class == PseudoClass) &&
           (image->colors > 256)) ||
          (image->matte == MagickTrue))
        {
          /* (void) SyncImage(image); */
          image->storage_class=DirectClass;
        }

      /*
        Initialize TGA raster file header.
      */
      tga_info.id_length=0;
      attribute=GetImageAttribute(image,"comment");
      if (attribute != (const ImageAttribute *) NULL)
        {
          unsigned char id_length =(unsigned char) strlen(attribute->value);
          tga_info.id_length=Min(id_length,255);
        }
      tga_info.colormap_type=0;
      tga_info.colormap_index=0;
      tga_info.colormap_length=0;
      tga_info.colormap_size=0;
      tga_info.x_origin=0;
      tga_info.y_origin=0;
      tga_info.width=(unsigned short) image->columns;
      tga_info.height=(unsigned short) image->rows;
      tga_info.bits_per_pixel=8;
      tga_info.attributes=0;
      if (write_grayscale == MagickTrue)
        {
          /*
            Grayscale without Colormap
          */
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Writing Grayscale raster ...");
          tga_info.image_type=TGAMonochrome;
          tga_info.bits_per_pixel = (image->colors==2) ? 1 : 8;
          tga_info.colormap_type=0;
          tga_info.colormap_index=0;
          tga_info.colormap_length=0;
          tga_info.colormap_size=0;
        }
      else if (image->storage_class == DirectClass)
        {
          /*
            Full color TGA raster.
          */
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Writing TrueColor raster ...");

          tga_info.image_type=TGARGB;
          tga_info.bits_per_pixel=24;
          if (image->matte)
            {
              tga_info.bits_per_pixel=32;
              tga_info.attributes=8;  /* # of alpha bits */
            }
        }
      else
        {
          /*
            Colormapped TGA raster.
          */
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Writing ColorMapped raster ..." );
          tga_info.image_type=TGAColormap;
          tga_info.colormap_type=1;
          tga_info.colormap_index=0;
          tga_info.colormap_length=(unsigned short) image->colors;
          tga_info.colormap_size=24;
        }

      if (image->logging)
        LogTGAInfo(&tga_info);

      if ((image->columns > 65535) || (image->rows > 65535))
        ThrowWriterException(CoderError,ImageColumnOrRowSizeIsNotSupported, image);

      /*
        Write TGA header.
      */
      (void) WriteBlobByte(image,tga_info.id_length);
      (void) WriteBlobByte(image,tga_info.colormap_type);
      (void) WriteBlobByte(image,tga_info.image_type);
      (void) WriteBlobLSBShort(image,tga_info.colormap_index);
      (void) WriteBlobLSBShort(image,tga_info.colormap_length);
      (void) WriteBlobByte(image,tga_info.colormap_size);
      (void) WriteBlobLSBShort(image,tga_info.x_origin);
      (void) WriteBlobLSBShort(image,tga_info.y_origin);
      (void) WriteBlobLSBShort(image,tga_info.width);
      (void) WriteBlobLSBShort(image,tga_info.height);
      (void) WriteBlobByte(image,tga_info.bits_per_pixel);
      (void) WriteBlobByte(image,tga_info.attributes);
      if (tga_info.id_length != 0)
        (void) WriteBlob(image,tga_info.id_length,attribute->value);
      if (tga_info.image_type == TGAColormap)
        {
          unsigned char
            *targa_colormap;

          /*
            Dump colormap to file (blue, green, red byte order).
          */
          targa_colormap=MagickAllocateResourceLimitedArray(unsigned char *,
                                                            tga_info.colormap_length,3);
          if (targa_colormap == (unsigned char *) NULL)
            ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,
                                 image);
          q=targa_colormap;
          for (i=0; i < (long) image->colors; i++)
            {
              *q++=ScaleQuantumToChar(image->colormap[i].blue);
              *q++=ScaleQuantumToChar(image->colormap[i].green);
              *q++=ScaleQuantumToChar(image->colormap[i].red);
            }
          (void) WriteBlob(image, (size_t)3*tga_info.colormap_length,
                           (char *) targa_colormap);
          MagickFreeResourceLimitedMemory(targa_colormap);
        }
      /*
        Convert MIFF to TGA raster pixels.
      */
      count = (size_t)((7+MagickArraySize(tga_info.bits_per_pixel,image->columns)) >> 3);  /*7 bits padding. */
      tga_pixels = MagickAllocateResourceLimitedMemory(unsigned char *,count);
      if (tga_pixels == (unsigned char *) NULL)
        ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);
      for (y=(long)(image->rows-1); y>=0; y--)
        {
          p = AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
          if (p == (const PixelPacket *) NULL)
            break;
          /* indexes = AccessImmutableIndexes(image); */

          switch (tga_info.image_type)
            {
            case TGAMonochrome:
              if (ExportImagePixelArea(image,GrayQuantum,tga_info.bits_per_pixel,tga_pixels,0,0) != MagickPass)
                status=MagickFail;
              break;
            case TGAColormap:
              if (ExportImagePixelArea(image,IndexQuantum,tga_info.bits_per_pixel,tga_pixels,0,0) != MagickPass)
                status=MagickFail;
              break;
            default:                    /* TrueColor RGB (quantum type is BGR, ExportImagePixelArea is useless.)*/
              q = tga_pixels;
              for (x=0; x<(long)image->columns; x++)
                {
                  *q++=ScaleQuantumToChar(p->blue);
                  *q++=ScaleQuantumToChar(p->green);
                  *q++=ScaleQuantumToChar(p->red);
                  if (image->matte)
                    *q++=ScaleQuantumToChar(MaxRGB-p->opacity);
                  p++;
                }
              break;
            }
          (void) WriteBlob(image,count,(char*)tga_pixels);
          if (image->previous == (Image *) NULL)
            if (QuantumTick(y,image->rows))
              if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                          SaveImageText,image->filename,
                                          image->columns,image->rows))
                break;
        }
      MagickFreeResourceLimitedMemory(tga_pixels);
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
  CloseBlob(image);
  return(MagickTrue);
}
