/*
% Copyright (C) 2003-2024 GraphicsMagick Group
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
%                            X   X  PPPP   M   M                              %
%                             X X   P   P  MM MM                              %
%                              X    PPPP   M M M                              %
%                             X X   P      M   M                              %
%                            X   X  P      M   M                              %
%                                                                             %
%                                                                             %
%                 Read/Write X Windows system Pixmap Format.                  %
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
#include "magick/blob.h"
#include "magick/color.h"
#include "magick/color_lookup.h"
#include "magick/colormap.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/quantize.h"
#include "magick/resize.h"
#include "magick/utility.h"


#define MAX_XPM_SUPPORTED_COLORS        Max(0x20000,MaxColormapSize)

/*
  Forward declarations.
*/
static unsigned int
  WritePICONImage(const ImageInfo *,Image *),
  WriteXPMImage(const ImageInfo *,Image *);

typedef magick_uint32_t xpmkeyval_t;

typedef struct xpmkey
{
  magick_uint32_t index;        /* Colormap index */
  xpmkeyval_t keyval;           /* Encoded XPM key value */
} xpmkey_t;


static int XPMKeyCompare(const void *l, const void *r)
{
  const xpmkey_t * restrict lp = l;
  const xpmkey_t * restrict rp = r;
  int sense;

  if (lp->keyval > rp->keyval)
    sense = 1;
  else if (lp->keyval < rp->keyval)
    sense = -1;
  else
    sense = 0;

  return sense;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s X P M                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsXPM returns True if the image format type, identified by the
%  magick string, is XPM.
%
%  The format of the IsXPM method is:
%
%      unsigned int IsXPM(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsXPM returns True if the image format type is XPM.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsXPM(const unsigned char *magick,const size_t length)
{
  if (length < 9)
    return(False);
  if (LocaleNCompare((char *) magick,"/* XPM */",9) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d X P M I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadXPMImage reads an X11 pixmap image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadXPMImage method is:
%
%      Image *ReadXPMImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadXPMImage returns a pointer to the image after
%      creating it. A null image is returned if there is a memory shortage
%      or if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/

static char **StringToListMod(char *text)
{
  char
    **textlist;

  register char
    *p;

  register size_t
    i;

  size_t
    lines;

  if (text == (char *) NULL)
    return((char **) NULL);

  /*
    Convert string to an ASCII list, modifying the input string.
  */
  lines=1;
  for (p=text; *p != '\0'; p++)
    if (*p == '\n')
      lines++;
  textlist=MagickAllocateResourceLimitedMemory(char **,(lines+1)*sizeof(char *));
  if (textlist == (char **) NULL)
    MagickFatalError3(ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToConvertText);
  i=0;
  textlist[i]=text;
  for (p=text; *p != '\0'; p++)
    {
      if (*p == '\r')
        {
          *p='\0';
          continue;
        }
      if (*p == '\n')
        {
          *p='\0';
          if (*(p+1) != '\0')
            {
              i++;
              textlist[i]=p+1;
            }
        }
    }
  i++;
  textlist[i]=(char *) NULL;
  return(textlist);
}

static char *ParseColor(char *data) MAGICK_FUNC_PURE;

static char *ParseColor(char *data)
{
#define NumberTargets  6

  static const char
    targets[NumberTargets][3] = { "c ", "g ", "g4 ", "m ", "b ", "s " };

  register char
    *p,
    *r;

  register const char
    *q;

  register long
    i;

  for (i=0; i < NumberTargets; i++)
    {
      r=data;
      for (q=targets[i]; *r != '\0'; r++)
        {
          if (*r != *q)
            continue;
          if (!isspace((int) (*(r-1))))
            continue;
          p=r;
          for ( ; ; )
            {
              if (*q == '\0')
                return(r);
              if (*p++ != *q++)
                break;
            }
          q=targets[i];
        }
    }
  return((char *) NULL);
}
#define ThrowXPMReaderException(code_,reason_,image_) \
do { \
  MagickFreeResourceLimitedMemory(keys); \
  MagickFreeResourceLimitedMemory(textlist); \
  MagickFreeResourceLimitedMemory(xpm_buffer); \
  ThrowReaderException(code_,reason_,image_); \
} while (0);

static Image *ReadXPMImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  xpmkey_t
    *keys = (xpmkey_t *) NULL;

  char
    target[MaxTextExtent],
    **textlist = (char **) NULL,
    *xpm_buffer = (char *) NULL;

  Image
    *image;

  int
    count;

  unsigned int
    i,
    j,
    k,
    none;

  long
    y;

  register char
    *p,
    *q;

  register IndexPacket
    *indexes;

  register long
    x;

  register PixelPacket
    *r;

  MagickPassFail
    status;

  MagickBool
    colormap_initialized;

  size_t
    length;

  unsigned int
    width; /* characters per pixel */

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  image=AllocateImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFail)
    ThrowXPMReaderException(FileOpenError,UnableToOpenFile,image);
  /*
    Read XPM file.
  */
  length=MaxTextExtent*4;
  xpm_buffer=MagickAllocateResourceLimitedMemory(char *,length);
  if (xpm_buffer != (char *) NULL)
    {
      xpm_buffer[0]='\0';
      p=xpm_buffer;
      while (ReadBlobString(image,p) != (char *) NULL)
        {
          char *new_xpm_buffer;
          if (*p == '#')
            if ((p == xpm_buffer) || (*(p-1) == '\n'))
              continue;
          if ((*p == '}') && (*(p+1) == ';'))
            break;
          p+=strlen(p);
          if (((size_t) (p-xpm_buffer)+MaxTextExtent+1) < length)
            continue;
          length += MaxTextExtent*4;
          new_xpm_buffer=MagickReallocateResourceLimitedMemory(char *,xpm_buffer,length);
          if (new_xpm_buffer == (char *) NULL)
            {
              MagickFreeResourceLimitedMemory(xpm_buffer);
              break;
            }
          if (xpm_buffer != new_xpm_buffer)
            {
              p=(p-xpm_buffer)+new_xpm_buffer;
              xpm_buffer=new_xpm_buffer;
            }
        }
    }
  if (xpm_buffer == (char *) NULL)
    ThrowXPMReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  /*
    Parse image properties from file header while skipping over comment markers.
  */
  count=0;
  for (p=xpm_buffer; ((p - xpm_buffer) < 512) && (*p != '\0'); p++)
    {
      if ((*p != '"') || !isdigit((int) *(p+1)))
        continue;
      count=sscanf(p+1,"%lu %lu %u %u",&image->columns,&image->rows,
                   &image->colors,&width);
      if (count == 4)
        {
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Columns: %lu, Rows: %lu, Colors: %u, Char Per Pixel: %u",
                                image->columns, image->rows, image->colors, width);
          break;
        }
    }
  if ((count != 4) || (width == 0) || (width > 3) ||
      (image->columns == 0) || (image->rows == 0) ||
      (image->colors == 0))
    ThrowXPMReaderException(CorruptImageError,ImproperImageHeader,image);
  if (image->colors > MAX_XPM_SUPPORTED_COLORS)
    ThrowXPMReaderException(CoderError,ColormapTooLarge,image);
  image->depth=16;

  /*
    Remove unquoted characters.
  */
  {
    MagickBool inquote = MagickFalse;
    q=xpm_buffer;
    while (*p != '\0')
      {
        if (*p++ == '"')
          {
            if (inquote)
              *q++='\n';
            inquote = !inquote;
          }
        if (inquote)
          *q++=*p;
      }
    *q='\0';
    if (inquote)
      {
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Imbalanced quotes error");
        ThrowXPMReaderException(CorruptImageError,CorruptImage,image);
      }
  }

  /*
    Scan for non-white space binary control codes and reject file if
    they are present.
  */
  for (p=xpm_buffer; *p != '\0'; p++)
    if (((unsigned char) *p < 32) && !isspace((int)(unsigned char) (*p)))
      break;
  if (*p != '\0')
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Binary control codes error");
      ThrowXPMReaderException(CorruptImageError,CorruptImage,image);
    }
  textlist=StringToListMod(xpm_buffer);
  if (textlist == (char **) NULL)
    ThrowXPMReaderException(ResourceLimitError,MemoryAllocationFailed,image);
#if 0
  if (image->logging)
    {
      for (i=0; textlist[i] != (char *) NULL; i++)
        { };
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "TextList has %u entries", i);
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "TextList");
      for (i=0; textlist[i] != (char *) NULL; i++)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "    %u: \"%s\"", i, textlist[i]);
    }
#endif

  /*
    Initialize image structure.
  */
  keys=MagickAllocateResourceLimitedArray(xpmkey_t *,image->colors,sizeof(xpmkey_t));
  if (keys == (xpmkey_t *) NULL)
    ThrowXPMReaderException(ResourceLimitError,MemoryAllocationFailed,image);
  for (i=0; i < image->colors; i++)
    {
      keys[i].index=0;
      keys[i].keyval=0;
    }
  if (image->colors <= MaxColormapSize)
    {
      if (!AllocateImageColormap(image,image->colors))
        ThrowXPMReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    }
  else
    {
      /* Allocate temporary palette. */
      if (image->colormap != (PixelPacket *)NULL)
        MagickFreeMemory(image->colormap);
      image->colormap=MagickAllocateMemory(PixelPacket *,MagickArraySize((size_t) image->colors,sizeof(PixelPacket)));
      if (image->colormap==NULL)
        ThrowXPMReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    }

  /*
    Read image colormap.
  */
  i=1;
  none=(~0U);
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Parsing colormap...");
  colormap_initialized=MagickFalse;
  for (j=0; j < image->colors; j++)
    {
      p=textlist[i++];
      if ((p == (char *) NULL) || (p[0] == '\0'))
        break;
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "    %u: %s", i-1, textlist[i-1]);
      if (strlen(p) < width)
        break;

      keys[j].index = j;
      keys[j].keyval = 0;
      for (k=0; k < width; k++)
        keys[j].keyval |= ((xpmkeyval_t) p[k]) << (k * 8);

      /* printf("Key[%03u] =\"%s\" (0x%04X)\n", keys[j].index, p, (unsigned int) keys[j].keyval); */
      /*
        Parse color.
      */
      (void) strlcpy(target,"gray",sizeof(target));
      q=ParseColor(p+width);
      if (q != (char *) NULL)
        {
          while (!isspace((int) (*q)) && (*q != '\0'))
            q++;
          (void) strlcpy(target,q,MaxTextExtent);
          q=ParseColor(target);
          if (q != (char *) NULL)
            *q='\0';
        }
      (void) MagickStripString(target);
      if (LocaleCompare(target,"none") == 0)
        {
          image->storage_class=DirectClass;
          image->matte=True;
          none=j;
          (void) strlcpy(target,"black",sizeof(target));
        }
      if (!QueryColorDatabase(target,&image->colormap[j],exception))
        {
          /* Promote warning to error */
          exception->severity = CorruptImageError;
          break;
        }
      /* We are going to be done now */
      if (j+1 == image->colors)
        colormap_initialized=MagickTrue;
    }
  if (!colormap_initialized)
    ThrowXPMReaderException(CorruptImageError,CorruptImage,image);

  /*
    Log the XPM Colormap if logging is enabled.
  */
  if (image->logging)
    {
      char
        name[MaxTextExtent];

      unsigned int
        ii;

      register PixelPacket
        *p;

      /*
        Display image colormap.
      */
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "XPM Colormap (Depth %u):", image->depth);
      p=image->colormap;
      for (ii=0; ii < image->colors; ii++)
        {
          char
            tuple[MaxTextExtent];

          GetColorTuple(p,image->depth,image->matte,False,tuple);
          (void) QueryColorname(image,p,X11Compliance,name,&image->exception);
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "    %" MAGICK_SIZE_T_F "u: %.1024s\t  %.1024s",
                                (MAGICK_SIZE_T) ii,tuple,name);
          p++;
        }
    }

  image->depth=GetImageDepth(image,&image->exception);
  image->depth=NormalizeDepthToOctet(image->depth);

  if (!image_info->ping)
    {
      xpmkey_t
        key = { 0, 0 },
        *keyp;

      xpmkeyval_t
        keyval;

      j = 0;

      /*
        Sort keys by kval
      */
      qsort((void *) keys,image->colors, sizeof(keys[0]), XPMKeyCompare);

#if 0
      for (j=0; j < image->colors; j++)
        printf("Key[%03u] = (0x%04X)\n", keys[j].index, (unsigned int) keys[j].keyval);
#endif

      /*
        Read image pixels.
      */
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Parsing pixels...");
      for (y=0; y < (long) image->rows; y++)
        {
          p=textlist[i++];
          if ((p == (char *) NULL) || (p[0] == '\0'))
            break;
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "    %u: %s", i-1, textlist[i-1]);
          r=SetImagePixelsEx(image,0,y,image->columns,1,exception);
          if (r == (PixelPacket *) NULL)
            break;
          indexes=AccessMutableIndexes(image);
          for (x=0; x < (long) image->columns; x++)
            {
              keyval=0;
              for (k=0; k < width; k++)
                {
                  if (p[k] == '\0')
                    {
                      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                            "Unexpected end of row %ld! (k=%u)", y, k);
                      ThrowXPMReaderException(CorruptImageError,UnexpectedEndOfFile,
                                              image);
                      break;
                    }
                  keyval |= ((xpmkeyval_t) p[k]) << (k * 8);
                }
              if (keyval != key.keyval)
                {
                  key.keyval = keyval;
                  keyp=(void *) bsearch((const void *) &key,(void *) keys,image->colors,
                                        sizeof(keys[0]),XPMKeyCompare);
                  if (keyp != (void *) NULL)
                    {
                      key.index = keyp->index;
                    }
                  else
                    {
                      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                            "Failed to find key! (0x%04X)",
                                            key.keyval);
                      ThrowXPMReaderException(CorruptImageError,CorruptImage,
                                              image);
                      break;
                    }
                }

              VerifyColormapIndex(image,key.index);
              if (image->storage_class == PseudoClass)
                indexes[x]=(IndexPacket) key.index;
              *r=image->colormap[key.index];
              r->opacity=(Quantum)
                (key.index == none ? TransparentOpacity : OpaqueOpacity);
              r++;
              p+=width;
            }
          if (!SyncImagePixelsEx(image,exception))
            break;
        }
      if (y < (long) image->rows)
        ThrowXPMReaderException(CorruptImageError,InsufficientImageDataInFile,image);
    }
  /*
    Free resources.
  */
  MagickFreeResourceLimitedMemory(keys);
  MagickFreeResourceLimitedMemory(textlist);
  MagickFreeResourceLimitedMemory(xpm_buffer);
  if (image->colors > MaxColormapSize)
    {
      /* Release temporary palette. */
      MagickFreeMemory(image->colormap);
      image->colors = 0;
      image->storage_class = DirectClass;
    }
  CloseBlob(image);
  StopTimer(&image->timer);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r X P M I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterXPMImage adds attributes for the XPM image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterXPMImage method is:
%
%      RegisterXPMImage(void)
%
*/
ModuleExport void RegisterXPMImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("PICON");
  entry->decoder=(DecoderHandler) ReadXPMImage;
  entry->encoder=(EncoderHandler) WritePICONImage;
  entry->adjoin=False;
  entry->description="Personal Icon";
  entry->module="XPM";
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("PM");
  entry->decoder=(DecoderHandler) ReadXPMImage;
  entry->encoder=(EncoderHandler) WriteXPMImage;
  entry->adjoin=False;
  entry->stealth=True; /* Don't list in '-list format' output */
  entry->description="X Windows system pixmap (color)";
  entry->module="XPM";
  (void) RegisterMagickInfo(entry);

  entry=SetMagickInfo("XPM");
  entry->decoder=(DecoderHandler) ReadXPMImage;
  entry->encoder=(EncoderHandler) WriteXPMImage;
  entry->magick=(MagickHandler) IsXPM;
  entry->adjoin=False;
  entry->description="X Windows system pixmap (color)";
  entry->module="XPM";
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r X P M I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterXPMImage removes format registrations made by the
%  XPM module from the list of supported formats.
%
%  The format of the UnregisterXPMImage method is:
%
%      UnregisterXPMImage(void)
%
*/
ModuleExport void UnregisterXPMImage(void)
{
  (void) UnregisterMagickInfo("PICON");
  (void) UnregisterMagickInfo("PM");
  (void) UnregisterMagickInfo("XPM");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e P I C O N I m a g e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Procedure WritePICONImage writes an image to a file in the Personal Icon
%  format.
%
%  The format of the WritePICONImage method is:
%
%      unsigned int WritePICONImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WritePICONImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/
static unsigned int WritePICONImage(const ImageInfo *image_info,Image *image)
{
#define ColormapExtent  155
#define GraymapExtent  95
#define PiconGeometry  "48x48>"

  static const unsigned char
    Colormap[]=
    {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x06, 0x00, 0x05, 0x00, 0xf4, 0x05,
      0x00, 0x00, 0x00, 0x00, 0x2f, 0x4f, 0x4f, 0x70, 0x80, 0x90, 0x7e, 0x7e,
      0x7e, 0xdc, 0xdc, 0xdc, 0xff, 0xff, 0xff, 0x00, 0x00, 0x80, 0x00, 0x00,
      0xff, 0x1e, 0x90, 0xff, 0x87, 0xce, 0xeb, 0xe6, 0xe6, 0xfa, 0x00, 0xff,
      0xff, 0x80, 0x00, 0x80, 0xb2, 0x22, 0x22, 0x2e, 0x8b, 0x57, 0x32, 0xcd,
      0x32, 0x00, 0xff, 0x00, 0x98, 0xfb, 0x98, 0xff, 0x00, 0xff, 0xff, 0x00,
      0x00, 0xff, 0x63, 0x47, 0xff, 0xa5, 0x00, 0xff, 0xd7, 0x00, 0xff, 0xff,
      0x00, 0xee, 0x82, 0xee, 0xa0, 0x52, 0x2d, 0xcd, 0x85, 0x3f, 0xd2, 0xb4,
      0x8c, 0xf5, 0xde, 0xb3, 0xff, 0xfa, 0xcd, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x21, 0xf9, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00,
      0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0x00, 0x05, 0x18, 0x20, 0x10, 0x08,
      0x03, 0x51, 0x18, 0x07, 0x92, 0x28, 0x0b, 0xd3, 0x38, 0x0f, 0x14, 0x49,
      0x13, 0x55, 0x59, 0x17, 0x96, 0x69, 0x1b, 0xd7, 0x85, 0x00, 0x3b,
    },
    Graymap[]=
    {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x04, 0x00, 0x04, 0x00, 0xf3, 0x0f,
      0x00, 0x00, 0x00, 0x00, 0x12, 0x12, 0x12, 0x21, 0x21, 0x21, 0x33, 0x33,
      0x33, 0x45, 0x45, 0x45, 0x54, 0x54, 0x54, 0x66, 0x66, 0x66, 0x78, 0x78,
      0x78, 0x87, 0x87, 0x87, 0x99, 0x99, 0x99, 0xab, 0xab, 0xab, 0xba, 0xba,
      0xba, 0xcc, 0xcc, 0xcc, 0xde, 0xde, 0xde, 0xed, 0xed, 0xed, 0xff, 0xff,
      0xff, 0x21, 0xf9, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00,
      0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x04, 0x0c, 0x10, 0x04, 0x31,
      0x48, 0x31, 0x07, 0x25, 0xb5, 0x58, 0x73, 0x4f, 0x04, 0x00, 0x3b,
    };

#define MaxCixels  92

  static const char
    Cixel[MaxCixels+1] = " .XoO+@#$%&*=-;:>,<1234567890qwertyuipasdfghjk"
                         "lzxcvbnmMNBVCZASDFGHJKLPIUYTREWQ!~^/()_`'][{}|";

  char
    buffer[MaxTextExtent],
    basename[MaxTextExtent],
    name[MaxTextExtent],
    symbol[MaxTextExtent];

  Image
    *picon,
    *map;

  int
    j;

  long
    k,
    y;

  RectangleInfo
    geometry;

  register const PixelPacket
    *p;

  register long
    i,
    x;

  register PixelPacket
    *q;

  unsigned int
    status,
    transparent;

  unsigned long
    characters_per_pixel,
    colors;

  ImageCharacteristics
    characteristics;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  /*
    Open output image file.
  */
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  /*
    Ensure that image is in an RGB space.
  */
  (void) TransformColorspace(image,RGBColorspace);
  /*
    Analyze image to be written.
  */
  if (!GetImageCharacteristics(image,&characteristics,
                               (OptimizeType == image_info->type),
                               &image->exception))
    {
      CloseBlob(image);
      return MagickFail;
    }
  SetGeometry(image,&geometry);
  (void) GetMagickGeometry(PiconGeometry,&geometry.x,&geometry.y,
    &geometry.width,&geometry.height);
  picon=ThumbnailImage(image,geometry.width,geometry.height,&image->exception);
  if ((image_info->type != TrueColorType) &&
      (characteristics.grayscale))
    map=BlobToImage(image_info,Graymap,GraymapExtent,&image->exception);
  else
    map=BlobToImage(image_info,Colormap,ColormapExtent,&image->exception);
  if ((picon == (Image *) NULL) || (map == (Image *) NULL))
    return(False);
  status=MapImage(picon,map,image_info->dither);
  DestroyImage(map);
  transparent=False;
  if (picon->storage_class == PseudoClass)
    {
      CompressImageColormap(picon);
      if (picon->matte)
        transparent=True;
    }
  else
    {
      /*
        Convert DirectClass to PseudoClass picon.
      */
      if (picon->matte)
        {
          /*
            Map all the transparent pixels.
          */
          for (y=0; y < (long) picon->rows; y++)
          {
            q=GetImagePixels(picon,0,y,picon->columns,1);
            if (q == (PixelPacket *) NULL)
              break;
            for (x=0; x < (long) picon->columns; x++)
            {
              if (q->opacity == TransparentOpacity)
                transparent=True;
              else
                q->opacity=OpaqueOpacity;
              q++;
            }
            if (!SyncImagePixels(picon))
              break;
          }
        }
      (void) SetImageType(picon,PaletteType);
    }
  colors=picon->colors;
  if (transparent)
    {
      colors++;
      MagickReallocMemory(PixelPacket *,picon->colormap,colors*sizeof(PixelPacket));
      if (picon->colormap == (PixelPacket *) NULL)
        ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,picon);
      picon->colormap[colors-1].red=picon->colormap[colors-1].green=picon->colormap[colors-1].blue=0;
      picon->colormap[colors-1].opacity=TransparentOpacity;
      for (y=0; y < (long) picon->rows; y++)
      {
        register IndexPacket
          *indexes;

        q=GetImagePixels(picon,0,y,picon->columns,1);
        if (q == (PixelPacket *) NULL)
          break;
        indexes=AccessMutableIndexes(picon);
        for (x=0; x < (long) picon->columns; x++)
        {
          if (q->opacity == TransparentOpacity)
            indexes[x]=(IndexPacket) picon->colors;
          q++;
        }
        if (!SyncImagePixels(picon))
          break;
      }
    }
  /*
    Compute the character per pixel.
  */
  characters_per_pixel=1;
  for (k=MaxCixels; (long) colors > k; k*=MaxCixels)
    characters_per_pixel++;
  /*
    XPM header.
  */
  (void) WriteBlobString(image,"/* XPM */\n");
  GetPathComponent(picon->filename,BasePath,basename);
  (void) FormatString(buffer,"static char *%.1024s[] = {\n",basename);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image,"/* columns rows colors chars-per-pixel */\n");
  FormatString(buffer,"\"%lu %lu %lu %ld\",\n",picon->columns,picon->rows,
    colors,characters_per_pixel);
  (void) WriteBlobString(image,buffer);
  for (i=0; i < (long) colors; i++)
  {
    /*
      Define XPM color.
    */
    picon->colormap[i].opacity=OpaqueOpacity;
    (void) QueryColorname(picon,picon->colormap+i,XPMCompliance,name,
      &picon->exception);
    if (transparent)
      {
        if (i == (long) (colors-1))
          (void) strlcpy(name,"grey75",sizeof(name));
      }
    /*
      Write XPM color.
    */
    k=i % MaxCixels;
    symbol[0]=Cixel[k];
    for (j=1; j < (long) characters_per_pixel; j++)
    {
      k=((i-k)/MaxCixels) % MaxCixels;
      symbol[j]=Cixel[k];
    }
    symbol[j]='\0';
    FormatString(buffer,"\"%.1024s c %.1024s\",\n",symbol,name);
    (void) WriteBlobString(image,buffer);
  }
  /*
    Define XPM pixels.
  */
  (void) WriteBlobString(image,"/* pixels */\n");
  for (y=0; y < (long) picon->rows; y++)
  {
    register const IndexPacket
      *indexes;

    p=AcquireImagePixels(picon,0,y,picon->columns,1,&picon->exception);
    if (p == (const PixelPacket *) NULL)
      break;
    indexes=AccessImmutableIndexes(picon);
    (void) WriteBlobString(image,"\"");
    for (x=0; x < (long) picon->columns; x++)
    {
      k=indexes[x] % MaxCixels;
      symbol[0]=Cixel[k];
      for (j=1; j < (long) characters_per_pixel; j++)
      {
        k=(((int) indexes[x]-k)/MaxCixels) % MaxCixels;
        symbol[j]=Cixel[k];
      }
      symbol[j]='\0';
      (void) strlcpy(buffer,symbol,MaxTextExtent);
      (void) WriteBlobString(image,buffer);
    }
    FormatString(buffer,"\"%.1024s\n",
      (y == (long) (picon->rows-1) ? "" : ","));
    (void) WriteBlobString(image,buffer);
    if (QuantumTick(y,picon->rows))
      if (!MagickMonitorFormatted(y,picon->rows,&image->exception,
                                  SaveImageText,image->filename,
                                  image->columns,image->rows))
        break;
  }
  DestroyImage(picon);
  (void) WriteBlobString(image,"};\n");
  status &= CloseBlob(image);
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e X P M I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Procedure WriteXPMImage writes an image to a file in the X pixmap format.
%
%  The format of the WriteXPMImage method is:
%
%      unsigned int WriteXPMImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteXPMImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/
static unsigned int WriteXPMImage(const ImageInfo *image_info,Image *image)
{
#define MaxCixels  92

  static const char
    Cixel[MaxCixels+1] = " .XoO+@#$%&*=-;:>,<1234567890qwertyuipasdfghjk"
                         "lzxcvbnmMNBVCZASDFGHJKLPIUYTREWQ!~^/()_`'][{}|";

  char
    buffer[MaxTextExtent],
    basename[MaxTextExtent],
    name[MaxTextExtent],
    symbol[MaxTextExtent];

  int
    j;

  long
    k,
    y;

  register const PixelPacket
    *p;

  register long
    i,
    x;

  register PixelPacket
    *q;

  unsigned int
    status,
    transparent;

  unsigned long
    characters_per_pixel,
    colors;

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
    Limit color resolution to what XPM can traditionally handle
  */
  if (image->depth > 16)
    image->depth=16;
  transparent=False;
  if (image->storage_class == PseudoClass)
    {
      CompressImageColormap(image);
      if (image->matte)
        transparent=True;
    }
  else
    {
      /*
        Convert DirectClass to PseudoClass image.
      */
      if (image->matte)
        {
          /*
            Map all the transparent pixels.
          */
          for (y=0; y < (long) image->rows; y++)
          {
            q=GetImagePixels(image,0,y,image->columns,1);
            if (q == (PixelPacket *) NULL)
              break;
            for (x=0; x < (long) image->columns; x++)
            {
              if (q->opacity == TransparentOpacity)
                transparent=True;
              else
                q->opacity=OpaqueOpacity;
              q++;
            }
            if (!SyncImagePixels(image))
              break;
          }
        }
      (void) SetImageType(image,PaletteType);
    }
  colors=image->colors;
  if (transparent)
    {
      colors++;
      MagickReallocMemory(PixelPacket *,image->colormap,colors*sizeof(PixelPacket));
      if (image->colormap == (PixelPacket *) NULL)
        ThrowWriterException(ResourceLimitError,MemoryAllocationFailed,image);
      image->colormap[colors-1].red=image->colormap[colors-1].green=image->colormap[colors-1].blue=0;
      image->colormap[colors-1].opacity=TransparentOpacity;
      for (y=0; y < (long) image->rows; y++)
      {
        register IndexPacket
          *indexes;

        q=GetImagePixels(image,0,y,image->columns,1);
        if (q == (PixelPacket *) NULL)
          break;
        indexes=AccessMutableIndexes(image);
        for (x=0; x < (long) image->columns; x++)
        {
          if (q->opacity == TransparentOpacity)
            indexes[x]=(IndexPacket) image->colors;
          q++;
        }
        if (!SyncImagePixels(image))
          break;
      }
    }
  /*
    Compute the character per pixel.
  */
  characters_per_pixel=1;
  for (k=MaxCixels; (long) colors > k; k*=MaxCixels)
    characters_per_pixel++;
  /*
    XPM header.
  */
  (void) WriteBlobString(image,"/* XPM */\n");
  GetPathComponent(image->filename,BasePath,basename);
  (void) FormatString(buffer,"static char *%.1024s[] = {\n",basename);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image,"/* columns rows colors chars-per-pixel */\n");
  FormatString(buffer,"\"%lu %lu %lu %ld\",\n",image->columns,
    image->rows,colors,characters_per_pixel);
  (void) WriteBlobString(image,buffer);
  for (i=0; i < (long) colors; i++)
  {
    /*
      Define XPM color.
    */
    image->colormap[i].opacity=OpaqueOpacity;
    (void) QueryColorname(image,image->colormap+i,XPMCompliance,name,
      &image->exception);
    if (transparent)
      {
        if (i == (long) (colors-1))
          (void) strlcpy(name,"None",sizeof(name));
      }
    /*
      Write XPM color.
    */
    k=i % MaxCixels;
    symbol[0]=Cixel[k];
    for (j=1; j < (long) characters_per_pixel; j++)
    {
      k=((i-k)/MaxCixels) % MaxCixels;
      symbol[j]=Cixel[k];
    }
    symbol[j]='\0';
    FormatString(buffer,"\"%.1024s c %.1024s\",\n",symbol,name);
    (void) WriteBlobString(image,buffer);
  }
  /*
    Define XPM pixels.
  */
  (void) WriteBlobString(image,"/* pixels */\n");
  for (y=0; y < (long) image->rows; y++)
  {
    register const IndexPacket
      *indexes;

    p=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
    if (p == (const PixelPacket *) NULL)
      break;
    indexes=AccessImmutableIndexes(image);
    (void) WriteBlobString(image,"\"");
    for (x=0; x < (long) image->columns; x++)
    {
      k=indexes[x] % MaxCixels;
      symbol[0]=Cixel[k];
      for (j=1; j < (long) characters_per_pixel; j++)
      {
        k=(((int) indexes[x]-k)/MaxCixels) % MaxCixels;
        symbol[j]=Cixel[k];
      }
      symbol[j]='\0';
      (void) strlcpy(buffer,symbol,MaxTextExtent);
      (void) WriteBlobString(image,buffer);
    }
    FormatString(buffer,"\"%.1024s\n",
      (y == (long) (image->rows-1) ? "" : ","));
    (void) WriteBlobString(image,buffer);
    if (QuantumTick(y,image->rows))
      if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                  SaveImageText,image->filename,
                                  image->columns,image->rows))
        break;
  }
  (void) WriteBlobString(image,"};\n");
  status &= CloseBlob(image);
  return(status);
}
