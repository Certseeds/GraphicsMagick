/*
% Copyright (C) 2003 - 2023 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                     GraphicsMagick Pixel Cache Methods                      %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1999                                   %
%                                Re-Designed                                  %
%                              Bob Friesenhahn                                %
%                                October 2008                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/blob.h"
#include "magick/constitute.h"
#include "magick/enum_strings.h"
#include "magick/list.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/resource.h"
#include "magick/pixel_cache.h"
#include "magick/semaphore.h"
#include "magick/tempfile.h"
#include "magick/utility.h"
#if defined(HasZLIB)
#include "zlib.h"
#endif

/*
  Define declarations.
*/
/* Maximum read/write size.  Should be no more than INT_MAX */
#define MAGICK_IO_MAX INT_MAX

#if defined(POSIX) && defined(S_IRUSR)
#  define S_MODE     (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#elif defined (MSWINDOWS)
#  define S_MODE     (_S_IREAD | _S_IWRITE)
#else
# define S_MODE      0644
#endif

/*
 Windows open extensions
*/
#if defined(__BORLANDC__)
/* These do not appear to work with Borland C++ */
#  undef _O_RANDOM
#  undef _O_SEQUENTIAL
#  undef _O_SHORT_LIVED
#  undef _O_TEMPORARY
#endif

#if !defined(_O_RANDOM)
# define _O_RANDOM 0
#endif
#if !defined(_O_SEQUENTIAL)
# define _O_SEQUENTIAL 0
#endif
#if !defined(_O_SHORT_LIVED)
# define _O_SHORT_LIVED 0
#endif
#if !defined(_O_TEMPORARY)
# define _O_TEMPORARY 0
#endif


/*
  Declare pixel cache interfaces.
*/
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

  typedef magick_uint64_t pixel_off_t;

  /*
    Read only access to a linear pixel region.
  */
  MagickExport const PixelPacket
  *AcquireImagePixelsDirect(const Image *image,
                            const pixel_off_t offset,
                            const unsigned long length,
                            ExceptionInfo *exception);

  /*
    Read/write access to a linear pixel region (existing data read and
    updated).
  */
  extern MagickExport PixelPacket
  *GetImagePixelsDirect(Image *image,
                        const pixel_off_t offset,
                        const unsigned long length,
                        ExceptionInfo *exception);

  /*
    Write access to a linear pixel region (existing data ignored).
  */
  extern MagickExport PixelPacket
  *SetImagePixelsDirect(Image *image,
                        const pixel_off_t offset,
                        const unsigned long length,
                        ExceptionInfo *exception);


/*
  Indexes are valid if the image storage class is PseudoClass or the
  colorspace is CMYK.
*/
#define PixelCacheImageIndexesValid(image)      \
  ((image->storage_class == PseudoClass) ||     \
   (image->colorspace == CMYKColorspace))

/*
  Enum declaractions.
*/
typedef enum
{
  UndefinedCache, /* Cache is not opened */
  PingCache,      /* Cache is ignored */
  MemoryCache,    /* Cache is a heap memory allocation */
  DiskCache,      /* Cache is a file accessed via read/write */
  MapCache        /* Cache is a file accessed via memory map */
} CacheType;

/*
  CacheInfo represents the underlying raster image.
*/
typedef struct _CacheInfo
{
  /* Image width */
  unsigned long columns;

  /* Image height */
  unsigned long rows;

  /* Offset to pixels in cache file (constrained to positive range of magick_off_t) */
  magick_uint64_t offset;

  /* Length of pixels region (constrained to positive range of magick_off_t) */
  magick_uint64_t length;

  /* Image pixels if memory resident */
  PixelPacket *pixels;

  /* Image indexes if memory resident */
  IndexPacket *indexes;

  /* Ping, Memory, Disk, Map */
  CacheType type;

  /* Image indexes are valid */
  MagickBool indexes_valid;

  /* Total pixels limit */
  magick_uint64_t limit_pixels;

  /* Maximum width (limited to LONG_MAX) */
  unsigned long limit_width;

  /* Maximum height (limited to LONG_MAX) */
  unsigned long limit_height;

  /* The number of Image structures referencing this cache */
  long reference_count;

  /* MagickTrue if cache is read only */
  MagickBool read_only;

  /* MagickTrue if logging cache events */
  MagickBool logging;

   /* Lock for updating reference count */
  SemaphoreInfo *reference_semaphore;

  /* Lock for file I/O access */
  SemaphoreInfo *file_semaphore;

  /* DirectClass/PseudoClass */
  ClassType storage_class;

  /* CMYKColorspace special due to indexes */
  ColorspaceType colorspace;

  /* Method for dealing with pixels requested outside the image
     boundaries. */
  VirtualPixelMethod virtual_pixel_method;

  /* Open file handle for disk cache */
  int file;

  /* Image file name in form "filename[index]" (for use in logging) */
  char filename[MaxTextExtent];

  /* Pixel cache file name */
  char cache_filename[MaxTextExtent];

  /* Unique number for structure validation */
  unsigned long signature;
} CacheInfo;

/*
  NexusInfo represents a selected region of pixels.
*/
typedef struct _NexusInfo
{
  /* Points to staging or cache_info->pixels+offset */
  PixelPacket *pixels;

  /* Points into staging or cache_info->indexes+offset */
  IndexPacket *indexes;

  /* Allocated copy of pixel data appended by indexes */
  PixelPacket *staging;

  /* Allocation size (in bytes) of pixel staging area */
  size_t staging_length;

  /* Selected region (width, height, x, y) */
  RectangleInfo region;

  /* Nexus pixels are non-strided and in core (sync not needed) */
  MagickBool in_core;

#if 0
  /* FIXME, use: Region starting offset in pixels */
  /* offset=nexus_info->region.y*(magick_off_t) cache_info->columns+nexus_info->region.x */
  magick_off_t region_offset;

  /* FIXME, use: Region linear length in pixels */
  /* length=(nexus_info->region.height-1)*cache_info->columns+nexus_info->region.width-1 */
  magick_uint64_t region_length;

  /* FIXME, use: Pixels are accessed linearly (rather than as a rectangle) */
  MagickBool direct_flag;
#endif

  /* Working NexusInfo for temporary/recursive use */
  struct _NexusInfo *image_nexus;

  /* Unique number for structure validation */
  unsigned long signature;
} NexusInfo;

/*
  View is a handle for a cache nexus as well as remembering which
  image it was allocated from.
*/
typedef struct _View
{
  /* Image that view was allocated from */
  Image *image;

  /* View data */
  NexusInfo nexus_info;

  /* Validation signature */
  unsigned long signature;
} View;

/*
  A vector of thread views.

  FIXME: Make default views into array allocation

  Relevant functions:

  exported: AllocateThreadViewSet() / DestroyThreadViewSet()
  exported: OpenCacheView() / CloseCacheView()
  static: InitializeCacheView() / DeinitializeCacheView()
  exported: AccessDefaultCacheView()
  static: AccessDefaultCacheViewInlined()

*/
typedef struct _ThreadViewSet
{
  size_t
    nviews;

  ViewInfo
    *views;

} ThreadViewSet;

/*
  Cache view interfaces.
*/

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

/*
  Forward declaration.
*/

/*

  Read data into buffer 'buffer', with size 'length', from file
  descriptor 'file' at offset 'offset'. Care is taken to make sure
  that all data requested is read if system calls are interrupted by
  signals.

*/
static ssize_t
FilePositionRead(int file, void *buffer, size_t length,magick_off_t offset)
{
  register ssize_t
    count=0;

  register size_t
    total_count;

  MAGICK_POSIX_IO_SIZE_T
    io_size;

#if !HAVE_PREAD
  if ((MagickSeek(file,offset,SEEK_SET)) < 0)
    return (ssize_t)-1;
#endif

  for (total_count=0; total_count < length; total_count+=count)
    {
      char
        *io_buff_address;

      size_t
        requested_io_size;

#if HAVE_PREAD
      off_t
        io_file_offset;
#endif

      requested_io_size=length-total_count;
      io_buff_address=(char *) buffer+total_count;
      if (requested_io_size > MAGICK_IO_MAX)
        io_size=MAGICK_IO_MAX;
      else
        io_size=(MAGICK_POSIX_IO_SIZE_T) requested_io_size;
#if HAVE_PREAD
      io_file_offset=offset+total_count;
      count=pread(file,io_buff_address,io_size,io_file_offset);
#else
      count=read(file,io_buff_address,io_size);
#endif
      if (count <= 0)
        break;
    }
  if (count < 0)
    return (ssize_t)-1;
  return (ssize_t) total_count;
}
/*

  Write data pointed to by 'buffer', with size 'length', to file
  descriptor 'file' at specified offset 'offset'.  Care is taken to
  make sure that all data is written if system calls are interrupted
  by signals.

*/
static ssize_t
FilePositionWrite(int file, const void *buffer,size_t length,magick_off_t offset)
{
  register ssize_t
    count=0;

  register size_t
    total_count;

  MAGICK_POSIX_IO_SIZE_T
    io_size;

#if !HAVE_PWRITE
  if ((MagickSeek(file,offset,SEEK_SET)) < 0)
    return (ssize_t)-1;
#endif /* !HAVE_PWRITE */
  for (total_count=0; total_count < length; total_count+=count)
    {
      char
        *io_buff_address;

      size_t
        requested_io_size;

#if HAVE_PWRITE
      off_t
        io_file_offset;
#endif

      io_buff_address=(char *) buffer+total_count;
      requested_io_size=length-total_count;
      if (requested_io_size > MAGICK_IO_MAX)
        io_size=MAGICK_IO_MAX;
      else
        io_size=(MAGICK_POSIX_IO_SIZE_T) requested_io_size;
#if HAVE_PWRITE
      io_file_offset=offset+total_count;
      count=pwrite(file,io_buff_address,io_size,io_file_offset);
#else
      count=write(file,io_buff_address,io_size);
#endif
      if (count <= 0)
        break;
    }
  if (count < 0)
    return (ssize_t)-1;
  return (ssize_t) total_count;
}

static NexusInfo *InitializeCacheNexus(NexusInfo * restrict nexus_info)
{
  if (nexus_info != ((NexusInfo *) NULL))
    {
      (void) memset(nexus_info,0,sizeof(NexusInfo));
      nexus_info->signature=MagickSignature;
    }
  return nexus_info;
}

static void DeinitializeCacheNexus(NexusInfo *nexus_info)
{
  if (nexus_info != (NexusInfo *) NULL)
    {
      if (nexus_info->staging_length > 0)
        {
          LiberateMagickResource(MemoryResource,nexus_info->staging_length);
          nexus_info->staging_length=0;
        }
      MagickFreeAlignedMemory(nexus_info->staging);
      if (nexus_info->image_nexus != (NexusInfo *) NULL)
        {
          DeinitializeCacheNexus(nexus_info->image_nexus);
          MagickFreeAlignedMemory(nexus_info->image_nexus);
          nexus_info->image_nexus=(NexusInfo *) NULL;
        }
    }
}

static void InitializeCacheView(Image * restrict image,
                                View * restrict view)
{
  view->image=image;
  (void) InitializeCacheNexus(&view->nexus_info);
  view->signature=MagickSignature;
}

static void DeinitializeCacheView(View *view_info)
{
  assert(view_info->signature == MagickSignature);
  assert(view_info->nexus_info.signature == MagickSignature);
  DeinitializeCacheNexus(&view_info->nexus_info);
}

void
DestroyThreadViewSet(ThreadViewSet *view_set)
{
  unsigned int
    i;

  if (view_set != (ThreadViewSet *) NULL)
    {
      if (view_set->views != (ViewInfo *) NULL)
        {
          for (i=0; i < view_set->nviews; i++)
            {
              if (view_set->views[i] != (ViewInfo *) NULL)
                {
                  CloseCacheView(view_set->views[i]);
                  view_set->views[i]=(ViewInfo *) NULL;
                }
            }
          MagickFreeMemory(view_set->views);
        }
      MagickFreeMemory(view_set);
    }
}

ThreadViewSet *
AllocateThreadViewSet(Image *image,ExceptionInfo *exception)
{
  ThreadViewSet
    *view_set;

  size_t
    nviews;

  size_t
    i;

  MagickPassFail
    status=MagickPass;

  ARG_NOT_USED(exception);

  nviews=omp_get_max_threads();

  view_set=MagickAllocateMemory(ThreadViewSet *,
                                sizeof(ThreadViewSet));

  if (view_set == (ThreadViewSet *) NULL)
    MagickFatalError3(ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToAllocateCacheView);
  view_set->nviews=nviews;
  view_set->views=MagickAllocateArray(ViewInfo *,view_set->nviews,sizeof(ViewInfo *));
  if (view_set->views == (ViewInfo *) NULL)
    {
      ThrowException(exception,CacheError,UnableToAllocateCacheView,
                     image->filename);
      status=MagickFail;
    }

  if (view_set->views != (ViewInfo *) NULL)
    for (i=0; i < view_set->nviews; i++)
      {
        view_set->views[i]=OpenCacheView(image);
        if (view_set->views[i] == (ViewInfo *) NULL)
          {
            ThrowException(exception,CacheError,UnableToAllocateCacheView,
                           image->filename);
            status=MagickFail;
          }
      }

  if (status == MagickFail)
    {
      DestroyThreadViewSet(view_set);
      view_set=(ThreadViewSet *) NULL;
    }

  return view_set;
}

/*
  Obtain the view corresponding to the current thread from the thread
  view set.  The compiler should normally automatically inline this
  function when used in this module.  Since we don't trust that, we
  also provide a static inlined version along with a macro to remap
  code from this module to use the inline version.
*/

MagickExport ViewInfo
*AccessDefaultCacheView(const Image *image)
{
  return (ViewInfo *) image->default_views->views[omp_get_thread_num()];
}

static inline ViewInfo
*AccessDefaultCacheViewInlined(const Image *image)
{
  return (ViewInfo *) image->default_views->views[omp_get_thread_num()];
}
#if !defined(AccessDefaultCacheView)
#  define AccessDefaultCacheView(image) AccessDefaultCacheViewInlined(image)
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   S e t N e x u s                                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetNexus() defines the region of the cache for the specified cache nexus.
%
%  The format of the SetNexus() method is:
%
%      PixelPacket *SetNexus(const Image *image,const long x,const long y,
%        const unsigned long columns, const unsigned long rows,
%        NexusInfo *nexus_info, MagickBool set, ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pixels: SetNexus() returns a pointer to the pixels associated with
%      the specified cache nexus.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o nexus_info: specifies which cache nexus to set.
%
%    o set: Set to one if pixels are being updated/set rather than read.
%
%    o exception: any error is reported here.
%
%
*/
static PixelPacket *
SetNexus(const Image * restrict image,const long x,const long y,
         const unsigned long columns, const unsigned long rows,
         NexusInfo * restrict nexus_info, MagickBool set, ExceptionInfo *exception)
{
  const CacheInfo
    * restrict cache_info;

  char
    message[MaxTextExtent];

  size_t
    length,
    packet_size,
    region_pixels;

  ARG_NOT_USED(exception);
  assert(image != (const Image *) NULL);
  cache_info=(const CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
#if 0
  fprintf(stderr,"SetNexus(): cache_info: %lux%lu,"
          " region: %lux%lu%+ld%+ld, cache_info->type: %u\n",
          cache_info->columns, cache_info->rows,
          columns, rows, x,y, cache_info->type);
#endif
  if ((columns == 0) || (rows == 0))
    {
      ThrowException(exception,CacheError,EmptyCacheNexus,
                     image->filename);
      return (PixelPacket *) NULL;
    }

  if ((cache_info->type != PingCache) &&
      (cache_info->type != DiskCache) &&
      (/* Region must entirely be in bounds of image raster */
       (x >= 0) && (y >= 0) && ((y+rows) <= cache_info->rows)
       ) &&
      ((/* All/part of one row */
        (rows == 1) && ((x+columns) <= cache_info->columns)
        )
       ||
       (/* One or more full rows */
        (x == 0) && (columns == cache_info->columns)
        )) &&
      (*ImageGetClipMaskInlined(image) == (const Image *) NULL) &&
      (*ImageGetCompositeMaskInlined(image) == (const Image *) NULL))
    {
      /*
        Pixels are accessed directly from memory.
      */
      size_t
        offset;

      offset=((size_t) y)*cache_info->columns+((size_t) x);

      nexus_info->pixels=cache_info->pixels+offset;
      nexus_info->indexes=(IndexPacket *) NULL;
      if (cache_info->indexes_valid)
        nexus_info->indexes=cache_info->indexes+offset;
      nexus_info->in_core=MagickTrue;
      nexus_info->region.x=x;
      nexus_info->region.y=y;
      nexus_info->region.width=columns;
      nexus_info->region.height=rows;
      /* fprintf(stderr,"Pixels in core (%p)\n",nexus_info->pixels); */
      return(nexus_info->pixels);
    }

  /*
    Pixels are stored in a staging area until they are synced to the cache.
  */
  region_pixels=(size_t) columns*rows;
  packet_size=sizeof(PixelPacket);
  if (cache_info->indexes_valid)
    packet_size+=sizeof(IndexPacket);
  length=region_pixels*packet_size;
  if ((region_pixels/columns != rows) ||
      (length/packet_size != region_pixels) ||
      (length != (size_t) ((magick_off_t) length)))
    {
      ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,
                     image->filename);
      return (PixelPacket *) NULL;
    }
  if (length < MAGICK_CACHE_LINE_SIZE)
    length=MAGICK_CACHE_LINE_SIZE;

  /*
    Require that nexus tile observe same width, height, total
    pixels, and memory requirements as imposed on images.
  */
  /* total pixels */
  if (region_pixels > cache_info->limit_pixels)
    {
      errno=0;
      FormatString(message,
                   "Total pixels %" MAGICK_SIZE_T_F "u > %" MAGICK_UINT64_F "u \"%.1024s\"",
                   (MAGICK_SIZE_T) region_pixels,
                   cache_info->limit_pixels,image->filename);
      ThrowException(exception,ResourceLimitError,NexusPixelLimitExceeded,
                     message);
      return (PixelPacket *) NULL;
    }
  /* width */
  if (!(columns <= cache_info->limit_width))
    {
      errno=0;
      FormatString(message,"Width %lu > %lu \"%.1024s\"",
                   columns,cache_info->limit_width,image->filename);
      ThrowException(exception,ResourceLimitError,NexusPixelWidthLimitExceeded,
                     message);
      return (PixelPacket *) NULL;
    }
  if (x >= 0 ? ((unsigned long) x >= cache_info->limit_width) :
      (x <= -(long) cache_info->limit_width))
    {
      errno=0;
      FormatString(message,"Xoffset abs(%ld) > %lu \"%.1024s\"",
                   x,cache_info->limit_width,image->filename);
      ThrowException(exception,ResourceLimitError,NexusPixelWidthLimitExceeded,
                     message);
      return (PixelPacket *) NULL;
    }

  /* height */
  if (!(rows <= cache_info->limit_height))
    {
      errno=0;
      FormatString(message,"Height %lu > %lu \"%.1024s\"",
                   rows,cache_info->limit_height,image->filename);
      ThrowException(exception,ResourceLimitError,NexusPixelHeightLimitExceeded,
                     message);
      return (PixelPacket *) NULL;
    }
  if (y >= 0 ? ((unsigned long) y >= cache_info->limit_height) :
      (y <= -(long) cache_info->limit_height))
    {
      errno=0;
      FormatString(message,"Y offset abs(%ld) > %lu \"%.1024s\"",
                   y,cache_info->limit_height,image->filename);
      ThrowException(exception,ResourceLimitError,NexusPixelHeightLimitExceeded,
                     message);
      return (PixelPacket *) NULL;
    }

  /*
    If pixels are being set, then require that at least part of the
    region includes the image pixels.

    This code used to be executed by SetCacheNexus() so value ranges
    could be sanitized before doing the signed arithmetic.
  */
  if (set)
    {
      magick_off_t
        offset;

      magick_uint64_t
        number_pixels = 0;

      offset=y*(magick_off_t) cache_info->columns+x;
      if (offset >= 0)
        {
          number_pixels=(magick_uint64_t) cache_info->columns*cache_info->rows;
          offset+=(rows-1)*(magick_off_t) cache_info->columns+columns-1;
        }
      if ((offset < 0) || ((magick_uint64_t) offset >= number_pixels))
        return (PixelPacket *) NULL;
    }

  if ((nexus_info->staging == (PixelPacket *) NULL) ||
      (nexus_info->staging_length < length))
    {
#if 0
      fprintf(stderr,"%s: Allocating %zu bytes for nexus_info region %lux%lu%+ld%+ld\n",
              __func__, length, columns, rows, x, y);
#endif

      /* memory */
      if (nexus_info->staging_length > 0)
        LiberateMagickResource(MemoryResource,nexus_info->staging_length);
      nexus_info->staging_length=0;
      MagickFreeAlignedMemory(nexus_info->staging);

      if (AcquireMagickResource(MemoryResource,length) == MagickPass)
        nexus_info->staging=MagickAllocateAlignedMemory(PixelPacket *,
                                                        MAGICK_CACHE_LINE_SIZE,
                                                        length);
      if (nexus_info->staging != (PixelPacket *) NULL)
        {
          nexus_info->staging_length=length;
          (void) memset((void *) nexus_info->staging,0,nexus_info->staging_length);
        }
    }
  nexus_info->pixels=nexus_info->staging;
  nexus_info->indexes=(IndexPacket *) NULL;
  if ((cache_info->indexes_valid) &&
      (nexus_info->pixels != (PixelPacket *) NULL))
    nexus_info->indexes=(IndexPacket *) (nexus_info->pixels+region_pixels);
  if (nexus_info->pixels == (PixelPacket *) NULL)
    {
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "Failed to allocate %" MAGICK_SIZE_T_F
                            "u bytes for nexus staging "
                            "(region pixels=%" MAGICK_SIZE_T_F "u, "
                            "region width=%lu, "
                            "region height=%lu, "
                            "cache columns=%lu)!",
                            (MAGICK_SIZE_T) length,
                            (MAGICK_SIZE_T) region_pixels,
                            columns,
                            rows,
                            cache_info->columns);
      ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,
                     image->filename);
      nexus_info->region.width=0;
      nexus_info->region.height=0;
      nexus_info->region.x=0;
      nexus_info->region.y=0;
      nexus_info->in_core=MagickFalse;
    }
  else
    {
      nexus_info->region.x=x;
      nexus_info->region.y=y;
      nexus_info->region.width=columns;
      nexus_info->region.height=rows;
      /*
        Determine if pixels associated with the cache nexus are
        non-strided and in core.  If not, then the nexus pixels
        require a sync.
      */
      nexus_info->in_core=MagickFalse;
      if (cache_info->type == PingCache)
        {
          /*
            Some coders *do* read the pixels in 'ping' mode.  Skip sync on
            such pixels.
          */
          nexus_info->in_core=MagickTrue;
        }
      else if (cache_info->pixels != NULL)
        {
          magick_off_t
            offset;

          offset=y*(magick_off_t) cache_info->columns+x;
          if (nexus_info->pixels == (cache_info->pixels+offset))
            nexus_info->in_core=MagickTrue;
        }
    }

  /* fprintf(stderr,"Pixels in staging (%p)\n",nexus_info->pixels); */
  return(nexus_info->pixels);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   S e t C a c h e N e x u s                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetCacheNexus() allocates an area to store image pixels as defined by the
%  region rectangle and returns a pointer to the area.  This area is
%  subsequently transferred from the pixel cache with SyncCacheNexus().  A
%  pointer to the pixels is returned if the pixels are transferred, otherwise
%  a NULL is returned.
%
%  The format of the SetCacheNexus() method is:
%
%      PixelPacket *SetCacheNexus(Image *image,const long x,const long y,
%                     const unsigned long columns,const unsigned long rows,
%                     NexusInfo *nexus_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pixels: SetCacheNexus() returns a pointer to the pixels if they are
%      transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o nexus_info: specifies which cache nexus to set.
%
%    o exception: any error is reported here.
%
*/
static PixelPacket *
SetCacheNexus(Image *image,const long x,const long y,
              const unsigned long columns,const unsigned long rows,
              NexusInfo *nexus_info,ExceptionInfo *exception)
{
  PixelPacket
    *pixels;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  pixels=(PixelPacket *) NULL;
#if 0
  {
    const CacheInfo
      * restrict cache_info = (const CacheInfo * restrict) image->cache;

    if ((cache_info->reference_count != 1) || (cache_info->read_only))
      fprintf(stderr,"SetCacheNexus: Thread %d enters (cache_info = %p, reference_count=%lu, read_only=%u)\n",
              omp_get_thread_num(),image->cache, cache_info->reference_count, cache_info->read_only);
#if 0
    if (cache_info->type == UndefinedCache)
      fprintf(stderr,"SetCacheNexus: Pixel cache is not open!\n");
#endif
    if ((cache_info->storage_class != UndefinedClass) &&
        (image->storage_class != cache_info->storage_class))
      fprintf(stderr,"SetCacheNexus: Pixel cache storage class mismatch! (image: %s, cache: %s)\n",
              ClassTypeToString(image->storage_class),ClassTypeToString(cache_info->storage_class));
#if 0
    if ((cache_info->colorspace != UndefinedColorspace) &&
        (image->colorspace != cache_info->colorspace))
      fprintf(stderr,"SetCacheNexus: Pixel cache colorspace mismatch! (image: %s, cache: %s)\n",
              ColorspaceTypeToString(image->colorspace), ColorspaceTypeToString(cache_info->colorspace));
#endif
  }
#endif


  if (ModifyCache(image,exception) != MagickFail)
    {
      /*
        Return pixel cache.
      */
      pixels=SetNexus(image,x,y,columns,rows,nexus_info,MagickTrue,exception);
#if 0
      if (!pixels)
        fprintf(stderr,"%s: SetNexus returns null (%lux%lu%+ld%+ld)\n",
                __func__,columns,rows,x,y);
#endif
    }

  return pixels;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   R e a d C a c h e I n d e x e s                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadCacheIndexes() reads colormap indexes from the specified region of the
%  pixel cache.
%
%  The format of the ReadCacheIndexes() method is:
%
%      MagickPassFail ReadCacheIndexes(const Cache cache,
%        const NexusInfo *nexus_info)
%
%  A description of each parameter follows:
%
%    o status: ReadCacheIndexes returns MagickPass if the colormap indexes are
%      successfully read from the pixel cache, otherwise MagickFail.
%
%    o cache: Specifies a pointer to a CacheInfo structure.
%
%    o nexus: specifies which cache nexus to read the colormap indexes.
%
%
*/
static MagickPassFail
ReadCacheIndexes(const Cache cache,const NexusInfo *nexus_info,
                 ExceptionInfo *exception)
{
  CacheInfo
    *cache_info;

  magick_uint64_t
    number_pixels;

  magick_off_t
    offset;

  int
    file;

  register IndexPacket
    *indexes;

  register long
    y;

  size_t
    length;

  unsigned long
    rows;

  ARG_NOT_USED(exception);
  assert(cache != (Cache) NULL);
  cache_info=(CacheInfo *) cache;
  assert(cache_info->signature == MagickSignature);
  if (!(cache_info->indexes_valid && (nexus_info->indexes != (IndexPacket *) NULL)))
    return(MagickFail);
  if (nexus_info->in_core)
    return(MagickPass);
  offset=nexus_info->region.y*(magick_off_t) cache_info->columns+nexus_info->region.x;
  length=nexus_info->region.width*sizeof(IndexPacket);
  rows=nexus_info->region.height;
  number_pixels=(magick_uint64_t) length*rows;
  if ((cache_info->columns == nexus_info->region.width) &&
      (number_pixels == (size_t) number_pixels))
    {
      length=number_pixels;
      rows=1;
    }
  y=0;
  indexes=nexus_info->indexes;
  if (cache_info->type != DiskCache)
    {
      /*
        Read indexes from memory.
      */
      register const IndexPacket
        *cache_indexes;

      cache_indexes=cache_info->indexes+offset;
      if (length < 257)
        {
          for (y=0; y < (long) rows; y++)
            {
              register long
                x;

              for (x=0; x < (long) nexus_info->region.width; x++)
                *indexes++=cache_indexes[x];
              cache_indexes+=cache_info->columns;
            }
        }
      else
        {
          for (y=0; y < (long) rows; y++)
            {
              (void) memcpy(indexes,cache_indexes,length);
              indexes+=nexus_info->region.width;
              cache_indexes+=cache_info->columns;
            }
        }
      return(MagickPass);
    }
  /*
    Read indexes from disk.
  */
  LockSemaphoreInfo(cache_info->file_semaphore);
  {
    file=(cache_info->file != -1 ? cache_info->file :
          open(cache_info->cache_filename,O_RDONLY | O_BINARY));
    if (file != -1)
      {
        number_pixels=(magick_uint64_t) cache_info->columns*cache_info->rows;
        for (y=0; y < (long) rows; y++)
          {
            if ((FilePositionRead(file,indexes,length,cache_info->offset+
                                  number_pixels*sizeof(PixelPacket)+offset*
                                  sizeof(IndexPacket))) <= 0)
              break;
            indexes+=nexus_info->region.width;
            offset+=cache_info->columns;
          }
        if (cache_info->file == -1)
          (void) close(file);
        if (QuantumTick(nexus_info->region.y,cache_info->rows))
          (void) LogMagickEvent(CacheEvent,GetMagickModule(),"%lux%lu%+ld%+ld",
                                nexus_info->region.width,nexus_info->region.height,
                                nexus_info->region.x,nexus_info->region.y);
      }
  }
  UnlockSemaphoreInfo(cache_info->file_semaphore);
  if (file == -1)
    return(MagickFail);
  return(y == (long) rows);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   R e a d C a c h e P i x e l s                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadCachePixels() reads pixels from the specified region of the pixel cache.
%
%  The format of the ReadCachePixels() method is:
%
%      MagickPassFail ReadCachePixels(const Cache cache,
%                        const NexusInfo *nexus_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: ReadCachePixels() returns MagickPass if the pixels are
%      successfully read from the pixel cache, otherwise MagickFail.
%
%    o cache: Specifies a pointer to a CacheInfo structure.
%
%    o nexus_info: specifies which cache nexus to read the pixels.
%
%    o exception: any exception is reported here.
%
%
*/
static MagickPassFail
ReadCachePixels(const Cache cache,const NexusInfo *nexus_info,
                ExceptionInfo *exception)
{
  CacheInfo
    *cache_info;

  magick_uint64_t
    number_pixels;

  magick_off_t
    offset;

  int
    file;

  register long
    y;

  register PixelPacket
    *pixels;

  size_t
    length;

  unsigned long
    rows;

  ARG_NOT_USED(exception);
  assert(cache != (Cache) NULL);
  /* printf("ReadCachePixels\n"); */
  cache_info=(CacheInfo *) cache;
  assert(cache_info->signature == MagickSignature);
  if (nexus_info->in_core)
    return(MagickPass);
  offset=nexus_info->region.y*(magick_off_t) cache_info->columns;
  if ((long) (offset/cache_info->columns) != nexus_info->region.y)
    return MagickFail;
  offset += nexus_info->region.x;
  length=nexus_info->region.width*sizeof(PixelPacket);
  if (length/sizeof(PixelPacket) != nexus_info->region.width)
    return MagickFail;
  rows=nexus_info->region.height;
  number_pixels=(magick_uint64_t) length*rows;
  if ((length ==0) || (number_pixels/length != rows))
    return MagickFail;
  if ((cache_info->columns == nexus_info->region.width) &&
      (number_pixels == (size_t) number_pixels))
    {
      length=number_pixels;
      rows=1;
    }
  y=0;
  pixels=nexus_info->pixels;
  if (cache_info->type != DiskCache)
    {
      /*
        Read pixels from memory.
      */
      register const PixelPacket
        *cache_pixels;

      cache_pixels=cache_info->pixels+offset;
      if (length < 257)
        {
          for (y=0; y < (long) rows; y++)
            {
              register long
                x;

              for (x=0; x < (long) nexus_info->region.width; x++)
                *pixels++=cache_pixels[x];
              cache_pixels+=cache_info->columns;
            }
        }
      else
        {
          for (y=0; y < (long) rows; y++)
            {
              (void) memcpy(pixels,cache_pixels,length);
              pixels+=nexus_info->region.width;
              cache_pixels+=cache_info->columns;
            }
        }
      return(MagickPass);
    }
  /*
    Read pixels from disk.
  */
  LockSemaphoreInfo(cache_info->file_semaphore);
  {
    file=(cache_info->file != -1 ? cache_info->file :
          open(cache_info->cache_filename,O_RDONLY | O_BINARY));
    if (file != -1)
      {
        for (y=0; y < (long) rows; y++)
          {
            if ((FilePositionRead(file,pixels,length,
                                  cache_info->offset+offset*
                                  sizeof(PixelPacket))) < (ssize_t) length)
              break;
            pixels+=nexus_info->region.width;
            offset+=cache_info->columns;
          }
        if (cache_info->file == -1)
          (void) close(file);
        if (QuantumTick(nexus_info->region.y,cache_info->rows))
          (void) LogMagickEvent(CacheEvent,GetMagickModule(),"%lux%lu%+ld%+ld",
                                nexus_info->region.width,nexus_info->region.height,
                                nexus_info->region.x,nexus_info->region.y);
      }
  }
  UnlockSemaphoreInfo(cache_info->file_semaphore);
  if (file == -1)
    return(MagickFail);
  return(y == (long) rows);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   W r i t e C a c h e I n d e x e s                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WriteCacheIndexes() writes the colormap indexes to the specified region of
%  the pixel cache.
%
%  The format of the WriteCacheIndexes() method is:
%
%      MagickPassFail WriteCacheIndexes(Cache cache,const NexusInfo *nexus_info)
%
%  A description of each parameter follows:
%
%    o status: WriteCacheIndexes() returns MagickPass if the indexes are
%      successfully written to the pixel cache, otherwise MagickFail.
%
%    o cache: Specifies a pointer to a CacheInfo structure.
%
%    o nexus: specifies which cache nexus to write the colormap indexes.
%
%
*/
static MagickPassFail
WriteCacheIndexes(Cache cache,const NexusInfo *nexus_info)
{
  CacheInfo
    *cache_info;

  magick_uint64_t
    number_pixels;

  magick_off_t
    offset;

  int
    file;

  register IndexPacket
    *indexes;

  register long
    y;

  size_t
    length;

  unsigned long
    rows;

  assert(cache != (Cache) NULL);
  cache_info=(CacheInfo *) cache;
  assert(cache_info->signature == MagickSignature);
  if (!cache_info->indexes_valid)
    return(MagickFail);
  if (nexus_info->in_core)
    return(MagickPass);
  offset=nexus_info->region.y*(magick_off_t) cache_info->columns+nexus_info->region.x;
  length=nexus_info->region.width*sizeof(IndexPacket);
  rows=nexus_info->region.height;
  number_pixels=(magick_uint64_t) length*rows;
  y=0;
  indexes=nexus_info->indexes;
  if (cache_info->type != DiskCache)
    {
      register IndexPacket
        *cache_indexes;

      /*
        Coalesce rows into larger write request if possible.
      */
      if ((cache_info->columns == nexus_info->region.width) &&
          (number_pixels == (size_t) number_pixels))
        {
          length=number_pixels;
          rows=1;
        }

      /*
        Write indexes to memory.
      */
      cache_indexes=cache_info->indexes+offset;
      if (length < 257)
        {
          for (y=0; y < (long) rows; y++)
            {
              register long
                x;

              for (x=0; x < (long) nexus_info->region.width; x++)
                cache_indexes[x]=*indexes++;
              cache_indexes+=cache_info->columns;
            }
        }
      else
        {
          for (y=0; y < (long) rows; y++)
            {
              (void) memcpy(cache_indexes,indexes,length);
              indexes+=nexus_info->region.width;
              cache_indexes+=cache_info->columns;
            }
        }
      return(MagickPass);
    }
  /*
    Write indexes to disk.
  */
  LockSemaphoreInfo(cache_info->file_semaphore);
  {
    file=cache_info->file;
    if (cache_info->file == -1)
      {
        /* FIXME: open */
        file=open(cache_info->cache_filename,O_WRONLY | O_BINARY | O_EXCL,S_MODE);
        if (file == -1)
          file=open(cache_info->cache_filename,O_WRONLY | O_BINARY,S_MODE);
      }
    if (file != -1)
      {
        magick_off_t
          row_offset;

        ssize_t
          bytes_written;

        number_pixels=(magick_uint64_t) cache_info->columns*cache_info->rows;
        row_offset=cache_info->offset+number_pixels*sizeof(PixelPacket)+offset
          *sizeof(IndexPacket);
        for (y=0; y < (long) rows; y++)
          {
            if ((bytes_written=FilePositionWrite(file,indexes,length,row_offset))
                < (long) length)
              {
                (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                                      "Failed to write row %ld at file offset %" MAGICK_OFF_F
                                      "d.  Wrote %" MAGICK_SSIZE_T_F "d rather than %"
                                      MAGICK_SIZE_T_F "u bytes (%s).",
                                      y,
                                      row_offset,
                                      (MAGICK_SSIZE_T) bytes_written,
                                      (MAGICK_SIZE_T) length,
                                      strerror(errno));
                break;
              }
            indexes+=nexus_info->region.width;
            offset+=cache_info->columns;
          }
        if (cache_info->file == -1)
          (void) close(file);
        if (QuantumTick(nexus_info->region.y,cache_info->rows))
          (void) LogMagickEvent(CacheEvent,GetMagickModule(),"%lux%lu%+ld%+ld",
                                nexus_info->region.width,nexus_info->region.height,
                                nexus_info->region.x,nexus_info->region.y);
      }
  }
  UnlockSemaphoreInfo(cache_info->file_semaphore);
  if (file == -1)
    return MagickFail;
  return(y == (long) rows);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   W r i t e C a c h e P i x e l s                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WriteCachePixels() writes image pixels to the specified region of the pixel
%  cache.
%
%  The format of the WriteCachePixels() method is:
%
%      MagickPassFail WriteCachePixels(Cache cache,const NexusInfo *nexus_info)
%
%  A description of each parameter follows:
%
%    o status: WriteCachePixels() returns MagickPass if the pixels are
%      successfully written to the cache, otherwise MagickFail.
%
%    o cache: Specifies a pointer to a Cache structure.
%
%    o nexus: specifies which cache nexus to write the pixels.
%
%
*/
static MagickPassFail
WriteCachePixels(Cache cache,const NexusInfo *nexus_info)
{
  CacheInfo
    *cache_info;

  magick_uint64_t
    number_pixels;

  magick_off_t
    offset;

  int
    file;

  register long
    y;

  register PixelPacket
    *pixels;

  size_t
    length;

  unsigned long
    rows;

  assert(cache != (Cache) NULL);
  cache_info=(CacheInfo *) cache;
  assert(cache_info->signature == MagickSignature);
  if (nexus_info->in_core)
    return(MagickPass);
  offset=nexus_info->region.y*(magick_off_t) cache_info->columns+nexus_info->region.x;
  length=nexus_info->region.width*sizeof(PixelPacket);
  rows=nexus_info->region.height;
  number_pixels=(magick_uint64_t) length*rows;
  y=0;
  pixels=nexus_info->pixels;
  if (cache_info->type != DiskCache)
    {
      register PixelPacket
        *cache_pixels;

      /*
        Coalesce rows into larger write request if possible.
      */
      if ((cache_info->columns == nexus_info->region.width) &&
          (number_pixels == (size_t) number_pixels))
        {
          length=number_pixels;
          rows=1;
        }

      /*
        Write pixels to memory.
      */
      cache_pixels=cache_info->pixels+offset;
      if (length < 257)
        {
          for (y=0; y < (long) rows; y++)
            {
              register long
                x;

              for (x=0; x < (long) nexus_info->region.width; x++)
                cache_pixels[x]=*pixels++;
              cache_pixels+=cache_info->columns;
            }
        }
      else
        {
          for (y=0; y < (long) rows; y++)
            {
              (void) memcpy(cache_pixels,pixels,length);
              pixels+=nexus_info->region.width;
              cache_pixels+=cache_info->columns;
            }
        }
      return(MagickPass);
    }
  /*
    Write pixels to disk.
  */
  LockSemaphoreInfo(cache_info->file_semaphore);
  {
    file=cache_info->file;
    if (cache_info->file == -1)
      {
        file=open(cache_info->cache_filename,O_WRONLY | O_BINARY | O_EXCL,S_MODE);
        if (file == -1)
          file=open(cache_info->cache_filename,O_WRONLY | O_BINARY,S_MODE);
      }
    if (file != -1)
      {
        for (y=0; y < (long) rows; y++)
          {
            magick_off_t
              row_offset;

            ssize_t
              bytes_written;

            row_offset=cache_info->offset+offset*sizeof(PixelPacket);
            if ((bytes_written=FilePositionWrite(file,pixels,length,row_offset))
                < (ssize_t) length)
              {
                (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                                      "Failed to write row %ld at file offset %"
                                      MAGICK_OFF_F "d.  Wrote %"
                                      MAGICK_SSIZE_T_F "d rather than %"
                                      MAGICK_SIZE_T_F "u bytes (%s).",
                                      y,
                                      row_offset,
                                      (MAGICK_SSIZE_T) bytes_written,
                                      (MAGICK_SIZE_T) length,
                                      strerror(errno));
                break;
              }
            pixels+=nexus_info->region.width;
            offset+=cache_info->columns;
          }
        if (cache_info->file == -1)
          (void) close(file);
        if (QuantumTick(nexus_info->region.y,cache_info->rows))
          (void) LogMagickEvent(CacheEvent,GetMagickModule(),"%lux%lu%+ld%+ld",
                                nexus_info->region.width,nexus_info->region.height,
                                nexus_info->region.x,nexus_info->region.y);
      }
  }
  UnlockSemaphoreInfo(cache_info->file_semaphore);
  if (file == -1)
    return(MagickFail);
  return(y == (long) rows);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t C a c h e N e x u s                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetCacheNexus() gets pixels from the in-memory or disk pixel cache as
%  defined by the geometry parameters.   A pointer to the pixels is returned
%  if the pixels are transferred, otherwise a NULL is returned.
%
%  The format of the GetCacheNexus() method is:
%
%      PixelPacket *GetCacheNexus(Image *image,const long x,const long y,
%                     const unsigned long columns,const unsigned long rows,
%                     NexusInfo *nexus_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: GetCacheNexus() returns a pointer to the pixels if they are
%      transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o nexus_info: specifies cache nexus to update
%
%
*/
static PixelPacket *
GetCacheNexus(Image *image,const long x,const long y,
              const unsigned long columns,const unsigned long rows,
              NexusInfo *nexus_info,ExceptionInfo *exception)
{
  PixelPacket
    *pixels;

  /*
    Transfer pixels from the cache.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  /*
    SetCacheNexus() invokes ModifyCache() which may replace the
    current image cache so we obtain the cache *after* invoking
    SetCacheNexus().
  */
  pixels=SetCacheNexus(image,x,y,columns,rows,nexus_info,exception);
  if (pixels != (PixelPacket *) NULL)
    {
      CacheInfo
        *cache_info;

      cache_info=(CacheInfo *) image->cache;
      assert(cache_info->signature == MagickSignature);
      /*
        If underlying image pixels are not already suited for being
        updated in-place, then make a working copy in our cache view
        buffer.
      */
      if (!nexus_info->in_core)
        {
          MagickPassFail
            status;

          status=ReadCachePixels(cache_info,nexus_info,exception);
          if (cache_info->indexes_valid)
            status&=ReadCacheIndexes(cache_info,nexus_info,exception);
          if (status == MagickFail)
            {
              ThrowException(exception,CacheError,UnableToGetPixelsFromCache,
                             image->filename);
              pixels=(PixelPacket *) NULL;
            }
        }
    }
  return(pixels);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   A l l o c a t e C a c h e N e x u s                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AllocateCacheNexus() allocates a cache nexus.  The cache nexus is
%  deallocated via DestroyCacheNexus().  NULL is returned on failure.
%
%  The format of the AllocateCacheNexus() method is:
%
%      NexusInfo *AllocateCacheNexus(void)
%
%  A description of each parameter follows:
%
%
%
*/
static NexusInfo *
AllocateCacheNexus(void)
{
  NexusInfo
    *nexus_info;

  nexus_info=MagickAllocateAlignedMemory(NexusInfo *,MAGICK_CACHE_LINE_SIZE,
                                         sizeof(NexusInfo));
  return InitializeCacheNexus(nexus_info);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   D e s t r o y C a c h e N e x u s                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyCacheNexus() destroys a cache nexus which was allocated via
%  AllocateCacheNexus().
%
%  The format of the DestroyCacheNexus() method is:
%
%      void DestroyCacheNexus(NexusInfo *nexus_info)
%
%  A description of each parameter follows:
%
%    o nexus_info: cache nexus to destroy.
%
%
*/
static void
DestroyCacheNexus(NexusInfo *nexus_info)
{
  if (nexus_info != (NexusInfo *) NULL)
    {
      DeinitializeCacheNexus(nexus_info);
      MagickFreeAlignedMemory(nexus_info);
    }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   A c q u i r e C a c h e N e x u s                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AcquireCacheNexus() acquires pixels from the in-memory or disk pixel cache
%  as defined by the geometry parameters.   A pointer to the pixels is
%  returned if the pixels are transferred, otherwise a NULL is returned.
%
%  The format of the AcquireCacheNexus() method is:
%
%      PixelPacket *AcquireCacheNexus(const Image *image,const long x,
%        const long y,const unsigned long columns,const unsigned long rows,
%        NexusInfo *nexus_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: AcquireCacheNexus() returns a pointer to the pixels if they
%      are transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o nexus_info: specifies which cache nexus to acquire.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
#define EdgeX(x) ((x) < 0 ? 0 : (x) >= (long) cache_info->columns ? \
  (long) cache_info->columns-1 : (x))
#define EdgeY(y) ((y) < 0 ? 0 : (y) >= (long) cache_info->rows ? \
  (long) cache_info->rows-1 : (y))
#define MirrorX(x) ((((x) >= 0) && (x) < (long) cache_info->columns) ? \
  (x) : (long) cache_info->columns-TileX(x)-1L)
#define MirrorY(y) ((((y) >= 0) && (y) < (long) cache_info->rows) ? \
  (y) : (long) cache_info->rows-TileY(y)-1L)
#define TileX(x) (((x) >= 0) ? ((x) % (long) cache_info->columns) : \
  (long) cache_info->columns-(-(x) % (long) cache_info->columns))
#define TileY(y) (((y) >= 0) ? ((y) % (long) cache_info->rows) : \
  (long) cache_info->rows-(-(y) % (long) cache_info->rows))

static const PixelPacket *
AcquireCacheNexus(const Image *image,const long x,const long y,
                  const unsigned long columns,const unsigned long rows,
                  NexusInfo *nexus_info,ExceptionInfo *exception)
{
  CacheInfo
    * restrict cache_info;

  magick_uint64_t
    number_pixels;

  magick_off_t
    offset;

  IndexPacket
    * restrict indexes,
    * restrict nexus_indexes;

  PixelPacket
    * restrict pixels,
    virtual_pixel;

  register const PixelPacket
    *p;

  register long
    u,
    v;

  register PixelPacket
    *q;

  size_t
    length;

  /*
    Acquire pixels.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (Cache) NULL);
  cache_info=(CacheInfo *) image->cache;
  if (cache_info->type == UndefinedCache)
    {
      ThrowException(exception,CacheError,PixelCacheIsNotOpen,
                     image->filename);
      return((const PixelPacket *) NULL);
    }
#if 0
  fprintf(stderr,"AcquireCacheNexus(): image->columns=%lu, image->rows=%lu, "
          "x=%ld, y=%ld, columns=%lu, rows=%lu\n",
          image->columns,image->rows,x,y,columns,rows);
#endif
  if ((image->columns != cache_info->columns) ||
      (image->rows > cache_info->rows))
    {
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "Image dimensions: %lux%lu, "
                            "Cache dimensions: %lux%lu",
                            image->columns, image->rows,
                            cache_info->columns, cache_info->rows);
      ThrowException(exception,CacheError,PixelCacheDimensionsMisMatch,
                     image->filename);
      return((const PixelPacket *) NULL);
    }
  /* Define the region of the cache for the cache nexus */
  pixels=SetNexus(image,x,y,columns,rows,nexus_info,MagickFalse,exception);
  if (pixels == (PixelPacket *) NULL)
    {
#if 0
      fprintf(stderr,"%s: SetNexus returns null (%lux%lu%+ld%+ld)\n",
              __func__,columns,rows,x,y);
#endif
      return((const PixelPacket *) NULL);
    }
  offset=y*(magick_off_t) cache_info->columns+x;
  length=(size_t) (rows-1)*cache_info->columns+columns-1;
  number_pixels=(magick_uint64_t) cache_info->columns*cache_info->rows;
  if ((offset >= 0) && (((magick_uint64_t) offset+length) < number_pixels))
    if ((x >= 0) && ((x+columns) <= cache_info->columns) &&
        (y >= 0) && ((y+rows) <= cache_info->rows))
      {
        /*
          Pixel request is inside cache extents.
        */
        if (!nexus_info->in_core)
          {
            MagickPassFail
              status;

            status=ReadCachePixels(cache_info,nexus_info,exception);
            if (cache_info->indexes_valid)
              status &= ReadCacheIndexes(cache_info,nexus_info,exception);
            if (status == MagickFail)
              {
                ThrowException(exception,CacheError,UnableToReadPixelCache,
                               image->filename);
                pixels = (PixelPacket *) NULL;
              }
          }
        return(pixels);
      }
  /*
    Pixel request is outside cache extents.
  */
  indexes=nexus_info->indexes;
  if (nexus_info->image_nexus == (NexusInfo *) NULL)
    {
      nexus_info->image_nexus=AllocateCacheNexus();
      if (nexus_info->image_nexus == (NexusInfo *) NULL)
        {
          ThrowException(exception,CacheError,UnableToGetCacheNexus,
                         image->filename);
          return((const PixelPacket *) NULL);
        }
    }
  virtual_pixel=image->background_color;
  q=pixels;
  for (v=0; v < (long) rows; v++)
    {
      for (u=0; u < (long) columns; u+=(long) length)
        {
          length=Min(cache_info->columns-(x+u),columns-u);
          if ((((x+u) < 0) || ((x+u) >= (long) cache_info->columns)) ||
              (((y+v) < 0) || ((y+v) >= (long) cache_info->rows)) || (length == 0))
            {
              /*
                Transfer a single pixel.
              */
              length=1;
              p=(const PixelPacket *) NULL;
              switch (cache_info->virtual_pixel_method)
                {
                case ConstantVirtualPixelMethod:
                  {
                    if (AcquireCacheNexus(image,EdgeX(x+u),EdgeY(y+v),1,1,
                                          nexus_info->image_nexus,exception) !=
                        (PixelPacket *) NULL)
                      p=(&virtual_pixel);
                    break;
                  }
                case EdgeVirtualPixelMethod:
                default:
                  {
                    p=AcquireCacheNexus(image,EdgeX(x+u),EdgeY(y+v),1,1,
                                        nexus_info->image_nexus,exception);
                    break;
                  }
                case MirrorVirtualPixelMethod:
                  {
                    p=AcquireCacheNexus(image,MirrorX(x+u),MirrorY(y+v),1,1,
                                        nexus_info->image_nexus,exception);
                    break;
                  }
                case TileVirtualPixelMethod:
                  {
                    p=AcquireCacheNexus(image,TileX(x+u),TileY(y+v),1,1,
                                        nexus_info->image_nexus,exception);
                    break;
                  }
                }
              if (p == (const PixelPacket *) NULL)
                break;
              *q++=(*p);
              if (indexes == (IndexPacket *) NULL)
                continue;
              nexus_indexes=nexus_info->image_nexus->indexes;
              if (nexus_indexes == (IndexPacket *) NULL)
                continue;
              *indexes++=(*nexus_indexes);
              continue;
            }
          /*
            Transfer a run of pixels.
          */
          p=AcquireCacheNexus(image,x+u,y+v,(const unsigned long) length,1,nexus_info->image_nexus,exception);
          if (p == (const PixelPacket *) NULL)
            break;
          (void) memcpy(q,p,length*sizeof(PixelPacket));
          q+=length;
          if (indexes == (IndexPacket *) NULL)
            continue;
          nexus_indexes=nexus_info->image_nexus->indexes;
          if (nexus_indexes == (IndexPacket *) NULL)
            continue;
          (void) memcpy(indexes,nexus_indexes,length*sizeof(IndexPacket));
          indexes+=length;
        }
    }
  /* DestroyCacheNexus(image_nexus); */
  return(pixels);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   C l i p C a c h e N e x u s                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ClipCacheNexus() clips the image pixels of the in-memory or disk cache as
%  defined by the image clip mask.  The method returns MagickPass if the
%  pixel region is clipped, otherwise MagickFail.
%
%  The format of the ClipCacheNexus() method is:
%
%      MagickPassFail ClipCacheNexus(Image *image,const NexusInfo *nexus_info)
%
%  A description of each parameter follows:
%
%    o status: ClipCacheNexus() returns MagickPass if the image pixels are
%      clipped, otherwise MagickFail.
%
%    o image: The image.
%
%    o nexusinfo: specifies which cache nexus to clip.
%
%
*/
static MagickPassFail
ClipCacheNexus(Image *image,const NexusInfo *nexus_info)
{
  unsigned long
    y;

  register const PixelPacket
    *r;

  register unsigned long
    x;

  register PixelPacket
    *p,
    *q;

  NexusInfo
    *image_nexus,
    *mask_nexus;

  Image
    *clip_mask;

  /*
    Apply clip mask.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  image_nexus=AllocateCacheNexus();
  mask_nexus=AllocateCacheNexus();
  if ((image_nexus == (NexusInfo *) NULL) || (mask_nexus == (NexusInfo *) NULL))
    {
      DestroyCacheNexus(image_nexus);
      DestroyCacheNexus(mask_nexus);
      ThrowBinaryException(CacheError,UnableToGetCacheNexus,image->filename);
    }
  p=GetCacheNexus(image,nexus_info->region.x,nexus_info->region.y,
                  nexus_info->region.width,nexus_info->region.height,
                  image_nexus,&image->exception);
  q=nexus_info->pixels;
  clip_mask = *ImageGetClipMaskInlined(image);
  r=AcquireCacheNexus(clip_mask,nexus_info->region.x,nexus_info->region.y,
                      nexus_info->region.width,nexus_info->region.height,mask_nexus,
                      &image->exception);
  if ((p != (PixelPacket *) NULL) && (r != (const PixelPacket *) NULL))
    for (y=0; y < nexus_info->region.height; y++)
      {
        for (x=0; x < nexus_info->region.width; x++)
          {
            if (r->red == TransparentOpacity)
              q->red=p->red;
            if (r->green == TransparentOpacity)
              q->green=p->green;
            if (r->blue == TransparentOpacity)
              q->blue=p->blue;
            if (r->opacity == TransparentOpacity)
              q->opacity=p->opacity;
            p++;
            q++;
            r++;
          }
      }
  DestroyCacheNexus(image_nexus);
  DestroyCacheNexus(mask_nexus);
  return((p != (PixelPacket *) NULL) && (q != (PixelPacket *) NULL));
}

/* code for CompositeCacheNexus() below was cloned/copied from ClipCacheNexus() */

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   C o m p o s i t e C a c h e N e x u s                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CompositeCacheNexus() composites the image pixels of the in-memory or disk cache as
%  defined by the image composite mask.  The method returns MagickPass if the
%  pixel region is composited, otherwise MagickFail.
%
%  The format of the CompositeCacheNexus() method is:
%
%      MagickPassFail CompositeCacheNexus(Image *image,const NexusInfo *nexus_info)
%
%  A description of each parameter follows:
%
%    o status: CompositeCacheNexus() returns MagickPass if the image pixels are
%      composited, otherwise MagickFail.
%
%    o image: The image.
%
%    o nexus_info: specifies which cache nexus to composite.
%
%
*/
static MagickPassFail
CompositeCacheNexus(Image *image,const NexusInfo *nexus_info)
{
  long
    y;

  register const PixelPacket
    *r; /* the mask */

  register long
    x;

  register PixelPacket
    *p, /* the background pixels */
    *q; /* the foreground pixels, also output */

  NexusInfo
    *image_nexus,
    *mask_nexus;

  Image
    *composite_mask;

  /*
    Apply composite mask.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  image_nexus=AllocateCacheNexus();
  mask_nexus=AllocateCacheNexus();
  if ((image_nexus == (NexusInfo *) NULL) || (mask_nexus == (NexusInfo *) NULL))
    {
      DestroyCacheNexus(image_nexus);
      DestroyCacheNexus(mask_nexus);
      ThrowBinaryException(CacheError,UnableToGetCacheNexus,image->filename);
    }
  /* get background pixels */
  p=GetCacheNexus(image,nexus_info->region.x,nexus_info->region.y,
                  nexus_info->region.width,nexus_info->region.height,
                  image_nexus,&image->exception);
  /* get foreground pixels */
  q=nexus_info->pixels;
  /* get composite mask */
  composite_mask = *ImageGetCompositeMaskInlined(image);
  r=AcquireCacheNexus(composite_mask,nexus_info->region.x,nexus_info->region.y,
                      nexus_info->region.width,nexus_info->region.height,mask_nexus,
                      &image->exception);
  if ((p != (PixelPacket *) NULL) && (r != (const PixelPacket *) NULL))
    for (y=0; y < (long) nexus_info->region.height; y++)
      {
        for (x=0; x < (long) nexus_info->region.width; x++)
          {
            /*
              The mask has already been converted to a luminance value, so using just the
              red component should do.  Also, the "fill-opacity" was integrated into the
              RGB components when the mask was rendered, so we do not do it again here.
            */
            unsigned int alpha = r->red;
            /*
              If the alpha value == MaxRGB (opaque), we do nothing, since the foreground
              value is already in the output "q".  Otherwise, ...
            */
            if  ( alpha == 0 )
              {/*mask fully transparent, store background*/
                q->red = p->red;
                q->green = p->green;
                q->blue = p->blue;
                q->opacity = p->opacity;
              }/*mask fully transparent, store background*/
            else if  ( alpha < MaxRGB )
              {/*alpha not completely opaque, composite*/
                /*
                  Notes:
                    - q is the fg, p is the bg
                    - The fg and bg pixel values are NOT premultiplied by their
                      alpha values.  However, in this case it doesn't matter because
                      the mask alpha value is used to simply mix the two pixel values
                      together according to:

                        output = alpha * fg + (1 - alpha) * bg
                               = alpha * (fg - bg) + bg

                    - The fg and bg alpha values are stored as 0 == opaque, MaxRGB ==
                      transparent (opposite the conventional usage), but if you work
                      through the algebra it turns out the same equation works here too.
                */
                double AlphaNorm = alpha / MaxRGBDouble;
                double aOut = MaxRGBDouble - (AlphaNorm * (q->opacity - p->opacity) + p->opacity);
                double rOut,gOut,bOut;
                if  ( aOut <= 0.0 )
                  rOut = gOut = bOut = aOut = 0.0;
                else if  ( aOut >= MaxRGBDouble )
                  {
                    rOut = AlphaNorm * (q->red - p->red) + p->red;
                    gOut = AlphaNorm * (q->green - p->green) + p->green;
                    bOut = AlphaNorm * (q->blue - p->blue) + p->blue;
                    aOut = MaxRGBDouble;
                  }
                else
                  {
                    /* ReScale makes RGB be not alpha pre-multipled */
                    double ReScale = MaxRGBDouble / aOut;
                    rOut = ReScale * (AlphaNorm * (q->red - p->red) + p->red);
                    gOut = ReScale * (AlphaNorm * (q->green - p->green) + p->green);
                    bOut = ReScale * (AlphaNorm * (q->blue - p->blue) + p->blue);
                    if  ( rOut > MaxRGBDouble )  rOut = MaxRGBDouble;
                    if  ( gOut > MaxRGBDouble )  gOut = MaxRGBDouble;
                    if  ( bOut > MaxRGBDouble )  bOut = MaxRGBDouble;
                  }
                q->red = RoundDoubleToQuantum(rOut);
                q->green = RoundDoubleToQuantum(gOut);
                q->blue = RoundDoubleToQuantum(bOut);
                q->opacity = MaxRGB - (Quantum) RoundDoubleToQuantum(aOut);
              }/*alpha not completely opaque, composite*/
            p++;
            q++;
            r++;
          }
      }
  DestroyCacheNexus(image_nexus);
  DestroyCacheNexus(mask_nexus);
  return((p != (PixelPacket *) NULL) && (q != (PixelPacket *) NULL));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   S y n c C a c h e N e x u s                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SyncCacheNexus() saves the image pixels to the in-memory or disk cache.
%  The method returns MagickPass if the pixel region is synced, otherwise
%  MagickFail.
%
%  The format of the SyncCacheNexus() method is:
%
%      MagickPassFail SyncCacheNexus(Image *image,const NexusInfo *nexus_info,
%                                    ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: SyncCacheNexus() returns MagickPass if the image pixels are
%      transferred to the in-memory or disk cache otherwise MagickFail.
%
%    o image: The image.
%
%    o nexus: specifies which cache nexus to sync.
%
%    o exception: any error is reported here.
%
*/
static MagickPassFail
SyncCacheNexus(Image *image,const NexusInfo *nexus_info,
               ExceptionInfo *exception)
{
  MagickPassFail
    status=MagickPass;

  CacheInfo
    *cache_info;

  /*
    Transfer pixels to the cache.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  cache_info=(CacheInfo *) image->cache;
  if (cache_info == (CacheInfo *) NULL)
    {
      ThrowException(exception,CacheError,PixelCacheIsNotOpen,image->filename);
      status=MagickFail;
    }
  else if (nexus_info->in_core)
    {
      status=MagickPass;
    }
  else
    {
      if (*ImageGetClipMaskInlined(image) != (Image *) NULL)
        if (!ClipCacheNexus(image,nexus_info))
          status=MagickFail;

      /* added mask */
      if  ( status != MagickFail )
        {
          if (*ImageGetCompositeMaskInlined(image) != (Image *) NULL)
            {
              if (!CompositeCacheNexus(image,nexus_info))
                status=MagickFail;
            }
        }

      if (status != MagickFail)
        if ((status=WriteCachePixels(cache_info,nexus_info)) == MagickFail)
          ThrowException(exception,CacheError,UnableToSyncCache,
                         image->filename);

      if (status != MagickFail)
        if (cache_info->indexes_valid)
          if ((status=WriteCacheIndexes(cache_info,nexus_info)) == MagickFail)
            ThrowException(exception,CacheError,UnableToSyncCache,
                           image->filename);
    }

  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   O p e n C a c h e                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  OpenCache() allocates the pixel cache.  This includes defining the cache
%  dimensions, allocating space for the image pixels and optionally the
%  colormap indexes, and memory mapping the cache if it is disk based.  The
%  cache nexus array is initialized as well.
%
%  The format of the OpenCache() method is:
%
%      MagickPass int OpenCache(Image *image,const MapMode mode,
%                               ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: OpenCache() returns MagickPass if the pixel cache is initialized
%      successfully otherwise MagickFail.
%
%    o image: The image.
%
%    o mode: ReadMode, WriteMode, or IOMode.
%
%    o exception: Errors are reported here.
%
%
*/

static MagickPassFail
ExtendCache(int file,magick_off_t length)
{
  ssize_t
    count;

  magick_off_t
    offset;

  offset=MagickSeek(file,0,SEEK_END);
  if (offset < 0)
    return(MagickFail);
  if (offset >= length)
    return(MagickPass);
  offset=MagickSeek(file,length-1,SEEK_SET);
  if (offset < 0)
    return(MagickFail);
  count=write(file,(void *) "",1);
  if (count != 1)
    return(MagickFail);
  return(MagickPass);
}

static MagickPassFail
OpenCache(Image *image,const MapMode mode,ExceptionInfo *exception)
{
  char
    format[MaxTextExtent];

  CacheInfo
    *cache_info;

  magick_uint64_t
    number_pixels,
    offset;

  int
    file;

  PixelPacket
    *pixels;

  size_t
    packet_size;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (void *) NULL);
  if ((image->columns == 0) || (image->rows == 0))
    {
      if (image->exception.severity < ResourceLimitError)
        ThrowException(exception,ResourceLimitError,NoPixelsDefinedInCache,
                       image->filename);
      return MagickFail;
    }

  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  FormatString(cache_info->filename,"%.1024s[%ld]",image->filename,
               image->scene /*GetImageIndexInList(image)*/);
  number_pixels=(magick_uint64_t) image->columns*image->rows;
  if (number_pixels/image->columns != image->rows)
    {
      ThrowException(exception,ResourceLimitError,PixelCacheAllocationFailed,
                     image->filename);
      return MagickFail;
    }
  cache_info->rows=image->rows;
  cache_info->columns=image->columns;
  if (cache_info->storage_class != UndefinedClass)
    {
      /*
        Free cache resources.
      */
      switch (cache_info->type)
        {
        case UndefinedCache:
          {
            break;
          }
        case PingCache:
          {
            break;
          }
        case MemoryCache:
          {
            break;
          }
        case DiskCache:
          {
            LiberateMagickResource(DiskResource,cache_info->length);
            if (cache_info->file == -1)
              break;
            (void) close(cache_info->file);
            cache_info->file=(-1);
            LiberateMagickResource(FileResource,1);
            break;
          }
        case MapCache:
          {
            (void) UnmapBlob(cache_info->pixels,(size_t) cache_info->length);
            LiberateMagickResource(MapResource,cache_info->length);
            break;
          }
        }
    }
#if 0
  /*
    Trace image-directed changes to cache storage class or color space
  */
  if ((cache_info->storage_class != UndefinedClass) &&
      (image->storage_class != cache_info->storage_class))
    (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                          "storage_class %.1024s %s --> %s",
                          cache_info->filename, ClassTypeToString(cache_info->storage_class),
                          ClassTypeToString(image->storage_class));
  if ((cache_info->colorspace != UndefinedColorspace) &&
      (image->colorspace != cache_info->colorspace))
    (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                          "colorspace %.1024s %s --> %s",
                          cache_info->filename, ColorspaceTypeToString(cache_info->colorspace),
                          ColorspaceTypeToString(image->colorspace));
#endif

  /*
    Save the open mode.
  */
  cache_info->read_only = (mode == ReadMode ? MagickTrue : MagickFalse);

  /*
    Indexes are valid if the image storage class is PseudoClass or the
    colorspace is CMYK.
  */
  cache_info->indexes_valid=PixelCacheImageIndexesValid(image);

  if (image->ping)
    {
      cache_info->storage_class=image->storage_class;
      cache_info->colorspace=image->colorspace;
      cache_info->type=PingCache;
      cache_info->pixels=(PixelPacket *) NULL;
      cache_info->indexes=(IndexPacket *) NULL;
      cache_info->length=0;
      return(MagickPass);
    }

  /*
    Ensure that image dimensions are within limits.
  */
  if (CheckImagePixelLimits(image,exception) == MagickFail)
    return MagickFail;

  /*
    Compute storage sizes.  Make sure that sizes fit within our
    numeric limits.
  */
  packet_size=sizeof(PixelPacket);
  if (cache_info->indexes_valid)
    packet_size+=sizeof(IndexPacket);
  offset=number_pixels*packet_size;
  if ((cache_info->columns != (offset/cache_info->rows/packet_size)) ||
      ((magick_uint64_t) ((magick_off_t) offset) != offset))
    {
      ThrowException(exception,ResourceLimitError,PixelCacheAllocationFailed,
                     image->filename);
      return MagickFail;
    }
  cache_info->length=offset;
  /*
    Attempt to create pixel cache in memory
  */
  offset=number_pixels*(sizeof(PixelPacket)+sizeof(IndexPacket));
  if ((offset/number_pixels == (sizeof(PixelPacket)+sizeof(IndexPacket))) &&
      (offset == (magick_uint64_t) ((size_t) offset)) &&
      ((cache_info->type == UndefinedCache) ||
       (cache_info->type == MemoryCache))
      )
    {
      pixels=MagickReallocateResourceLimitedMemory(PixelPacket *,
                                                   cache_info->pixels,
                                                   (size_t) offset);
      if (pixels == (PixelPacket *) NULL)
      {
        MagickFreeResourceLimitedMemory(cache_info->pixels);
      }
      else
      {
        cache_info->pixels=pixels;
      }
      if (pixels != (PixelPacket *) NULL)
        {
          /*
            Create in-memory pixel cache.
          */
          cache_info->length=offset;
          cache_info->storage_class=image->storage_class;
          cache_info->colorspace=image->colorspace;
          cache_info->type=MemoryCache;
          cache_info->pixels=pixels;
          cache_info->indexes=(IndexPacket *) NULL;
          if (cache_info->indexes_valid)
            cache_info->indexes=(IndexPacket *) (pixels+number_pixels);
          FormatSize(cache_info->length,format);
          if (cache_info->logging)
            (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                                  "open %.1024s (%.1024s) storage_class=%s,"
                                  " colorspace=%s",cache_info->filename,
                                  format,
                                  ClassTypeToString(cache_info->storage_class),
                                  ColorspaceTypeToString(cache_info->colorspace));
          return(MagickPass);
        }
    }
  /*
    Create pixel cache on disk.
  */
  if (!AcquireMagickResource(DiskResource,cache_info->length))
    {
      ThrowException(exception,ResourceLimitError,CacheResourcesExhausted,
                     image->filename);
      return MagickFail;
    }
  if (*cache_info->cache_filename == '\0')
    if(!AcquireTemporaryFileName(cache_info->cache_filename))
      {
        LiberateMagickResource(DiskResource,cache_info->length);
        ThrowException(exception,FileOpenError,UnableToCreateTemporaryFile,
                       cache_info->cache_filename);
        return MagickFail;
      }
  switch (mode)
    {
    case ReadMode:
      {
        /* FIXME: open */
        file=open(cache_info->cache_filename,O_RDONLY | O_BINARY | _O_SEQUENTIAL);
        break;
      }
    case WriteMode:
      {
        /* FIXME: open */
        file=open(cache_info->cache_filename,O_WRONLY | O_CREAT | O_BINARY |
                  O_EXCL | _O_SEQUENTIAL,S_MODE);
        if (file == -1)
          file=open(cache_info->cache_filename,O_WRONLY | O_BINARY,S_MODE);
        break;
      }
    case IOMode:
    default:
      {
        /* FIXME: open */
        file=open(cache_info->cache_filename,O_RDWR | O_CREAT | O_BINARY |
                  O_EXCL | _O_SEQUENTIAL, S_MODE);
        if (file == -1)
          file=open(cache_info->cache_filename,O_RDWR | O_BINARY | _O_RANDOM,
                    S_MODE);
        break;
      }
    }
  if (file == -1)
    {
      LiberateMagickResource(DiskResource,cache_info->length);
      ThrowException(exception,CacheError,UnableToOpenCache,image->filename);
      return MagickFail;
    }
  if (!ExtendCache(file,(magick_off_t) cache_info->length+cache_info->offset))
    {
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "Unable to extend pixel cache from %"
                            MAGICK_UINT64_F "u bytes "
                            "by %" MAGICK_UINT64_F "u bytes "
                            "to %" MAGICK_UINT64_F "u bytes",
                            cache_info->length,
                            cache_info->offset,
                            cache_info->offset+cache_info->length);
      (void) close(file);
      (void) LiberateTemporaryFile(cache_info->cache_filename);
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "remove %.1024s (%.1024s)",cache_info->filename,
                            cache_info->cache_filename);
      LiberateMagickResource(DiskResource,cache_info->length);
      ThrowException(exception,CacheError,UnableToExtendCache,image->filename);
      return MagickFail;
    }
  cache_info->storage_class=image->storage_class;
  cache_info->colorspace=image->colorspace;
  cache_info->type=DiskCache;
  if ((cache_info->length > MinBlobExtent) &&
      (cache_info->length == ((size_t) cache_info->length)) &&
      AcquireMagickResource(MapResource,cache_info->length))
    {
      pixels=(PixelPacket *) MapBlob(file,mode,(off_t) cache_info->offset,
                                     (size_t) cache_info->length);
      if (pixels == (PixelPacket *) NULL)
        LiberateMagickResource(MapResource,cache_info->length);
      else
        {
          /*
            Create memory-mapped pixel cache.
          */
          (void) close(file);
          cache_info->type=MapCache;
          cache_info->pixels=pixels;
          cache_info->indexes=(IndexPacket *) NULL;
          if (cache_info->indexes_valid)
            cache_info->indexes=(IndexPacket *) (pixels+number_pixels);
        }
    }
  if (cache_info->type == DiskCache)
    {
      if (AcquireMagickResource(FileResource,1))
        cache_info->file=file;
      else
        (void) close(file);
    }
#if defined(SIGBUS)
  /*   (void) signal(SIGBUS,CacheSignalHandler); */
#endif
  FormatSize(cache_info->length,format);
  if (cache_info->logging)
    (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                          "open %.1024s (%.1024s[%d], %.1024s, %.1024s)"
                          " storage_class=%s, colorspace=%s",
                          cache_info->filename,cache_info->cache_filename,
                          cache_info->file,
                          cache_info->type == MapCache ? "memory-mapped" : "disk",
                          format,
                          ClassTypeToString(cache_info->storage_class),
                          ColorspaceTypeToString(cache_info->colorspace));
  return(MagickPass);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c c e s s C a c h e V i e w P i x e l s                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method AccessCacheViewPixels returns writeable pixels associated with
%  the specified view.
%
%  The format of the AccessCacheViewPixels method is:
%
%      PixelPacket *AccessCacheViewPixels(const ViewInfo *view)
%
%  A description of each parameter follows:
%
%    o indexes: Method AccessCacheViewPixels returns the pixels associated with
%      the specified view.
%
%    o view: The address of a structure of type ViewInfo.
%
%
*/
MagickExport PixelPacket *
AccessCacheViewPixels(const ViewInfo *view)
{
  const View
    * restrict view_info = (const View *) view;

  assert(view_info != (View *) NULL);
  assert(view_info->signature == MagickSignature);
  return view_info->nexus_info.pixels;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c c e s s I m m u t a b l e I n d e x e s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AccessImmutableIndexes() returns the read-only colormap indexes
%  associated with the last call to AcquireImagePixels(). NULL is
%  returned if colormap indexes are not available.
%
%  The format of the AccessImmutableIndexes() method is:
%
%      const IndexPacket *AccessImmutableIndexes(const Image *image)
%
%  A description of each parameter follows:
%
%    o indexes: The indexes associated with the last call to
%               AcquireImagePixels().
%
%    o image: The image.
%
%
*/
MagickExport const IndexPacket *
AccessImmutableIndexes(const Image *image)
{
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
 return AcquireCacheViewIndexes((ViewInfo *) AccessDefaultCacheView(image));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c c e s s M u t a b l e I n d e x e s                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AccessMutableIndexes() returns the writeable colormap indexes associated
%  with the last call to SetImagePixels() or GetImagePixels(). NULL is
%  returned if colormap indexes are not available.
%
%  The format of the AccessMutableIndexes() method is:
%
%      IndexPacket *AccessMutableIndexes(Image *image)
%
%  A description of each parameter follows:
%
%    o indexes: The indexes associated with the last call to
%               AcquireImagePixels().
%
%    o image: The image.
%
%
*/
MagickExport IndexPacket *
AccessMutableIndexes(Image *image)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return GetCacheViewIndexes(AccessDefaultCacheView(image));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c c e s s M u t a b l e P i x e l s                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AccessMutablePixels() returns the pixels associated with the last call to
%  SetImagePixels() or GetImagePixels(). This is useful in order to access
%  an already selected region without passing the geometry of the region.
%
%  The format of the AccessMutablePixels() method is:
%
%      PixelPacket *AccessMutablePixels(Image image)
%
%  A description of each parameter follows:
%
%    o pixels: The pixels associated with the last call to SetImagePixels()
%              or GetImagePixels().
%
%    o image: The image.
%
%
*/
MagickExport PixelPacket *
AccessMutablePixels(Image *image)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return AccessCacheViewPixels(AccessDefaultCacheView(image));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c q u i r e C a c h e V i e w P i x e l s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method AcquireCacheViewPixels gets pixels from the in-memory or disk pixel
%  cache as defined by the geometry parameters for read-only access.   A
%  pointer to the pixels is returned if the pixels are transferred, otherwise
%  NULL is returned.
%
%  The format of the AcquireCacheViewPixels method is:
%
%      const PixelPacket *AcquireCacheViewPixels(ViewInfo *view,
%        const long x,const long y,const unsigned long columns,
%        const unsigned long rows,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pixels: Method AcquireCacheViewPixels returns a null pointer if an error
%      occurs, otherwise a pointer to the view pixels.
%
%    o view: The address of a structure of type ViewInfo.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport const PixelPacket *
AcquireCacheViewPixels(ViewInfo *view,
                       const long x,const long y,const unsigned long columns,
                       const unsigned long rows,ExceptionInfo *exception)
{
  View
    * restrict view_info = (View *) view;

  assert(view_info != (View *) NULL);
  assert(view_info->signature == MagickSignature);
  return AcquireCacheNexus(view_info->image,x,y,columns,rows,
                           &view_info->nexus_info,exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c q u i r e C a c h e V i e w I n d e x e s                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method AcquireCacheViewIndexes returns read-only indexes associated with
%  the specified view.
%
%  The format of the AcquireCacheViewIndexes method is:
%
%      const IndexPacket *AcquireCacheViewIndexes(const ViewInfo *view)
%
%  A description of each parameter follows:
%
%    o indexes: Method AcquireCacheViewIndexes returns the indexes
%      associated with the specified view.
%
%    o view: The address of a structure of type ViewInfo.
%
%
*/
MagickExport const IndexPacket *
AcquireCacheViewIndexes(const ViewInfo *view)
{
  const View
    * restrict view_info = (const View *) view;

  assert(view_info != (const View *) NULL);
  assert(view_info->signature == MagickSignature);
  return view_info->nexus_info.indexes;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c q u i r e I m a g e P i x e l s                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AcquireImagePixels() obtains a pixel region for read-only access. If the
%  region is successfully accessed, a pointer to it is returned, otherwise
%  NULL is returned. The returned pointer may point to a temporary working
%  copy of the pixels or it may point to the original pixels in memory.
%  Performance is maximized if the selected area is part of one row, or one
%  or more full rows, since then there is opportunity to access the pixels
%  in-place (without a copy) if the image is in RAM, or in a memory-mapped
%  file. The returned pointer should *never* be deallocated by the user.
%
%  Pixels accessed via the returned pointer represent a simple array of type
%  PixelPacket. If the image storage class is PsudeoClass, call
%  AccessImmutableIndexes() after invoking GetImagePixels() to obtain the
%  colormap indexes (of type IndexPacket) corresponding to the region.
%
%  If you plan to modify the pixels, use GetImagePixels() instead.
%
%  The format of the AcquireImagePixels() method is:
%
%      const PixelPacket *AcquireImagePixels(const Image *image,const long x,
%        const long y,const unsigned long columns,const unsigned long rows,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: AcquireImagePixels() returns a pointer to the pixels if they
%      are transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport const PixelPacket *
AcquireImagePixels(const Image *image,
                   const long x,const long y,const unsigned long columns,
                   const unsigned long rows,ExceptionInfo *exception)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return AcquireCacheViewPixels(AccessDefaultCacheView(image),
                                x,y,columns,rows,exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c q u i r e O n e C a c h e V i e w P i x e l                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method AcquireOneCacheViewPixel gets one pixel from the in-memory or disk
%  pixel cache as defined by the geometry parameters for read-only access.
%  The image background color is returned if there is an error retrieving
%  the pixel.
%
%  The format of the AcquireOneCacheViewPixel method is:
%
%      MagickPassFail AcquireOneCacheViewPixel(const ViewInfo *view,
%                              PixelPacket *pixel,const long x,const long y,
%                              ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o view: The address of a structure of type ViewInfo.
%
%    o pixel: Pointer to PixelPacket to update.
%
%    o x,y:  Coordinate of pixel to retrieve
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
static inline MagickPassFail
AcquireOneCacheViewPixelInlined(View *view_info,
                                PixelPacket *pixel,
                                const long x,const long y,
                                ExceptionInfo *exception)
{
  const Image
    *image=view_info->image;

  const CacheInfo
    * restrict cache_info=(const CacheInfo *) image->cache;

  MagickPassFail
    status=MagickFail;

  if (((MemoryCache == cache_info->type) || (MapCache == cache_info->type)) &&
      ((x >= 0) && (y >= 0) &&
       ((unsigned long) x < cache_info->columns) &&
       ((unsigned long) y < cache_info->rows)))
    {
      magick_off_t
        offset;

      offset=y*(magick_off_t) cache_info->columns+x;
      if ((cache_info->indexes_valid) &&
          (PseudoClass == cache_info->storage_class))
        *pixel=image->colormap[cache_info->indexes[offset]];
      else
        *pixel=cache_info->pixels[offset];
      status=MagickPass;
    }
  else
    {
      const PixelPacket
        *pixels;

      if ((pixels=AcquireCacheNexus(image,x,y,1,1,&view_info->nexus_info,
                                    exception)) != (const PixelPacket *) NULL)
        {
          *pixel=pixels[0];
          status=MagickPass;
        }
      else
        {
          *pixel=image->background_color;
        }
    }

  return status;
}

MagickExport MagickPassFail
AcquireOneCacheViewPixel(ViewInfo *view,PixelPacket *pixel,
                         const long x,const long y,
                         ExceptionInfo *exception)
{
  return AcquireOneCacheViewPixelInlined((View *) view,pixel,x,y,
                                         exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c q u i r e O n e P i x e l                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AcquireOnePixel() returns a single pixel at the specified (x,y) location.
%  The image background color is returned if an error occurs.  If errors
%  are to be returned to the image, use GetOnePixel() instead. This function
%  is convenient but performance will be poor if it is used too often.
%
%  The format of the AcquireOnePixel() method is:
%
%      PixelPacket AcquireOnePixel(const Image image,const long x,
%        const long y,ExceptionInfo exception)
%
%  A description of each parameter follows:
%
%    o pixels: AcquireOnePixel() returns a pixel at the specified (x,y)
%      location.
%
%    o image: The image.
%
%    o x,y:  These values define the location of the pixel to return.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport PixelPacket
AcquireOnePixel(const Image *image,const long x,const long y,
                ExceptionInfo *exception)
{
  PixelPacket
    pixel;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  (void) AcquireOneCacheViewPixel(AccessDefaultCacheView(image),
                                  &pixel,x,y,exception);
  return pixel;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c q u i r e O n e P i x e l B y R e f e r e n c e                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AcquireOnePixelByReference() returns a single pixel at the specified (x,y)
%  location. The image background color is returned if an error occurs. This
%  function is convenient but performance will be poor if it is used too
%  often.
%
%  The format of the AcquireOnePixelByReference() method is:
%
%      MagickPassFail AcquireOnePixelByReference(const Image *image,
%                                                PixelPacket *pixel,
%                                                const long x,const long y,
%                                                ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pixels: AcquireOnePixel() returns a pixel at the specified (x,y)
%      location.
%
%    o image: The image.
%
%    o pixel: A reference to the pixel to update.
%
%    o x,y:  These values define the location of the pixel to return.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport MagickPassFail
AcquireOnePixelByReference(const Image *image,PixelPacket *pixel,
                           const long x,const long y,
                           ExceptionInfo *exception)
{
  return
    AcquireOneCacheViewPixelInlined((View *) AccessDefaultCacheView(image),
                                    pixel,x,y,
                                    exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C h e c k I m a g e P i x e l L i m i t s                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CheckImagePixelLimits() verifies that image dimensions are within current
%  limits.  Returns MagickPass if image dimensions are within limits, or
%  MagickFail (and updates exception) if dimensions exceed a limit.
%
%  While this function is used within the pixel cache to prevent allocating
%  an image which exceeds the limits, it may also be used to validate image
%  dimensions obtained from file headers prior to allocating memory or doing
%  further processing of the image.  Such additional limits should be after
%  any 'ping' mode processing so that the image dimensions can still be
%  shown by 'identify'.
%
%  The format of the CheckImagePixelLimits() method is:
%
%      MagickPassFail CheckImagePixelLimits(const Image *image,
%                                           ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: Image to verify rows/columns.
%
%    o exception: Throw exception into this ExceptionInfo structure.
%
%
*/
MagickExport MagickPassFail
CheckImagePixelLimits(const Image *image, ExceptionInfo *exception)
{
  if ((image->columns == 0) ||
      (image->columns > LONG_MAX) ||
      (AcquireMagickResource(WidthResource,image->columns)
       != MagickPass))
    {
      char
        message[MaxTextExtent];

      magick_int64_t
        limit;

      errno=0;
      limit=GetMagickResourceLimit(WidthResource);
      if (limit > LONG_MAX)
        limit = LONG_MAX;
      FormatString(message,"%lu > %" MAGICK_INT64_F "u \"%.1024s\"",
                   image->columns,limit,image->filename);
      ThrowException(exception,ResourceLimitError,ImagePixelWidthLimitExceeded,
                     message);
      return MagickFail;
    }

  if ((image->rows == 0) ||
      (image->rows > LONG_MAX) ||
      (AcquireMagickResource(HeightResource,image->rows)
       != MagickPass))
    {
      char
        message[MaxTextExtent];

      magick_int64_t
        limit;

      errno=0;
      limit=GetMagickResourceLimit(HeightResource);
      if (limit > LONG_MAX)
        limit = LONG_MAX;
      FormatString(message,"%lu > %" MAGICK_INT64_F "u \"%.1024s\"",
                   image->rows,limit,image->filename);
      ThrowException(exception,ResourceLimitError,ImagePixelHeightLimitExceeded,
                     message);
      return MagickFail;
    }

  {
    magick_int64_t
      total_pixels;

    total_pixels=(magick_int64_t) image->columns*image->rows;
    if (AcquireMagickResource(PixelsResource,total_pixels)
        != MagickPass)
      {
        char
          message[MaxTextExtent];

        errno=0;
        FormatString(message,
                     "%" MAGICK_INT64_F "d > %" MAGICK_INT64_F "u \"%.1024s\"",
                     total_pixels,
                     GetMagickResourceLimit(PixelsResource),image->filename);
        ThrowException(exception,ResourceLimitError,ImagePixelLimitExceeded,
                       message);
        return MagickFail;
      }
  }

  return MagickPass;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   C l o n e P i x e l C a c h e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ClonePixelCache() clones the pixel cache pixels from one cache to another.
%
%  The format of the ClonePixelCache() method is:
%
%      MagickPassFail ClonePixelCache(Image *image,Image *clone_image)
%
%  A description of each parameter follows:
%
%    o image: Image to clone from (the master).
%
%    o clone_image: Image to clone to (the copy).
%
%
*/
static MagickPassFail
ClonePixelCache(Image *image,Image *clone_image,ExceptionInfo *exception)
{
#define MaxBufferSize  65541

  CacheInfo
    *cache_info,
    *clone_info;

  char
    *buffer;

  ssize_t
    count;

  int
    cache_file,
    clone_file;

  register magick_uint64_t
    offset;

  size_t
    length;

  MagickPassFail
    status;

  cache_info=(CacheInfo *) image->cache;
  clone_info=(CacheInfo *) clone_image->cache;
  if (cache_info->length != clone_info->length)
    {
      Image
        *clip_mask,
        *composite_mask,
        **ppclone_clip_mask,
        **ppclone_composite_mask;

      ViewInfo
        *clone_view,
        *image_view;

      long
        y;

      register const PixelPacket
        *p;

      register const IndexPacket
        *indexes;

      register IndexPacket
        *clone_indexes;

      register PixelPacket
        *q;

      /*
        Unoptimized pixel cache clone.
      */
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),"unoptimized clone");
      ppclone_clip_mask = ImageGetClipMaskInlined(clone_image);
      clip_mask=*ppclone_clip_mask;
      *ppclone_clip_mask=(Image *) NULL;
      ppclone_composite_mask = ImageGetCompositeMaskInlined(clone_image);
      composite_mask=*ppclone_composite_mask;
      *ppclone_composite_mask=(Image *) NULL;
      length=Min(image->columns,clone_image->columns);
      y=0;
      image_view=OpenCacheView(image);
      clone_view=OpenCacheView(clone_image);
      if ((image_view != (ViewInfo *) NULL) &&
          (clone_view != (ViewInfo *) NULL))
        {
          for (y=0; y < (long) image->rows; y++)
            {
              p=AcquireCacheViewPixels(image_view,0,y,image->columns,1,
                                       exception);
              q=SetCacheViewPixels(clone_view,0,y,image->columns,1,exception);
              if ((p == (const PixelPacket *) NULL) ||
                  (q == (PixelPacket *) NULL))
                break;
              (void) memcpy(q,p,length*sizeof(PixelPacket));
              indexes=AcquireCacheViewIndexes(image_view);
              clone_indexes=GetCacheViewIndexes(clone_view);
              if ((indexes != (const IndexPacket *) NULL) &&
                  (clone_indexes != (IndexPacket *) NULL))
                (void) memcpy(clone_indexes,indexes,
                              length*sizeof(IndexPacket));
              if (!SyncCacheViewPixels(clone_view,exception))
                break;
            }
        }
      *ImageGetClipMaskInlined(clone_image)=clip_mask;
      *ImageGetCompositeMaskInlined(clone_image)=composite_mask;
      CloseCacheView(image_view);
      CloseCacheView(clone_view);
      return(y == (long) image->rows);
    }
  /*
    Optimized pixel cache clone.
  */
  if ((cache_info->type != DiskCache) && (clone_info->type != DiskCache))
    {
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "memory => memory clone");
      (void) memcpy(clone_info->pixels,cache_info->pixels,
                    (size_t) cache_info->length);
      return(MagickPass);
    }
  LockSemaphoreInfo(cache_info->file_semaphore);
  LockSemaphoreInfo(clone_info->file_semaphore);
  status=MagickPass;
  cache_file=cache_info->file;
  if (cache_info->type == DiskCache)
    {
      if (cache_info->file == -1)
        {
          /* FIXME: open */
          cache_file=open(cache_info->cache_filename,O_RDONLY | O_BINARY);
          if (cache_file == -1)
            {
              status=MagickFail;
              ThrowException(exception,FileOpenError,UnableToOpenFile,
                             cache_info->cache_filename);
              goto clone_pixel_cache_done;
            }
        }
      (void) MagickSeek(cache_file,cache_info->offset,SEEK_SET);
      if (clone_info->type != DiskCache)
        {
          (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                                "disk => memory clone");
          for (offset=0; offset < cache_info->length; offset+=(magick_uint64_t) count)
            {
              size_t
                requested_io_size;

              unsigned int
                io_size;

              requested_io_size=(size_t) (cache_info->length-offset);
              if (requested_io_size > MAGICK_IO_MAX)
                io_size=MAGICK_IO_MAX;
              else
                io_size=(unsigned int) requested_io_size;

              count=read(cache_file,(char *) clone_info->pixels+offset,
                         io_size);
              if (count <= 0)
                break;
            }
          if (cache_info->file == -1)
            (void) close(cache_file);
          if (offset < cache_info->length)
            {
              status=MagickFail;
              ThrowException(exception,CacheError,UnableToCloneCache,
                             image->filename);
              goto clone_pixel_cache_done;
            }
          goto clone_pixel_cache_done;
        }
    }
  clone_file=clone_info->file;
  if (clone_info->type == DiskCache)
    {
      if (clone_info->file == -1)
        {
          /* FIXME: open */
          clone_file=open(clone_info->cache_filename,O_WRONLY | O_BINARY |
                          O_EXCL,S_MODE);
          if (clone_file == -1)
            clone_file=open(clone_info->cache_filename,O_WRONLY | O_BINARY,
                            S_MODE);
          if (clone_file == -1)
            {
              if (cache_info->file == -1)
                (void) close(cache_file);
              status=MagickFail;
              ThrowException(exception,FileOpenError,UnableToOpenFile,
                             clone_info->cache_filename);
              goto clone_pixel_cache_done;
            }
        }
      (void) MagickSeek(clone_file,cache_info->offset,SEEK_SET);
      if (cache_info->type != DiskCache)
        {
          (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                                "memory => disk clone");
          for (offset=0L; offset < clone_info->length; offset+=(magick_uint64_t) count)
            {
              size_t
                requested_io_size;

              MAGICK_POSIX_IO_SIZE_T
                io_size;

              requested_io_size=(size_t) (clone_info->length-offset);
              if (requested_io_size > MAGICK_IO_MAX)
                io_size=MAGICK_IO_MAX;
              else
                io_size=(MAGICK_POSIX_IO_SIZE_T) requested_io_size;

              count=write(clone_file,(char *) cache_info->pixels+offset,
                          io_size);
              if (count <= 0)
                break;
            }
          if (clone_info->file == -1)
            (void) close(clone_file);
          if (offset < clone_info->length)
            {
              status=MagickFail;
              ThrowException(exception,CacheError,UnableToCloneCache,
                             image->filename);
            }
          goto clone_pixel_cache_done;
        }
    }
  (void) LogMagickEvent(CacheEvent,GetMagickModule(),"disk => disk clone");
  buffer=MagickAllocateMemory(char *,MaxBufferSize);
  if (buffer == (char *) NULL)
    {
      if (cache_info->file == -1)
        (void) close(cache_file);
      if (clone_info->file == -1)
        (void) close(clone_file);
      status=MagickFail;
      ThrowException3(exception,ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToCloneImage);
      goto clone_pixel_cache_done;
    }
  (void) MagickSeek(cache_file,cache_info->offset,SEEK_SET);
  (void) MagickSeek(clone_file,cache_info->offset,SEEK_SET);

  for (offset=0, length=0; (count=read(cache_file,buffer,MaxBufferSize)) > 0; )
    {
      length=(size_t) count;
      for (offset=0; offset < length; offset+=(magick_uint64_t) count)
        {
          size_t
            requested_io_size;

          MAGICK_POSIX_IO_SIZE_T
            io_size;

          requested_io_size=(size_t) (length-offset);
          io_size=(MAGICK_POSIX_IO_SIZE_T) Min(MAGICK_IO_MAX,requested_io_size);

          count=write(clone_file,buffer+offset,io_size);
          if (count <= 0)
            break;
        }
      if (offset < length)
        break;
    }
  if (cache_info->file == -1)
    (void) close(cache_file);
  if (clone_info->file == -1)
    (void) close(clone_file);

  MagickFreeMemory(buffer);
  if (offset < length)
    {
      status=MagickFail;
      ThrowException(exception,CacheError,UnableToCloneCache,image->filename);
      goto  clone_pixel_cache_done;
    }
 clone_pixel_cache_done:
  UnlockSemaphoreInfo(cache_info->file_semaphore);
  UnlockSemaphoreInfo(clone_info->file_semaphore);
  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   C l o s e C a c h e V i e w                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CloseCacheView() closes the specified view returned by a previous call
%  to OpenCacheView().
%
%  The format of the CloseCacheView method is:
%
%      void CloseCacheView(ViewInfo *view)
%
%  A description of each parameter follows:
%
%    o view: The address of a structure of type ViewInfo.
%
*/
MagickExport void
CloseCacheView(ViewInfo *view)
{
  if (view != (ViewInfo *) NULL)
    {
      View
        *view_info = (View *) view;

      DeinitializeCacheView(view_info);
      MagickFreeAlignedMemory(view_info);
    }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D e s t r o y C a c h e I n f o                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyCacheInfo() deallocates memory associated with the pixel cache.
%
%  The format of the DestroyCacheInfo() method is:
%
%      void DestroyCacheInfo(Cache cache)
%
%  A description of each parameter follows:
%
%    o cache: Specifies a pointer to a Cache structure.
%
%
*/
void
DestroyCacheInfo(Cache cache_info)
{
  assert(cache_info != (Cache) NULL);
  assert(cache_info->signature == MagickSignature);
  LockSemaphoreInfo(cache_info->reference_semaphore);
  cache_info->reference_count--;
  if (cache_info->reference_count > 0)
    {
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "destroy skipped (still referenced %ld times) %.1024s",
                            cache_info->reference_count,
                            cache_info->filename);
      UnlockSemaphoreInfo(cache_info->reference_semaphore);
      return;
    }
  UnlockSemaphoreInfo(cache_info->reference_semaphore);

  /*
    Release Cache Pixel Resources
  */
  if (MemoryCache == cache_info->type)
    {
      MagickFreeResourceLimitedMemory(cache_info->pixels);
    }
  else if (MapCache == cache_info->type)
    {
      (void) UnmapBlob(cache_info->pixels,(size_t) cache_info->length);
      cache_info->pixels = NULL;
      LiberateMagickResource(MapResource,cache_info->length);
    }

  /*
    Release Cache File Resources
  */
  if ((MapCache == cache_info->type) || (DiskCache == cache_info->type))
    {
      if (cache_info->file != -1)
        {
          (void) close(cache_info->file);
          LiberateMagickResource(FileResource,1);
          cache_info->file=(-1);
        }
      (void) LiberateTemporaryFile(cache_info->cache_filename);
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "remove %.1024s (%.1024s)",cache_info->filename,
                            cache_info->cache_filename);
      LiberateMagickResource(DiskResource,cache_info->length);
    }

  DestroySemaphoreInfo(&cache_info->file_semaphore);
  DestroySemaphoreInfo(&cache_info->reference_semaphore);
  (void) LogMagickEvent(CacheEvent,GetMagickModule(),"destroy cache %.1024s",
                        cache_info->filename);
  cache_info->signature=0;
  MagickFreeAlignedMemory(cache_info);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D e s t r o y I m a g e P i x e l s                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyImagePixels() deallocates memory associated with the pixel cache.
%
%  The format of the DestroyImagePixels() method is:
%
%      void DestroyImagePixels(Image *image)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%
*/
MagickExport void
DestroyImagePixels(Image *image)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if (image->cache != (void *) NULL)
    DestroyCacheInfo(image->cache);
  image->cache=(Cache) NULL;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t C a c h e I n f o                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetCacheInfo() initializes the Cache structure.
%
%  The format of the GetCacheInfo() method is:
%
%      void GetCacheInfo(Cache *cache)
%
%  A description of each parameter follows:
%
%    o cache: Specifies a pointer to a Cache structure.
%
%
*/
void
GetCacheInfo(Cache *cache)
{
  CacheInfo
    *cache_info;

  magick_int64_t
    limit;

  assert(cache != (Cache*) NULL);
  cache_info=MagickAllocateAlignedMemory(CacheInfo *,
                                         MAGICK_CACHE_LINE_SIZE,
                                         sizeof(CacheInfo));
  if (cache_info == (CacheInfo *) NULL)
    MagickFatalError3(ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToAllocateCacheInfo);
  (void) memset(cache_info,0,sizeof(CacheInfo));
  cache_info->colorspace=RGBColorspace;
  cache_info->reference_semaphore=AllocateSemaphoreInfo();
  LockSemaphoreInfo(cache_info->reference_semaphore);
  cache_info->reference_count=1;
  UnlockSemaphoreInfo(cache_info->reference_semaphore);
  cache_info->file=(-1);
  if (cache_info->reference_semaphore == (SemaphoreInfo *) NULL)
    MagickFatalError3(ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToAllocateCacheInfo);
  cache_info->file_semaphore=AllocateSemaphoreInfo();
  if (cache_info->file_semaphore == (SemaphoreInfo *) NULL)
    MagickFatalError3(ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToAllocateCacheInfo);
  /*
    Cache limits to apply later when allocating cache nexus
  */
  limit=GetMagickResourceLimit(PixelsResource);
  cache_info->limit_pixels=limit;
  limit=GetMagickResourceLimit(WidthResource);
  cache_info->limit_width=Min(LONG_MAX,limit);
  limit=GetMagickResourceLimit(HeightResource);
  cache_info->limit_height=Min(LONG_MAX,limit);

  cache_info->logging=IsEventLogged(CacheEvent);

  cache_info->signature=MagickSignature;
  *cache=cache_info;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t C a c h e V i e w A r e a                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetCacheViewArea() returns the area (width * height in pixels) consumed by
%  the pixel cache view
%
%  The format of the GetCacheViewArea() method is:
%
%      magick_off_t GetCacheViewArea(const ViewInfo *view)
%
%  A description of each parameter follows:
%
%    o view: The view.
%
%
*/
MagickExport magick_off_t
GetCacheViewArea(const ViewInfo *view)
{
  const View
    * restrict view_info = (const View *) view;

  register const NexusInfo
    * restrict nexus_info;

  assert(view_info != (const View *) NULL);
  assert(view_info->signature == MagickSignature);
  nexus_info=&view_info->nexus_info;
  return((magick_off_t) nexus_info->region.width*nexus_info->region.height);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t C a c h e V i e w P i x e l s                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetCacheViewPixels() gets writeable pixels from the in-memory or disk pixel
%  cache as defined by the geometry parameters.   A pointer to the pixels
%  is returned if the pixels are transferred, otherwise a NULL is returned.
%
%  The format of the GetCacheViewPixels method is:
%
%      PixelPacket *GetCacheViewPixels(ViewInfo *view,const long x,
%        const long y,const unsigned long columns,const unsigned long rows,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pixels: Method GetCacheViewPixels returns a null pointer if an error
%      occurs, otherwise a pointer to the view pixels.
%
%    o view: The address of a structure of type ViewInfo.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o exception: Any errors are reported here.
%
*/
MagickExport PixelPacket *
GetCacheViewPixels(ViewInfo *view,const long x,const long y,
                   const unsigned long columns,const unsigned long rows,
                   ExceptionInfo *exception)
{
  View
    *view_info = (View *) view;

  PixelPacket
    *pixels;

  assert(view_info != (const View *) NULL);
  assert(view_info->signature == MagickSignature);
  pixels=GetCacheNexus(view_info->image,x,y,columns,rows,&view_info->nexus_info,
                       exception);
  return pixels;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t C a c h e V i e w I m a g e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method GetCacheViewImage returns the image which allocated the view.
%
%  The format of the GetCacheViewImage method is:
%
%      Image *GetCacheViewImage(const ViewInfo *view)
%
%  A description of each parameter follows:
%
%    o image: Method GetCacheViewImage returns the image which allocated
%        the view.
%
%    o view: The address of a structure of type ViewInfo.
%
%
*/
extern Image *
GetCacheViewImage(const ViewInfo *view)
{
  const View
    * restrict view_info = (const View *) view;

  assert(view_info != (View *) NULL);
  assert(view_info->signature == MagickSignature);
  return view_info->image;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t C a c h e V i e w I n d e x e s                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method GetCacheViewIndexes returns writeable indexes associated with
%  the specified view.
%
%  The format of the GetCacheViewIndexes method is:
%
%      IndexPacket *GetCacheViewIndexes(const ViewInfo *view)
%
%  A description of each parameter follows:
%
%    o indexes: Method GetCacheViewIndexes returns the indexes associated with
%      the specified view.
%
%    o view: The address of a structure of type ViewInfo.
%
%
*/
MagickExport IndexPacket *
GetCacheViewIndexes(const ViewInfo *view)
{
  const View
    *view_info = (const View *) view;

  assert(view_info != (View *) NULL);
  assert(view_info->signature == MagickSignature);
  return view_info->nexus_info.indexes;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t C a c h e V i e w R e g i o n                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetCacheViewRegion() returns the bounded region for the pixel cache view.
%
%  The format of the GetCacheViewRegion() method is:
%
%      RectangleInfo GetCacheViewRegion(const ViewInfo *view)
%
%  A description of each parameter follows:
%
%    o view: The view.
%
%
*/
MagickExport RectangleInfo
GetCacheViewRegion(const ViewInfo *view)
{
  const View
    *view_info = (const View *) view;

  const NexusInfo
    *nexus_info;

  assert(view_info != (View *) NULL);
  assert(view_info->signature == MagickSignature);
  nexus_info=&view_info->nexus_info;
  assert(nexus_info != (NexusInfo *) NULL);
  assert(nexus_info->signature == MagickSignature);
  return nexus_info->region;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e P i x e l s                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImagePixels() obtains a pixel region for read/write access. If the
%  region is successfully accessed, a pointer to a PixelPacket array
%  representing the region is returned, otherwise NULL is returned.
%
%  The returned pointer may point to a temporary working copy of the pixels
%  or it may point to the original pixels in memory. Performance is maximized
%  if the selected area is part of one row, or one or more full rows, since
%  then there is opportunity to access the pixels in-place (without a copy)
%  if the image is in RAM, or in a memory-mapped file. The returned pointer
%  should *never* be deallocated by the user.
%
%  Pixels accessed via the returned pointer represent a simple array of type
%  PixelPacket. If the image storage class is PsudeoClass, call
%  AccessMutableIndexes() after invoking GetImagePixels() to obtain the
%  colormap indexes (of type IndexPacket) corresponding to the region.  Once
%  the PixelPacket (and/or IndexPacket) array has been updated, the changes
%  must be saved back to the underlying image using SyncImagePixels() or they
%  may be lost.
%
%  The format of the GetImagePixels() method is:
%
%      PixelPacket *GetImagePixels(Image *image,const long x,const long y,
%        const unsigned long columns,const unsigned long rows)
%
%  A description of each parameter follows:
%
%    o status: GetImagePixels() returns a pointer to the pixels if they are
%      transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%
*/
MagickExport PixelPacket *
GetImagePixels(Image *image,const long x,const long y,
               const unsigned long columns,const unsigned long rows)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return GetCacheViewPixels(AccessDefaultCacheView(image),
                            x,y,columns,rows,&image->exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e P i x e l s E x                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImagePixelsEx() obtains a pixel region for read/write access.  It is
%  similar to GetImagePixels() except that it reports any error information
%  to a user provided exception structure.
%
%  The format of the GetImagePixelsEx() method is:
%
%      PixelPacket *GetImagePixelsEx(Image *image,const long x,const long y,
%        const unsigned long columns,const unsigned long rows,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: GetImagePixelsEx() returns a pointer to the pixels if they are
%      transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o exception: Any error details are reported here.
%
%
*/
MagickExport PixelPacket *
GetImagePixelsEx(Image *image,const long x,const long y,
                 const unsigned long columns,const unsigned long rows,
                 ExceptionInfo *exception)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return GetCacheViewPixels(AccessDefaultCacheView(image),
                            x,y,columns,rows,exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e V i r t u a l P i x e l M e t h o d                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImageVirtualPixelMethod() gets the "virtual pixels" method for the
%  image.  A virtual pixel is any pixel access that is outside the boundaries
%  of the image cache.
%
%  The format of the GetImageVirtualPixelMethod() method is:
%
%      VirtualPixelMethod GetImageVirtualPixelMethod(const Image *image)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%
*/
MagickExport VirtualPixelMethod
GetImageVirtualPixelMethod(const Image *image)
{
  CacheInfo
    *cache_info;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (Cache) NULL);
  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  return(cache_info->virtual_pixel_method);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I n d e x e s                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetIndexes() returns the writeable colormap indexes associated with the
%  last call to SetImagePixels() or GetImagePixels(). NULL is returned if
%  colormap indexes are not available.
%
%  This function is deprecated since November 7, 2008.  Please use
%  AccessMutableIndexes() or AccessImmutableIndexes() instead of this
%  function.
%
%  The format of the GetIndexes() method is:
%
%      IndexPacket *GetIndexes(const Image *image)
%
%  A description of each parameter follows:
%
%    o indexes: GetIndexes() returns the indexes associated with the last
%      call to SetImagePixels() or GetImagePixels().
%
%    o image: The image.
%
%
*/
MagickExport IndexPacket *
GetIndexes(const Image *image)
{
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  return GetCacheViewIndexes(AccessDefaultCacheView(image));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t O n e P i x e l                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetOnePixel() returns a single pixel at the specified (x,y) location.
%  The image background color is returned if an error occurs.  This function
%  is convenient but performance will be poor if it is used too often.
%  GetOnePixel() is identical to AcquireOnePixel() except that exceptions
%  are implicitly delivered to the image.
%
%  The format of the GetOnePixel() method is:
%
%      PixelPacket GetOnePixel(const Image image,const long x,const long y)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o x,y:  These values define the location of the pixel to return.
%
*/
MagickExport PixelPacket
GetOnePixel(Image *image,const long x,const long y)
{
  PixelPacket
    pixel;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  (void) AcquireOneCacheViewPixel(AccessDefaultCacheView(image),
                                  &pixel,x,y,&image->exception);

  return pixel;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t P i x e l s                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetPixels() returns the pixels associated with the last call to
%  SetImagePixels() or GetImagePixels(). This is useful in order to access
%  an already selected region without passing the geometry of the region.
%
%  The format of the GetPixels() method is:
%
%      PixelPacket *GetPixels(const Image image)
%
%  A description of each parameter follows:
%
%    o pixels: GetPixels() returns the pixels associated with the last call
%      to SetImagePixels() or GetImagePixels().
%
%    o image: The image.
%
%
*/
MagickExport PixelPacket *
GetPixels(const Image *image)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return AccessCacheViewPixels(AccessDefaultCacheView(image));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t P i x e l C a c h e A r e a                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetPixelCacheArea() returns the area (width * height in pixels) consumed by
%  the current pixel cache.
%
%  The format of the GetPixelCacheArea() method is:
%
%      magick_off_t GetPixelCacheArea(const Image *image)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%
*/
MagickExport magick_off_t
GetPixelCacheArea(const Image *image)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return GetCacheViewArea(AccessDefaultCacheView(image));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t P i x e l C a c h e I n C o r e                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetPixelCacheInCore() tests to see the pixel cache is based on allocated
%  memory and therefore supports efficient random access.
%
%  The format of the GetPixelCacheInCore() method is:
%
%      MagickBool GetPixelCacheInCore(const Image *image)
%
%  A description of each parameter follows:
%
%    o image: Specifies a pointer to an Image structure.
%
%
*/
extern MagickBool
GetPixelCacheInCore(const Image *image)
{

  MagickBool
    status;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);

  status = MagickFalse;
  if (image->cache != (Cache) NULL)
    {
      CacheInfo
        *cache_info;

      cache_info=(CacheInfo *) image->cache;
      assert(cache_info->signature == MagickSignature);

      if ((image->cache->type == MemoryCache) ||
          ((image->cache->type == MapCache) && (image->cache->read_only)))
        status=MagickTrue;
    }

  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t P i x e l C a c h e P r e s e n t                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetPixelCachePresent() tests to see the pixel cache is present
%  and contains pixels.
%
%  The format of the GetPixelCachePresent() method is:
%
%      MagickBool GetPixelCachePresent(const Image *image)
%
%  A description of each parameter follows:
%
%    o image: Specifies a pointer to an Image structure.
%
%
*/
extern MagickExport MagickBool
GetPixelCachePresent(const Image *image)
{
  CacheInfo
    *cache_info;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);

  if (image->cache == (Cache) NULL)
    return MagickFalse;

  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  if ((cache_info->columns == 0) ||
      (cache_info->rows == 0))
    return MagickFalse;

  return MagickTrue;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   I n t e r p o l a t e C o l o r                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method InterpolateColor applies bi-linear interpolation between a pixel and
%  it's neighbors.
%
%  The format of the InterpolateColor method is:
%
%      PixelPacket InterpolateColor(const Image *image,const double x_offset,
%        const double y_offset,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o x_offset,y_offset: A double representing the current (x,y) position of
%      the pixel.
%
%
*/
MagickExport MagickPassFail
InterpolateViewColor(ViewInfo *view,
                     PixelPacket *color,
                     const double x_offset,
                     const double y_offset,
                     ExceptionInfo *exception)
{
  register const PixelPacket
    * restrict p;

  const Image
    * restrict image = ((const View *) view)->image;

  register MagickBool
    matte;

  double
    alpha,
    beta,
    one_minus_alpha,
    one_minus_beta,
    p0_area,
    p1_area,
    p2_area,
    p3_area,
    p_area;

  p=AcquireCacheViewPixels(view,MagickDoubleToLong(x_offset),
                           MagickDoubleToLong(y_offset),2,2,exception);
  if (p == (const PixelPacket *) NULL)
    return MagickFail;

  matte = image->matte && IsRGBColorspace(image->colorspace);

  alpha=x_offset-floor(x_offset);
  beta=y_offset-floor(y_offset);
  one_minus_alpha=1.0-alpha;
  one_minus_beta=1.0-beta;
  p0_area = ((!matte) || (p[0].opacity != TransparentOpacity)
             ? one_minus_beta * one_minus_alpha : 0.0);
  p1_area = ((!matte) || (p[1].opacity != TransparentOpacity)
             ? one_minus_beta * alpha : 0.0);
  p2_area = ((!matte) || (p[2].opacity != TransparentOpacity)
             ? beta * one_minus_alpha : 0.0);
  p3_area = ((!matte) || (p[3].opacity != TransparentOpacity)
             ? beta * alpha : 0.0);
  p_area = p0_area + p1_area + p2_area + p3_area;
  if (p_area <= 0.5/MaxRGBDouble)
    {
      color->red=0;
      color->green=0;
      color->blue=0;
      color->opacity=TransparentOpacity;
    }
  else
    {
      color->red=(Quantum)
        (((p0_area*p[0].red+p1_area*p[1].red+
           p2_area*p[2].red+p3_area*p[3].red)/p_area)+0.5);
      color->green=(Quantum)
        (((p0_area*p[0].green+p1_area*p[1].green+
           p2_area*p[2].green+p3_area*p[3].green)/p_area)+0.5);
      color->blue=(Quantum)
        (((p0_area*p[0].blue+p1_area*p[1].blue+
           p2_area*p[2].blue+p3_area*p[3].blue)/p_area)+0.5);
      if (!matte)
        color->opacity=OpaqueOpacity;
      else
        color->opacity=(Quantum)
          (one_minus_beta*(one_minus_alpha*p[0].opacity+alpha*p[1].opacity)+
           beta*(one_minus_alpha*p[2].opacity+alpha*p[3].opacity)+0.5);
    }

  return MagickPass;
}
MagickExport PixelPacket InterpolateColor(const Image *image,
  const double x_offset,const double y_offset,ExceptionInfo *exception)
{
  PixelPacket
    color;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if (InterpolateViewColor(AccessDefaultCacheView(image),&color,
                           x_offset,y_offset,exception) == MagickFail)
    color.red=color.green=color.blue=color.opacity=0U;
  return color;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   M o d i f y C a c h e                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ModifyCache() ensures that there is only a single reference to the pixel
%  cache to be modified, updating the provided cache pointer to point to
%  a clone of the original pixel cache if necessary.  This is used to
%  implement copy on write.
%
%  The format of the ModifyCache method is:
%
%      MagickPassFail ModifyCache(Image *image, ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o exception: Errors are reported here.
%
*/
MagickPassFail
ModifyCache(Image *image, ExceptionInfo *exception)
{
  CacheInfo
    * restrict cache_info;

  MagickPassFail
    status;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  status=MagickPass;

  /*
    Note that this function is normally executed for each and every
    scanline which is read/updated so it represents constant locking
    overhead.
  */
  LockSemaphoreInfo(image->semaphore);
  {
    MagickBool
      destroy_cache=MagickFalse;

    assert(image->cache != (Cache) NULL);
    cache_info=(CacheInfo *) image->cache;
    LockSemaphoreInfo(cache_info->reference_semaphore);
    {
      if ((cache_info->reference_count > 1) || (cache_info->read_only))
        {
          Image
            clone_image;

          (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                                "modify+clone %.1024s",cache_info->filename);
#if 0
          fprintf(stderr,"ModifyCache: Thread %d enters (cache_info = %p, reference_count=%lu, read_only=%u)\n",
                  omp_get_thread_num(),image->cache, cache_info->reference_count, cache_info->read_only);
#endif
          clone_image=(*image);
          /*
            Semaphore and reference count need to be initialized for the temporary
            Image copy since otherwise there may be deadlock in ClonePixelCache.
          */
          clone_image.semaphore=AllocateSemaphoreInfo();
          clone_image.reference_count=1;

          GetCacheInfo(&clone_image.cache);
          status=OpenCache(&clone_image,IOMode,exception);
          if (status != MagickFail)
            {
              /*
                Clone the pixel cache.
              */
              status=ClonePixelCache(image,&clone_image,exception);
              if (status == MagickFail)
                DestroyCacheInfo(clone_image.cache);
            }
          else
            {
              DestroyCacheInfo(clone_image.cache);
              clone_image.cache=(CacheInfo *) NULL;
            }
          DestroySemaphoreInfo(&clone_image.semaphore);

          if (status != MagickFail)
            {
              destroy_cache=MagickTrue;
              image->cache=clone_image.cache;
            }
          if (status == MagickFail)
            fprintf(stderr,"ModifyCache failed!\n"); /* oss-fuzz-20871 leaked clone_image.cache allocated by GetCacheInfo(&clone_image.cache) */
          /* fprintf(stderr,"ModifyCache: Thread %d exits (cache_info = %p)\n",
             omp_get_thread_num(),image->cache); */
        }
    }
    UnlockSemaphoreInfo(cache_info->reference_semaphore);

    /*
      Decrement the cache reference count, and destroys the origin
      cache if necessary.
    */
    if (destroy_cache)
      {
        DestroyCacheInfo(cache_info);
#if !defined(__COVERITY__) /* 384801 Unused value */
        cache_info=(CacheInfo *) NULL;
#endif /* if !defined(__COVERITY__) */
      }

    if (status != MagickFail)
      {
        /*
          Indicate that image will be (possibly) modified, and unset
          grayscale/monochrome flags.
        */
        image->taint=MagickTrue;
        image->is_grayscale=MagickFalse;
        image->is_monochrome=MagickFalse;

        /*
          Make sure that pixel cache reflects key image parameters
          such as storage class and colorspace.  Re-open cache if
          necessary.
        */
        cache_info=(CacheInfo *) image->cache;
        status=(((image->storage_class == cache_info->storage_class) &&
                 (image->colorspace == cache_info->colorspace) &&
                 (image->rows == cache_info->rows) &&
                 (image->columns == cache_info->columns)) ||
                (OpenCache(image,IOMode,exception)));
      }
  }
  UnlockSemaphoreInfo(image->semaphore);

  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   O p e n C a c h e V i e w                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  OpenCacheView() opens a view into the pixel cache.
%
%  The format of the OpenCacheView method is:
%
%      ViewInfo *OpenCacheView(Image *image)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%
*/
MagickExport ViewInfo *
OpenCacheView(Image *image)
{
  View
    *view=(View *) NULL;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);

  view=MagickAllocateAlignedMemory(View *,MAGICK_CACHE_LINE_SIZE,
                                   sizeof(View));
  if (view == (View *) NULL)
    MagickFatalError3(ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToAllocateCacheView);
  InitializeCacheView(image,view);
  return (ViewInfo *) view;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   P e r s i s t C a c h e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  PersistCache() attaches to or initializes a persistent pixel cache.  A
%  persistent pixel cache is one that resides on disk and is not destroyed
%  when the program exits.
%
%  The format of the PersistCache() method is:
%
%      MagickPassFail PersistCache(Image *image,const char *filename,
%        const MagickBool attach,magick_off_t *offset,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: PersistCache() returns MagickPass if the persistent pixel cache is
%      attached or initialized successfully otherwise MagickFail.
%
%    o image: The image.
%
%    o filename: The persistent pixel cache filename.
%
%    o attach: A value other than zero initializes the persistent pixel
%      cache.
%
%    o offset: The offset in the persistent cache to store pixels.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport MagickPassFail
PersistCache(Image *image,const char *filename,
             const MagickBool attach,magick_off_t *offset,
             ExceptionInfo *exception)
{
  CacheInfo
    *cache_info;

  Image
    *clone_image;


  long
    pagesize,
    y;

  register const PixelPacket
    *p;

  register PixelPacket
    *q;

  MagickPassFail
    status;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (void *) NULL);
  assert(filename != (const char *) NULL);
  assert(offset != (magick_off_t *) NULL);
  pagesize=MagickGetMMUPageSize();
  cache_info=(CacheInfo *) image->cache;
  if (attach)
    {
      /*
        Attach persistent pixel cache.
      */
      (void) strlcpy(cache_info->cache_filename,filename,MaxTextExtent);
      cache_info->type=DiskCache;
      cache_info->offset=(*offset);
      if (!OpenCache(image,ReadMode,exception))
        return(MagickFail);
      *offset+=cache_info->length+pagesize-(cache_info->length % pagesize);
      cache_info->read_only=MagickTrue;
      (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                            "Attach persistent cache %.1024s",
                            cache_info->filename);
      return(MagickPass);
    }
  LockSemaphoreInfo(cache_info->reference_semaphore);
  if ((cache_info->reference_count == 1) &&
      (cache_info->type != MemoryCache))
    {
      /*
        Usurp resident persistent pixel cache.
      */
      status=rename(cache_info->cache_filename,filename);
      if (status == 0)
        {
          (void) strlcpy(cache_info->cache_filename,filename,MaxTextExtent);
          UnlockSemaphoreInfo(cache_info->reference_semaphore);
          cache_info=(CacheInfo*) ReferenceCache(cache_info);
          *offset+=cache_info->length+pagesize-(cache_info->length % pagesize);
          (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                                "Usurp resident persistent cache");
          return(MagickPass);
        }
    }
  UnlockSemaphoreInfo(cache_info->reference_semaphore);
  /*
    Clone persistent pixel cache.
  */
  clone_image=CloneImage(image,image->columns,image->rows,MagickPass,exception);
  if (clone_image == (Image *) NULL)
    return(MagickFail);
  cache_info=(CacheInfo *) clone_image->cache;
  (void) strlcpy(cache_info->cache_filename,filename,MaxTextExtent);
  cache_info->type=DiskCache;
  cache_info->offset=(*offset);
  if (!OpenCache(clone_image,IOMode,exception))
    {
      DestroyImage(clone_image);
      return(MagickFail);
    }
  y=0;
  {
    ViewInfo
      *clone_view,
      *image_view;

    const IndexPacket
      *indexes;

    IndexPacket
      *clone_indexes;

    image_view=OpenCacheView(image);
    clone_view=OpenCacheView(clone_image);
    if ((image_view != (ViewInfo *) NULL) &&
        (clone_view != (ViewInfo *) NULL))
      {
        for (y=0; y < (long) image->rows; y++)
          {
            p=AcquireCacheViewPixels(image_view,0,y,image->columns,1,exception);
            q=SetCacheViewPixels(clone_view,0,y,clone_image->columns,1,exception);
            if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
              break;
            (void) memcpy(q,p,image->columns*sizeof(PixelPacket));
            clone_indexes=GetCacheViewIndexes(clone_view);
            indexes=AcquireCacheViewIndexes(image_view);
            if ((clone_indexes != (IndexPacket *) NULL) &&
                (indexes != (const IndexPacket *) NULL))
              (void) memcpy(clone_indexes,indexes,image->columns*sizeof(IndexPacket));
            if (!SyncCacheViewPixels(clone_view,exception))
              break;
          }
      }
    CloseCacheView(image_view);
    CloseCacheView(clone_view);
  }
  if (y < (long) image->rows)
    {
      DestroyImage(clone_image);
      return(MagickFail);
    }
  *offset+=cache_info->length+pagesize-(cache_info->length % pagesize);
  DestroyImage(clone_image);
  (void) LogMagickEvent(CacheEvent,GetMagickModule(),"Clone persistent cache");
  return(MagickPass);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e f e r e n c e C a c h e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReferenceCache() increments the reference count associated with the pixel
%  cache returning a pointer to the cache.
%
%  The format of the ReferenceCache method is:
%
%      Cache ReferenceCache(Cache cache_info)
%
%  A description of each parameter follows:
%
%    o cache_info: The cache_info.
%
%
*/
Cache
ReferenceCache(Cache cache_info)
{
  assert(cache_info != (_CacheInfoPtr_) NULL);
  assert(cache_info->signature == MagickSignature);
  LockSemaphoreInfo(cache_info->reference_semaphore);
  cache_info->reference_count++;
  (void) LogMagickEvent(CacheEvent,GetMagickModule(),
                        "reference (reference count now %ld) %.1024s",
                        cache_info->reference_count, cache_info->filename);
  UnlockSemaphoreInfo(cache_info->reference_semaphore);
  return(cache_info);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t C a c h e V i e w P i x e l s                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetCacheViewPixels() gets pixels from the in-memory or disk pixel cache as
%  defined by the geometry parameters.   A pointer to the pixels is returned
%  if the pixels are transferred, otherwise a NULL is returned.
%
%  The format of the SetCacheViewPixels method is:
%
%      PixelPacket *SetCacheViewPixels(ViewInfo *view,const long x,
%        const long y,const unsigned long columns,const unsigned long rows)
%
%  A description of each parameter follows:
%
%    o view: The address of a structure of type ViewInfo.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o exception: Any errors are reported here.
%
*/
MagickExport PixelPacket *
SetCacheViewPixels(ViewInfo *view,const long x,const long y,
                   const unsigned long columns,const unsigned long rows,
                   ExceptionInfo *exception)
{
  View
    *view_info = (View *) view;

  assert(view_info != (const View *) NULL);
  assert(view_info->signature == MagickSignature);
  return SetCacheNexus(view_info->image,x,y,columns,rows,
                       &view_info->nexus_info,exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t I m a g e P i x e l s                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetImagePixels() initializes a pixel region for write-only access.
%  If the region is successfully initialized a pointer to a PixelPacket
%  array representing the region is returned, otherwise NULL is returned.
%  The returned pointer may point to a temporary working buffer for the
%  pixels or it may point to the final location of the pixels in memory.
%
%  Write-only access means that any existing pixel values corresponding to
%  the region are ignored.  This is useful while the initial image is being
%  created from scratch, or if the existing pixel values are to be
%  completely replaced without need to refer to their pre-existing values.
%  The application is free to read and write the pixel buffer returned by
%  SetImagePixels() any way it pleases. SetImagePixels() does not initialize
%  the pixel array values. Initializing pixel array values is the
%  application's responsibility.
%
%  Performance is maximized if the selected area is part of one row, or
%  one or more full rows, since then there is opportunity to access the
%  pixels in-place (without a copy) if the image is in RAM, or in a
%  memory-mapped file. The returned pointer should *never* be deallocated
%  by the user.
%
%  Pixels accessed via the returned pointer represent a simple array of type
%  PixelPacket. If the image storage class is PsudeoClass, call
%  AccessMutableIndexes() after invoking GetImagePixels() to obtain
%  the colormap indexes (of type IndexPacket) corresponding to the region.
%  Once the PixelPacket (and/or IndexPacket) array has been updated, the
%  changes must be saved back to the underlying image using SyncCacheNexus()
%  or they may be lost.
%
%  The format of the SetImagePixels() method is:
%
%      PixelPacket *SetImagePixels(Image *image,const long x,const long y,
%        const unsigned long columns,const unsigned long rows)
%
%  A description of each parameter follows:
%
%    o pixels: SetImagePixels returns a pointer to the pixels if they are
%      transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%
*/
MagickExport PixelPacket *
SetImagePixels(Image *image,const long x,const long y,
               const unsigned long columns,const unsigned long rows)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return SetCacheViewPixels(AccessDefaultCacheView(image),
                            x,y,columns,rows,&image->exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t I m a g e P i x e l s E x                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetImagePixelsEx() initializes a pixel region for write-only access.
%  It is similar to SetImagePixels() except that any exception information
%  is written to a user provided exception structure.
%
%  The format of the SetImagePixelsEx() method is:
%
%      PixelPacket *SetImagePixelsEx(Image *image,const long x,const long y,
%        const unsigned long columns,const unsigned long rows,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o pixels: SetImagePixelsEx returns a pointer to the pixels if they are
%      transferred, otherwise a NULL is returned.
%
%    o image: The image.
%
%    o x,y,columns,rows:  These values define the perimeter of a region of
%      pixels.
%
%    o exception: Any error details are reported here.
%
%
*/
MagickExport PixelPacket *
SetImagePixelsEx(Image *image,const long x,const long y,
                 const unsigned long columns,const unsigned long rows,
                 ExceptionInfo *exception)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return SetCacheViewPixels(AccessDefaultCacheView(image),
                            x,y,columns,rows,exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t I m a g e V i r t u a l P i x e l M e t h o d                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetImageVirtualPixelMethod() sets the "virtual pixels" method for the
%  image.  A virtual pixel is any pixel access that is outside the boundaries
%  of the image cache.
%
%  The format of the SetImageVirtualPixelMethod() method is:
%
%      SetImageVirtualPixelMethod(const Image *image,
%        const VirtualPixelMethod method)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o type: choose from these access types:
%
%        EdgeVPType:  the edge pixels of the image extend infinitely.
%        Any pixel outside the image is assigned the same value as the
%        pixel at the edge closest to it.
%
%        TileVPType:  the image extends periodically or tiled.  The pixels
%        wrap around the edges of the image.
%
%        MirrorVPType:  mirror the image at the boundaries.
%
%        ConstantVPType:  every value outside the image is a constant as
%        defines by the pixel parameter.
%
%
*/
MagickExport MagickPassFail
SetImageVirtualPixelMethod(const Image *image,
                           const VirtualPixelMethod method)
{
  CacheInfo
    *cache_info;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (Cache) NULL);
  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  cache_info->virtual_pixel_method=method;
  return MagickPass;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S y n c C a c h e V i e w P i x e l s                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SyncCacheViewPixels() saves the view pixels to the in-memory or disk cache.
%  The method returns MagickPass if the pixel region is synced, otherwise
%  MagickFail.
%
%  The format of the SyncCacheViewPixels method is:
%
%      MagickPassFail SyncCacheViewPixels(const ViewInfo *view,
%                                         ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o view: The address of a structure of type ViewInfo.
%
%    o exception: Any errors are reported here.
%
*/
MagickExport MagickPassFail
SyncCacheViewPixels(const ViewInfo *view,ExceptionInfo *exception)
{
  View
    *view_info = (View *) view;

  MagickPassFail
    status;

  assert(view_info != (View *) NULL);
  assert(view_info->signature == MagickSignature);
  status=SyncCacheNexus(view_info->image,&view_info->nexus_info,exception);
  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S y n c I m a g e P i x e l s                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SyncImagePixels() saves the image pixels to the in-memory or disk cache.
%  The method returns MagickPass if the pixel region is synced, otherwise MagickFail.
%
%  The format of the SyncImagePixels() method is:
%
%      MagickPassFail SyncImagePixels(Image *image)
%
%  A description of each parameter follows:
%
%    o status: SyncImagePixels() returns MagickPass if the image pixels are
%      transferred to the in-memory or disk cache otherwise MagickFail.
%
%    o image: The image.
%
*/
MagickExport MagickPassFail
SyncImagePixels(Image *image)
{
  assert (image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return SyncCacheViewPixels(AccessDefaultCacheView(image),
                             &image->exception);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S y n c I m a g e P i x e l s E x                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SyncImagePixelsEx() saves the image pixels to the in-memory or disk cache.
%  The method returns MagickPass if the pixel region is synced, otherwise
%  MagickFail.
%
%  The format of the SyncImagePixelsEx() method is:
%
%      MagickPassFail SyncImagePixelsEx(Image *image,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o status: SyncImagePixelsEx() returns MagickPass if the image pixels are
%      transferred to the in-memory or disk cache otherwise MagickFail.
%
%    o image: The image.
%
%    o exception: Any error details are reported here.
%
*/
MagickExport MagickPassFail
SyncImagePixelsEx(Image *image,ExceptionInfo *exception)
{
  assert (image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  return SyncCacheViewPixels(AccessDefaultCacheView(image),exception);
}
