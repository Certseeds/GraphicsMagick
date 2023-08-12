/*
% Copyright (C) 2003-2023 GraphicsMagick Group
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                    TTTTT   OOO    PPPP    OOO    L                          %
%                      T    O   O   P   P  O   O   L                          %
%                      T    O   O   PPPP   O   O   L                          %
%                      T    O   O   P      O   O   L                          %
%                      T     OOO    P       OOO    LLLL                       %
%                                                                             %
%                                                                             %
%                    Read/Write TOPOL X Image Raster Format.                  %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                              Jaroslav Fojtik                                %
%                                2003 - 2023                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Note: TopoL GIS is here: http://www.topol.eu/articles/about
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/constitute.h"
#include "magick/magick_endian.h"
#include "magick/error.h"
#include "magick/list.h"
#include "magick/magick.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"


typedef struct
{
  char Name[20];
  magick_uint16_t Rows;
  magick_uint16_t Cols;
  magick_uint16_t FileType;     /* 0-binary, 1-8 bitu, 2-8 bits+PAL, 3-4 bits,
                                   4-4 bits+PAL, 5-24 bits, 6-16 bits, 7-32 bits */
  magick_uint32_t Zoom;
  magick_uint16_t Version;
  magick_uint16_t Komprese;	/* 0 - uncompressed (from release 1) */
  magick_uint16_t Stav;
  double xRasMin;
  double yRasMin;
  double xRasMax;
  double yRasMax;
  double Scale;                 /* from release 2 */
  magick_uint16_t TileWidth;    /* tile width in pixels */
  magick_uint16_t TileHeight;   /* tile height in pixels */
  magick_uint32_t TileOffsets;  /* offset to array of longints that contains
                                   adresses of tiles in the raster (adreses
                                   are counted from 0) */
  magick_uint32_t TileByteCounts;/* offset to array of words, that contain amount of bytes stored in
                                   tiles. The tile size might vary depending on
                                   the value TileCompression */
  magick_uint8_t TileCompression;/* 0 - uncompressed, 1 - variant TIFF
                                   Packbits, 2 - CCITT G3 */

  magick_uint8_t Dummy[423];
} RasHeader;

/*
typedef struct                  The palette record inside TopoL
{
   BYTE Flag;
   BYTE Red;
   BYTE Green;
   BYTE Blue;
} paletteRAS;*/

static int InsertRow(int depth, unsigned char *p, long y, Image * image, unsigned Xoffset, unsigned columns, ImportPixelAreaOptions *import_options)
{
  int
    bit;

  long
    x;

  register PixelPacket
    *q;

  IndexPacket
    index;

  register IndexPacket
    *indexes;

  switch (depth)
    {
    case 1:                     /* Convert bitmap scanline. */
      {
        q = SetImagePixels(image, Xoffset, y, columns, 1);
        if(q == (PixelPacket *) NULL) return -1;
        indexes = AccessMutableIndexes(image);
        for (x = 0; x < ((long)columns - 7); x += 8)
          {
            for (bit = 0; bit < 8; bit++)
              {
                index = ((*p) & (0x80U >> bit) ? 0x01U : 0x00U);
                indexes[x + bit] = index;
                *q++ = image->colormap[index];
              }
            p++;
          }
        if ((columns % 8) != 0)
          {
            for (bit = 0; bit < (long)(columns % 8); bit++)
              {
                index = ((*p) & (0x80 >> bit) ? 0x01 : 0x00);
                indexes[x + bit] = index;
                *q++ = image->colormap[index];
              }
            p++;
          }
        if (!SyncImagePixels(image))
          break;
        /* if (image->previous == (Image *) NULL)
           if (QuantumTick(y,image->rows))
           ProgressMonitor(LoadImageText,image->rows-y-1,image->rows); */
        break;
      }
    case 2:                     /* Convert PseudoColor scanline. */
      {
        q = SetImagePixels(image, Xoffset, y, columns, 1);
        if(q == (PixelPacket *) NULL) return -1;
        indexes = AccessMutableIndexes(image);
        for (x = 0; x < ((long)columns - 1); x += 2)
          {
            index = (IndexPacket) ((*p >> 6) & 0x3);
            VerifyColormapIndex(image, index);
            indexes[x] = index;
            *q++ = image->colormap[index];
            index = (IndexPacket) ((*p >> 4) & 0x3);
            VerifyColormapIndex(image, index);
            indexes[x] = index;
            *q++ = image->colormap[index];
            index = (IndexPacket) ((*p >> 2) & 0x3);
            VerifyColormapIndex(image, index);
            indexes[x] = index;
            *q++ = image->colormap[index];
            index = (IndexPacket) ((*p) & 0x3);
            VerifyColormapIndex(image, index);
            indexes[x + 1] = index;
            *q++ = image->colormap[index];
            p++;
          }
        if ((columns % 4) != 0)
          {
            index = (IndexPacket) ((*p >> 6) & 0x3);
            VerifyColormapIndex(image, index);
            indexes[x] = index;
            *q++ = image->colormap[index];
            if ((columns % 4) >= 1)
              {
                index = (IndexPacket) ((*p >> 4) & 0x3);
                VerifyColormapIndex(image, index);
                indexes[x] = index;
                *q++ = image->colormap[index];
                if((columns % 4) >= 2)
                  {
                    index = (IndexPacket) ((*p >> 2) & 0x3);
                    VerifyColormapIndex(image, index);
                    indexes[x] = index;
                    *q++ = image->colormap[index];
                  }
              }
            p++;
          }
        if (!SyncImagePixels(image))
          break;
        /*         if (image->previous == (Image *) NULL)
                   if (QuantumTick(y,image->rows))
                   ProgressMonitor(LoadImageText,image->rows-y-1,image->rows); */
        break;
      }

    case 4:                     /* Convert PseudoColor scanline. */
      {
        q = SetImagePixels(image, Xoffset, y, columns, 1);
        if(q == (PixelPacket *) NULL) return -1;
        indexes = AccessMutableIndexes(image);
        for (x = 0; x < ((long)columns - 1); x += 2)
          {
            index = (IndexPacket) ((*p >> 4) & 0xF);    /* Lo nibble */
            VerifyColormapIndex(image, index);
            indexes[x] = index;
            *q++ = image->colormap[index];
            index = (IndexPacket) ((*p) & 0xF);         /* Hi nibble */
            VerifyColormapIndex(image, index);
            indexes[x + 1] = index;
            *q++ = image->colormap[index];
            p++;
          }
        if((columns % 2) != 0)
          {
            index = (IndexPacket) ((*p >> 4) & 0xF);    /* padding nibble */
            VerifyColormapIndex(image, index);
            indexes[x] = index;
            *q++ = image->colormap[index];
            p++;
          }
        if (!SyncImagePixels(image))
          break;
        /*         if (image->previous == (Image *) NULL)
                   if (QuantumTick(y,image->rows))
                   ProgressMonitor(LoadImageText,image->rows-y-1,image->rows); */
        break;
      }
    case 8:                     /* Convert PseudoColor scanline. */
      {
        q = SetImagePixels(image, Xoffset, y, columns, 1);
        if(q == (PixelPacket *) NULL) return -1;
        indexes = AccessMutableIndexes(image);

        for (x = 0; x < (long)columns; x++)
          {
            index = (IndexPacket) (*p);
            VerifyColormapIndex(image, index);
            indexes[x] = index;
            *q++ = image->colormap[index];
            p++;
          }
        if (!SyncImagePixels(image))
          break;
        /*           if (image->previous == (Image *) NULL)
                     if (QuantumTick(y,image->rows))
                     ProgressMonitor(LoadImageText,image->rows-y-1,image->rows); */
      }
      break;

    case 16:            /* Convert 16 bit Gray scanline. */
      q = SetImagePixels(image, Xoffset, y, columns, 1);
      if(q == (PixelPacket *) NULL) return -1;
      (void)ImportImagePixelArea(image,GrayQuantum,16,p,import_options,0);
      if(!SyncImagePixels(image)) break;
      break;

    case 24:            /* Convert RGB scanline. */
      q = SetImagePixels(image, Xoffset, y, columns, 1);
      if(q == (PixelPacket *) NULL) return -1;
      (void)ImportImagePixelArea(image,RGBQuantum,8,p,import_options,0);
      if(!SyncImagePixels(image)) break;
      break;

    case 32:            /* Convert 32 bit Gray scanline. */
      q = SetImagePixels(image, Xoffset, y, columns, 1);
      if(q == (PixelPacket *) NULL) return -1;
      (void)ImportImagePixelArea(image,GrayQuantum,32,p,import_options,0);
      if(!SyncImagePixels(image)) break;
      break;

    }

  return 0;
}


/* This function reads one block of unsigned longS */
static int ReadBlobDwordLSB(Image *image, size_t len, magick_uint32_t *data)
{
  if(ReadBlob(image, len, data) != len) return -1;

#if defined(WORDS_BIGENDIAN)
  MagickSwabArrayOfUInt32(data, len/4);
#endif

  return 0;
}


static const char *ExplainFileType(magick_uint16_t FileType)
{
  switch(FileType)
  {
    case 0: return "binary";
    case 1: return "8 bits gray";
    case 2: return "8 bits + PALETTE";
    case 3: return "4 bits gray";
    case 4: return "4 bits + PALETTE";
    case 5: return "24 bits RGB";
    case 6: return "16 bits";
    case 7: return "32 bits";
  }
  return "Unknown - invalid";
}

static void LogHeaderTopoL(RasHeader *pHeader)
{
 if(pHeader==NULL) return;
 (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "TopoL Header:\n"
                        "    Rows:		%u\n"
                        "    Columns:		%u\n"
                        "    FileType:		%u %s\n"
                        "    Zoom:		%u\n"
                        "    Version:		%u\n"
                        "    Compression:	%u\n"
                        "    Status:		%u",
                               pHeader->Rows,
			       pHeader->Cols,
                               pHeader->FileType, ExplainFileType(pHeader->FileType),
			       pHeader->Zoom,
                               pHeader->Version,
			       pHeader->Komprese,
                               pHeader->Stav);
}


static ImageInfo *CheckFName(ImageInfo *clone_info, size_t *i)
{
size_t j;
  if(clone_info==NULL || i==NULL) return NULL;

  j = *i = strnlen(clone_info->filename, sizeof(clone_info->filename));
  if(j>=sizeof(clone_info->filename) || j==0)
  {
    DestroyImageInfo(clone_info);
    return NULL;
  }

  while(--j > 0)
  {
    const char c = clone_info->filename[j];
    if(c == '.')
    {
      *i = j;
      break;
    }
    if(c=='/' || c=='\\' || c==':')
    {
      j = *i;
      break;	/* *i will remain intact. */
    }
  }

  if(j <= 0)
  {
    DestroyImageInfo(clone_info);
    return NULL;
  }

return clone_info;
}



/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d T O P O L I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadTopoLImage reads an TOPOL X image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadTopoLImage method is:
%
%      Image *ReadTopoLImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadTopoLImage returns a pointer to the image after
%      reading. A null image is returned if there is a memory shortage or if
%      the image cannot be read.
%
%    o image_info: The image info.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/

#define ThrowTOPOLReaderException(code_,reason_,image_) \
{ \
  if (clone_info) \
    DestroyImageInfo(clone_info); \
  if (palette) \
    DestroyImage(palette); \
  MagickFreeResourceLimitedMemory(BImgBuff); \
  ThrowReaderException(code_,reason_,image_); \
}

static Image *ReadTopoLImage(const ImageInfo * image_info, ExceptionInfo * exception)
{
  Image
    *image,
    *palette = (Image *) NULL;

  ImageInfo
    *clone_info = (ImageInfo *) NULL;

  RasHeader
    Header;

  int logging;

  int
    depth,
    status;

  size_t i;
  long j;
  long ldblk;

  unsigned char
    *BImgBuff = NULL,
    MEZ[256] = { 0 };
  ImportPixelAreaOptions import_options;


  palette = NULL;
  clone_info = NULL;

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);

  logging = LogMagickEvent(CoderEvent,GetMagickModule(),"enter");

  image = AllocateImage(image_info);
  status = OpenBlob(image_info, image, ReadBinaryBlobMode, exception);
  if (status == False)
    ThrowReaderException(FileOpenError, UnableToOpenFile, image);

  ImportPixelAreaOptionsInit(&import_options);
  import_options.endian = LSBEndian;
  import_options.sample_type = UnsignedQuantumSampleType;

  /*
    Read TopoL RAS header.
  */
  (void) memset(&Header, 0, sizeof(Header));
  (void) ReadBlob(image, 20, &Header.Name);

  Header.Rows = ReadBlobLSBShort(image);
  Header.Cols = ReadBlobLSBShort(image);
  Header.FileType = ReadBlobLSBShort(image);
  Header.Zoom = ReadBlobLSBLong(image);
  Header.Version = ReadBlobLSBShort(image);
  if (EOFBlob(image))
    ThrowTOPOLReaderException(CorruptImageError,UnexpectedEndOfFile,image);
  if (Header.Version >= 1)
    {
      Header.Komprese = ReadBlobLSBShort(image);
      Header.Stav = ReadBlobLSBShort(image);
      Header.xRasMin = ReadBlobLSBDouble(image);
      Header.yRasMin = ReadBlobLSBDouble(image);
      Header.xRasMax = ReadBlobLSBDouble(image);
      Header.yRasMax = ReadBlobLSBDouble(image);
      if (Header.Version >= 2)  /* from release 2 */
        {
          Header.Scale = ReadBlobLSBDouble(image);
          Header.TileWidth = ReadBlobLSBShort(image);
          Header.TileHeight = ReadBlobLSBShort(image);
          Header.TileOffsets = ReadBlobLSBLong(image);
          Header.TileByteCounts = ReadBlobLSBLong(image);
          Header.TileCompression = ReadBlobByte(image);
          /* BYTE Dummy[423]; */
        }
      if (EOFBlob(image))
        ThrowTOPOLReaderException(CorruptImageError,UnexpectedEndOfFile,image);
    }
  if(image->logging) LogHeaderTopoL(&Header);

  for(i=0; i<sizeof(Header.Name); i++)
    {
      if (Header.Name[i] < ' ')
TOPOL_KO:              ThrowTOPOLReaderException(CorruptImageError,ImproperImageHeader, image);
    }
  if (Header.Komprese != 0 || (Header.Version >= 2 && Header.TileCompression != 0))
    ThrowTOPOLReaderException(CorruptImageError, UnrecognizedImageCompression, image);
  if(Header.Rows == 0 || Header.Cols == 0 ||
      ((Header.Version >= 2) &&
       (Header.TileWidth == 0 ||
        Header.TileHeight == 0 ||
        Header.TileOffsets == 0 ||
        Header.TileByteCounts == 0)))
      ThrowTOPOLReaderException(CorruptImageError,ImproperImageHeader, image);
  if (Header.Version > 2)
    ThrowTOPOLReaderException(CorruptImageError, InvalidFileFormatVersion, image); /* unknown version */

  switch(Header.FileType)
    {
    case 0:
      image->colors = 2;
      depth = 1;
      break;
    case 1:
    case 2:
      image->colors = 256;
      depth = 8;
      break;
    case 3:
    case 4:
      image->colors = 16;
      depth = 4;
      break;
    case 5:
      image->colors = 0;
      image->depth = 8;
      depth = 24;
      break;
    case 6:
      image->colors = 0;
      depth = 16;
      break;                    /* ????????? 16 bits */
    case 7:
      image->colors = 0;
      depth = 32;
      break;                    /* ????????? 32 bits */
    default:
      goto TOPOL_KO;
    }

  image->columns = Header.Cols;
  image->rows = Header.Rows;

  j = GetBlobSize(image);
  if(j<512)			// Header size=512bytes; negative number means failure.
  {
    fprintf(stderr,"TopoL: GetBlobSize() returned small or negative value %ld!",j);
    goto TOPOL_KO;
  }

  /* If ping is true, then only set image size and colors without reading any image data. */
  if (image_info->ping) goto DONE_READING;

  if(((magick_uint64_t)(depth*Header.Cols+7)/8) * (magick_uint64_t)Header.Rows > (magick_uint64_t)GetBlobSize(image)-512)
      goto TOPOL_KO;    /* Check for forged image that overflows file size. */

  /* ----- Handle the reindexing mez file ----- */
  j = image->colors;
  if(j<=0 || j>256) j=256;
  for(i=0; i<(size_t) j; i++)
  {
    MEZ[i] = (unsigned char)((i*255) / (j-1));
  }

  if(Header.FileType>=5) goto NoMEZ;

  if((clone_info=CheckFName(CloneImageInfo(image_info),&i)) == NULL) goto NoMEZ;

  (void) strlcpy(clone_info->filename+i,".MEZ",sizeof(clone_info->filename)-i);
  if((clone_info->file=fopen(clone_info->filename,"rb"))==NULL)
    {
      (void) strlcpy(clone_info->filename+i,".mez",sizeof(clone_info->filename)-i);
      if((clone_info->file=fopen(clone_info->filename,"rb"))==NULL)
        {
          DestroyImageInfo(clone_info);
          clone_info=NULL;
          goto NoMEZ;
        }
    }

  if( (palette=AllocateImage(clone_info))==NULL ) goto NoMEZ;
  status=OpenBlob(clone_info,palette,ReadBinaryBlobMode,exception);
  if (status == False) goto NoMEZ;

  ldblk = (long)GetBlobSize(palette);
  if ( ldblk > (long) sizeof(MEZ))
    ldblk=sizeof(MEZ);
  (void) ReadBlob(palette, ldblk, MEZ);

NoMEZ:          /*Clean up palette and clone_info*/
  if (palette != NULL) {DestroyImage(palette);palette=NULL;}
  if (clone_info != NULL)
    {
      DestroyImageInfo(clone_info);
      clone_info=NULL;
    }

  /* ----- Do something with palette ----- */
  if(Header.FileType==5) goto NoPalette;
  if ((clone_info=CheckFName(CloneImageInfo(image_info),&i)) == NULL) goto NoPalette;

  (void) strlcpy(clone_info->filename+i,".PAL",sizeof(clone_info->filename)-i);
  if ((clone_info->file=fopen(clone_info->filename,"rb"))==NULL)
    {
      (void) strlcpy(clone_info->filename+i,".pal",sizeof(clone_info->filename)-i);
      if ((clone_info->file=fopen(clone_info->filename,"rb"))==NULL)
        {
          clone_info->filename[i]=0;
          if ((clone_info->file=fopen(clone_info->filename,"rb"))==NULL)
            {
              DestroyImageInfo(clone_info);
              clone_info=NULL;
              goto NoPalette;
            }
        }
    }

  if( (palette=AllocateImage(clone_info))==NULL ) goto NoPalette;
  status=OpenBlob(clone_info,palette,ReadBinaryBlobMode,exception);
  if (status == False)
    {
    ErasePalette:
      DestroyImage(palette);
      palette=NULL;
      goto NoPalette;
    }


  if(palette!=NULL)
    {
      ldblk=ReadBlobByte(palette);              /*size of palette*/
      if(ldblk==EOF) goto ErasePalette;
      if(ldblk==0)
          image->colors = 256;
      else
          image->colors = ldblk+1;
      if(!AllocateImageColormap(image, image->colors)) goto NoMemory;

      for(i=0;i<=(size_t) ldblk;i++)
      {
        j = ReadBlobByte(palette);      /* Flag */
        if(j==EOF) break;               /* unexpected end of file */
        if(j<=ldblk)
        {
          if(j==MEZ[i])
            j = i; /* MEZ[i];   ignore MEZ!!! proper palete element after reindexing */
          else
            j = MEZ[i];                 /* ?? I do not know, big mess ?? */
          if(j>=(long) image->colors) j=image->colors-1;
          image->colormap[j].red = ScaleCharToQuantum(ReadBlobByte(palette));
          image->colormap[j].green = ScaleCharToQuantum(ReadBlobByte(palette));
          image->colormap[j].blue = ScaleCharToQuantum(ReadBlobByte(palette));
        }
        else
        {
          (void) SeekBlob(palette, 3, SEEK_CUR);
          (void) fprintf(stderr,"TopoL: Wrong index inside palette %d!",(int)j);
        }
      }
    }

NoPalette:
  if(palette == NULL && image->colors != 0)
  {
    if(Header.FileType<5)
    {
      if (!AllocateImageColormap(image, image->colors))
      {
        NoMemory:
          ThrowTOPOLReaderException(ResourceLimitError, MemoryAllocationFailed, image);
      }

      for(i = 0; i < image->colors; i++)
      {
        j = MEZ[i];
        image->colormap[i].red = ScaleCharToQuantum(j);
        image->colormap[i].green = ScaleCharToQuantum(j);
        image->colormap[i].blue = ScaleCharToQuantum(j);
      }
    }
  }

  /* ----- Load TopoL raster ----- */
  switch(Header.Version)
  {
   case 0:
   case 1:
     ldblk = (long) ((depth * image->columns + 7) / 8);
     BImgBuff = MagickAllocateResourceLimitedMemory(unsigned char *,(size_t) ldblk);   /*Ldblk was set in the check phase */
     if (BImgBuff == NULL)
        ThrowTOPOLReaderException(ResourceLimitError, MemoryAllocationFailed, image);
     (void) SeekBlob(image, 512 /*sizeof(Header)*/, SEEK_SET);
     for (i = 0; i < Header.Rows; i++)
     {
       if (ReadBlob(image, ldblk, (char *)BImgBuff) != (size_t) ldblk)
         ThrowTOPOLReaderException(CorruptImageError,UnexpectedEndOfFile,image);
       InsertRow(depth, BImgBuff, i, image, 0, image->columns, &import_options);
     }
     break;
  case 2:
    {
      magick_uint32_t *Offsets;
      long SkipBlk;
      unsigned TilX, TilY;
      unsigned TilesAcross = (Header.Cols+Header.TileWidth-1) / Header.TileWidth;
      unsigned TilesDown   = (Header.Rows+Header.TileHeight-1) / Header.TileHeight;

      if(Header.TileCompression!=0)
                {
                ThrowTOPOLReaderException(CorruptImageError, UnrecognizedImageCompression, image);
                break;
                }

       ldblk = (long)((depth * Header.TileWidth + 7) / 8);
       BImgBuff = MagickAllocateResourceLimitedMemory(unsigned char *,(size_t) ldblk); /*Ldblk was set in the check phase */
       if (BImgBuff == NULL)
         ThrowTOPOLReaderException(ResourceLimitError, MemoryAllocationFailed, image);

       /* dlazdice.create(Header.TileWidth,Header.TileHeight,p.Planes); */
       Offsets = MagickAllocateResourceLimitedArray(magick_uint32_t *,
                                     MagickArraySize((size_t)TilesAcross,(size_t)TilesDown),
                                     sizeof(magick_uint32_t));
       if(Offsets==NULL)
         ThrowTOPOLReaderException(ResourceLimitError, MemoryAllocationFailed, image);

       (void)SeekBlob(image, Header.TileOffsets, SEEK_SET);
       if(ReadBlobDwordLSB(image, TilesAcross*TilesDown*4, (magick_uint32_t *)Offsets) < 0)
       {
         MagickFreeResourceLimitedMemory(Offsets);
         ThrowTOPOLReaderException(CorruptImageError,InsufficientImageDataInFile, image);
       }

       for(TilY=0; TilY<Header.Rows; TilY+=Header.TileHeight)	/* TilY counts per pixel.*/
         for(TilX=0; TilX<TilesAcross; TilX++)			/* TilX counts per tile.*/
           {
           ldblk = Offsets[(TilY/Header.TileHeight)*TilesAcross+TilX];
           if(SeekBlob(image, ldblk, SEEK_SET) != ldblk)
             {                                                  /* When seek does not reach required place, bail out. */
               MagickFreeResourceLimitedMemory(Offsets);
               ThrowTOPOLReaderException(CorruptImageError,InsufficientImageDataInFile, image);
               break;
             }

           ldblk = image->columns - TilX*Header.TileWidth;

           if(ldblk>Header.TileWidth) ldblk = Header.TileWidth;
           SkipBlk = ((long)depth * (Header.TileWidth-ldblk)+7) / 8;
           ldblk = ((long)depth * ldblk+7) / 8;

           j = TilX * (ldblk+SkipBlk);
           for(i=0;i<Header.TileHeight;i++)
           {                                    /* It appears that tile padding is legal in Topol format. */
             if((unsigned long) i+TilY>=image->rows) break;     /* Do not read padding tile data, abort the current tile. */

             if(ReadBlob(image, ldblk, (char *)BImgBuff) != (size_t) ldblk)
             {
               MagickFreeResourceLimitedMemory(Offsets);
               ThrowTOPOLReaderException(CorruptImageError,InsufficientImageDataInFile, image);
               break;
             }
             if(SkipBlk>0)
               SeekBlob(image, SkipBlk, SEEK_CUR);
             /*printf("Inserting x=%d; y=%d\n", TilX*Header.TileWidth, i+TilY);*/
             if(InsertRow(depth, BImgBuff, i+TilY, image, TilX*Header.TileWidth,
                    (image->columns<Header.TileWidth)?image->columns:Header.TileWidth, &import_options))
             {
               MagickFreeResourceLimitedMemory(Offsets);
               ThrowTOPOLReaderException(CorruptImageError,TooMuchImageDataInFile, image);
               break;
             }
          }
        }

       MagickFreeResourceLimitedMemory(Offsets);
       break;
      }
    }

  /* Finish: */
DONE_READING:
  MagickFreeResourceLimitedMemory(BImgBuff);
  if (palette != NULL)
    DestroyImage(palette);
  if (clone_info != NULL)
    DestroyImageInfo(clone_info);
  /* if (EOFBlob(image))
     ThrowTOPOLReaderException(CorruptImageError,UnexpectedEndOfFile,image); */
  CloseBlob(image);
  StopTimer(&image->timer);

  if (logging) (void)LogMagickEvent(CoderEvent,GetMagickModule(),"return");
  return (image);
}


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e T o p o L I m a g e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Function WriteTopoLImage writes an WPG image to a file.
%
%  The format of the WriteTopoLImage method is:
%
%      unsigned int WriteTopoLImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Function WriteTopoLImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
*/
static MagickPassFail WriteTopoLImage(const ImageInfo *image_info, Image *image)
{
  long y;
  unsigned int status;
  int logging;
  unsigned char *pixels;
  RasHeader Header;
  size_t DataSize;
  QuantumType qt;
  int bpp;
  ExportPixelAreaInfo export_info;

	/* Open output image file. */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *)NULL);
  assert(image->signature == MagickSignature);
  logging = LogMagickEvent(CoderEvent,GetMagickModule(),"enter TopoL");

  DataSize = 0;
  memset(&Header,0,sizeof(Header));
  memset(&Header.Name,' ',sizeof(Header.Name));
  //Header.Version = 0;
  Header.Cols = image->columns;
  Header.Rows = image->rows;
  if(image->colors>=1 && image->colors<=256)
  {
    if(image->colors <= 2)
    {
      Header.FileType = 0;
      DataSize = (Header.Cols+7) / 8;
      qt = GrayQuantum;
      bpp =1;
    } else if(image->colors <= 16)
    {
      Header.FileType = 4;
      DataSize = (Header.Cols+1) / 2;
      qt = IndexQuantum;
      bpp = 4;
    }
    else
    {
      Header.FileType = 2;
      DataSize = Header.Cols;
      qt = IndexQuantum;
      bpp = 8;
    }
  }
  else		// RGB
  {
    Header.FileType = 5;
    DataSize = 3*Header.Cols;
    qt = RGBQuantum;
    bpp = 8;
  }

  if(DataSize==0)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  pixels = MagickAllocateResourceLimitedMemory(unsigned char *,(size_t) (DataSize));
  if (pixels == (unsigned char *) NULL)
    ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);

  status = OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if(status == MagickFail)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);

	/* Write TopoL hader. */
  WriteBlob(image, 20, Header.Name);
  WriteBlobLSBShort(image, Header.Rows);
  WriteBlobLSBShort(image, Header.Cols);
  WriteBlobLSBShort(image, Header.FileType);
  WriteBlobLSBLong(image, Header.Zoom);
  WriteBlobLSBShort(image, Header.Version);
  WriteBlobLSBShort(image, Header.Komprese);
  WriteBlobLSBShort(image, Header.Stav);

  WriteBlobLSBDouble(image, Header.xRasMin);
  WriteBlobLSBDouble(image, Header.yRasMin);
  WriteBlobLSBDouble(image, Header.xRasMax);
  WriteBlobLSBDouble(image, Header.yRasMax);
  WriteBlobLSBDouble(image, Header.Scale);
	//from release 2
  WriteBlobLSBShort(image, Header.TileWidth);
  WriteBlobLSBShort(image, Header.TileHeight);
  WriteBlobLSBLong(image, Header.TileOffsets);
  WriteBlobLSBLong(image, Header.TileByteCounts);
  WriteBlobByte(image, Header.TileCompression);

  WriteBlob(image, 423, Header.Dummy);
  if (GetBlobStatus(image))
     ThrowWriterException(FileOpenError,UnableToWriteFile,image);

	/* Store image data. */
  for(y=0; y<(long)image->rows; y++)
  {
    if(AcquireImagePixels(image,0,y,image->columns,1,&image->exception)  == (const PixelPacket *)NULL)
    {
      status=MagickFail;
      break;
    }
    if(ExportImagePixelArea(image,qt,bpp,pixels,0,&export_info) != MagickPass)
    {
      status = MagickFail;
      break;
    }
    if (DataSize != export_info.bytes_exported)
    {
      status = MagickFail;
      break;
    }
    if(WriteBlob(image,DataSize,pixels) != DataSize)
    {
      status = MagickFail;
      break;
    }
  }

  CloseBlob(image); /* valgrind reports write of unitialized data */
  MagickFreeResourceLimitedMemory(pixels);

  if (y != (long)image->rows)
    ThrowWriterException(FileOpenError,UnableToWriteFile,image);


	/* Palette */
  if(qt == IndexQuantum)
  {
    ImageInfo *clone_info;
    size_t i;
    if((clone_info=CheckFName(CloneImageInfo(image_info),&i)) != NULL)
    {
      (void)strlcpy(clone_info->filename+i,".pal",sizeof(clone_info->filename)-i);
      if((clone_info->file=fopen(clone_info->filename,"wb"))!=NULL)
      {
        Image *Palette;
        if((Palette=AllocateImage(clone_info)) != NULL)
        {
          ExceptionInfo exception;
          if(OpenBlob(clone_info,Palette,WriteBinaryBlobMode,&exception))
          {
            size_t j;
            if(Header.FileType == 2)
              j = 256;
            else
              j = 15;
            WriteBlobByte(Palette,j);
            for(i=0; i<j; i++)
            {
              WriteBlobByte(Palette, i&0xFF);
              if(i<image->colors)
              {
                WriteBlobByte(Palette,i);
                WriteBlobByte(Palette,i);
                WriteBlobByte(Palette,i);
              }
              else
              {
                WriteBlobByte(Palette,ScaleQuantumToChar(image->colormap[i].red));
                WriteBlobByte(Palette,ScaleQuantumToChar(image->colormap[i].green));
                WriteBlobByte(Palette,ScaleQuantumToChar(image->colormap[i].blue));
              }
            }
            CloseBlob(Palette);
          }
          DestroyImage(Palette);
        }
      }
      DestroyImageInfo(clone_info);
    }
  }

  if(logging)
    (void)LogMagickEvent(CoderEvent,GetMagickModule(),"return TopoL");

  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s T o p o L                                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsTopoL returns True if the image format type, identified by the
%  magick string, is TopoL.
%
%  The format of the IsTopoL method is:
%
%      unsigned int IsTopoL(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsTopoL returns True if the image format type is TopoL.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.*/
static unsigned int IsTopoL(const unsigned char *magick, const size_t length)
{
int i;
magick_uint16_t FileType;     /* 0-binary, 1-8 bitu, 2-8 bits+PAL, 3-4 bits,
                                   4-4 bits+PAL, 5-24 bits, 6-16 bits, 7-32 bits */
//magick_uint32_t Zoom;
magick_uint16_t Version;
magick_uint16_t Compression;	/* 0 - uncompressed (from release 1) */
//magick_uint16_t Stav;

  if (length < 34) return(False);
  for(i=0; i<20; i++)
      if(magick[i] != ' ') return(False);
  if(magick[20]==0 && magick[21]==0) return(False);	// Zero rows
  if(magick[22]==0 && magick[23]==0) return(False);	// Zero cols

  FileType = magick[24] + 256*magick[25];
  if(FileType > 7) return False;
  Version = magick[30] + 256*magick[31];
  if(Version > 2) return(False);
  Compression = magick[32] + 256*magick[33];
  if(Compression > 1) return(False);
  if(Compression==1 && Version==0) return(False);

  return(True);
}


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r T O P O L I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterTOPOLImage adds attributes for the TOPOL image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterTOPOLImage method is:
%
%      RegisterTOPOLImage(void)
%
*/
ModuleExport void RegisterTOPOLImage(void)
{
  MagickInfo * entry;

  entry = SetMagickInfo("TOPOL");
  entry->decoder = (DecoderHandler) ReadTopoLImage;
  entry->encoder = (EncoderHandler) WriteTopoLImage;
  entry->magick = (MagickHandler) IsTopoL;
  entry->seekable_stream = True;
  entry->description = "TopoL X Image";
  entry->adjoin=MagickFalse;
  entry->module = "TOPOL";
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r T O P O L I m a g e                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterTOPOLImage removes format registrations made by the
%  TOPOL module from the list of supported formats.
%
%  The format of the UnregisterTOPOLImage method is:
%
%      UnregisterTOPOLImage(void)
%
*/
ModuleExport void UnregisterTOPOLImage(void)
{
  (void) UnregisterMagickInfo("TOPOL");
}
