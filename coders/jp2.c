/*
% Copyright (C) 2003-2022 GraphicsMagick Group
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
%                              JJJ  PPPP    222                               %
%                               J   P   P  2   2                              %
%                               J   PPPP     22                               %
%                            J  J   P       2                                 %
%                             JJ    P      22222                              %
%                                                                             %
%                                                                             %
%                    Read/Write JPEG-2000 Image Format.                       %
%                                                                             %
%                                                                             %
%                                John Cristy                                  %
%                                Nathan Brown                                 %
%                                 June 2001                                   %
%                              Bob Friesenhahn                                %
%                               February 2003                                 %
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
#include "magick/pixel_cache.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/profile.h"
#include "magick/resource.h"
#include "magick/utility.h"
#if defined(HasJP2)
#  if !defined(uchar)
#    define uchar  unsigned char
#  endif
#  if !defined(ushort)
#    define ushort  unsigned short
#  endif
#  if !defined(uint)
#    define uint  unsigned int
#  endif
#  if !defined(longlong)
#    define longlong  long long
#  endif
#  if !defined(ulonglong)
#    define ulonglong  unsigned long long
#  endif

#  ifdef __VMS
#    define JAS_VERSION 1.700.0
#    define PACKAGE jasper
#    define VERSION 1.700.0
#  endif /* ifdef __VMS */
#  undef PACKAGE_NAME
#  undef PACKAGE_STRING
#  undef PACKAGE_TARNAME
#  undef PACKAGE_VERSION
#  include "jasper/jasper.h"
#  undef PACKAGE_NAME
#  undef PACKAGE_STRING
#  undef PACKAGE_TARNAME
#  undef PACKAGE_VERSION
/*
  Old JasPer uses non-persistent '!defined(EXCLUDE_FOO_SUPPORT)' and
  modern JasPer uses persistent 'if defined(JAS_INCLUDE_FOO_CODEC)'
  in jas_image.h
*/
#  if defined(EXCLUDE_JP2_SUPPORT)
#    undef HAVE_JP2_DECODE
#  endif
#  if defined(EXCLUDE_JPC_SUPPORT)
#    undef HAVE_JPC_DECODE
#  endif
#  if defined(EXCLUDE_PGX_SUPPORT)
#    undef HAVE_PGX_DECODE
#  endif

#if defined(HAVE_JAS_INIT_LIBRARY)
# define HAVE_JAS_STREAM_IO_V3
#endif

#if 0
/* Development JasPer 3.0.0 jas_init_library() is not yet ready for our purposes */
#if !(defined(MAGICK_ENABLE_JAS_INIT_LIBRARY) && MAGICK_ENABLE_JAS_INIT_LIBRARY)
#undef HAVE_JAS_INIT_LIBRARY
#endif /* if !(defined(MAGICK_ENABLE_JAS_INIT_LIBRARY) && MAGICK_ENABLE_JAS_INIT_LIBRARY) */
#endif

#if defined(HAVE_PTHREAD) || defined(MSWINDOWS) || defined(HAVE_OPENMP)
#  define JP2_HAVE_THREADS 1
#else
#  define JP2_HAVE_THREADS 0
#endif


/*
  Forward declarations.
*/
static unsigned int
  WriteJP2Image(const ImageInfo *,Image *);

static MagickBool jasper_initialized=MagickFalse;
static const char jasper_enc_options[][11] =
  {
    "cblkheight",
    "cblkwidth",
    "debug",
    "eph",
    "ilyrrates",
    "imgareatlx",
    "imgareatly",
    "lazy",
    "mode",
    "nomct",
    "numgbits",
    "numrlvls",
    "prcheight",
    "prcwidth",
    "prg",
    "pterm",
    "rate",
    "resetprob",
    "segsym",
    "sop",
    "termall",
    "tilegrdtlx",
    "tilegrdtly",
    "tileheight",
    "tilewidth",
    "vcausal"
  };

static const char jasper_dec_options[][12] =
  {
    "allow_trunc",
    "debug",
    "max_samples",
    "maxlyrs",
    "maxpkts",
    "version"
  };


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s J P 2                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsJP2 returns True if the image format type, identified by the
%  magick string, is JP2.
%
%  The format of the IsJP2 method is:
%
%      unsigned int IsJP2(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsJP2 returns True if the image format type is JP2.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsJP2(const unsigned char *magick,const size_t length)
{
  if (length < 9)
    return(False);
  if (memcmp(magick+4,"\152\120\040\040\015",5) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s J P C                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsJPC returns True if the image format type, identified by the
%  magick string, is JPC.
%
%  The format of the IsJPC method is:
%
%      unsigned int IsJPC(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsJPC returns True if the image format type is JPC.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsJPC(const unsigned char *magick,const size_t length)
{
  if (length < 2)
    return(False);
  if (memcmp(magick,"\377\117",2) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s P G X                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsPGX returns True if the image format type, identified by the
%  magick string, is PGX.
%
%  The format of the IsPGX method is:
%
%      unsigned int IsPGX(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsPGX returns True if the image format type is PGX.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsPGX(const unsigned char *magick,const size_t length)
{
  if (length < 5)
    return(False);
  if ((memcmp(magick,"PG ML",5) == 0) || (memcmp(magick,"PG LM",5) == 0))
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d J P 2 I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadJP2Image reads a JPEG 2000 Image file (JP2) or JPEG 2000
%  codestream (JPC) image file and returns it.  It allocates the memory
%  necessary for the new Image structure and returns a pointer to the new
%  image or set of images.
%
%  JP2 support is originally written by Nathan Brown, nathanbrown@letu.edu.
%
%  The format of the ReadJP2Image method is:
%
%      Image *ReadJP2Image(const ImageInfo *image_info,
%                          ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadJP2Image returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
*/

typedef struct _StreamManager
{
  jas_stream_t
    *stream;

  Image
    *image;
} StreamManager;

/*
  I/O read/write callbacks changed

  Cnt argument changed from 'int' to 'unsigned' on 6/29/20 (2.0.19).

  Write write buf pointer changed from 'char *' to 'const char *' on 8/14/20

  Old interface:
  int (*read_)(jas_stream_obj_t *obj, char *buf, int cnt);
  int (*write_)(jas_stream_obj_t *obj, char *buf, int cnt);

  New interface:
  int (*read_)(jas_stream_obj_t *obj, char *buf, unsigned cnt);
  int (*write_)(jas_stream_obj_t *obj, const char *buf, unsigned cnt);

  In Jasper 3.0.0 the interface changed again:
  ssize_t (*read_)(jas_stream_obj_t *obj, char *buf, size_t cnt);
  ssize_t (*write_)(jas_stream_obj_t *obj, const char *buf, size_t cnt);

  We have yet to find a useful way to determine the version of the
  JasPer library using the C pre-processor.
 */

/* Read characters from a file object. */
/* ssize_t (*read_)(jas_stream_obj_t *obj, char *buf, size_t cnt); */
#if defined(HAVE_JAS_STREAM_IO_V3)
static ssize_t BlobRead(jas_stream_obj_t *obj, char *buf, size_t cnt)
#else
static int BlobRead(jas_stream_obj_t *obj, char *buf, unsigned cnt)
#endif
{
  size_t
    count;

  StreamManager
    *source = (StreamManager *) obj;

  count=ReadBlob(source->image,(size_t) cnt,(void *) buf);
  return (count);
}

/* Write characters to a file object. */
/* ssize_t (*write_)(jas_stream_obj_t *obj, const char *buf, size_t cnt); */
#if defined(HAVE_JAS_STREAM_IO_V3)
static ssize_t  BlobWrite(jas_stream_obj_t *obj, const char *buf, size_t cnt)
#else
static int BlobWrite(jas_stream_obj_t *obj, const char *buf, unsigned cnt)
#endif
{
  size_t
    count;

  StreamManager
    *source = (StreamManager *) obj;

  count=WriteBlob(source->image,(size_t) cnt,(void *) buf);
  return(count);
}

/* Set the position for a file object. */
/* long (*seek_)(jas_stream_obj_t *obj, long offset, int origin); */
static long BlobSeek(jas_stream_obj_t *obj,long offset,int origin)
{
  StreamManager
    *source = (StreamManager *) obj;

  return (SeekBlob(source->image,offset,origin));
}

/* Close a file object. */
/* int (*close_)(jas_stream_obj_t *obj); */
static int BlobClose(jas_stream_obj_t *obj)
{
  StreamManager
    *source = (StreamManager *) obj;

  CloseBlob(source->image);
  jas_free(source);
  return (0);
}


static jas_stream_t *JP2StreamManager(jas_stream_ops_t *stream_ops, Image *image)
{
  jas_stream_t
    *stream;

  StreamManager
    *source;

  stream=(jas_stream_t *) jas_malloc(sizeof(jas_stream_t));
  if (stream == (jas_stream_t *) NULL)
    return((jas_stream_t *) NULL);
  (void) memset(stream,0,sizeof(jas_stream_t));
  stream->rwlimit_=(-1);
  stream->obj_=(jas_stream_obj_t *) jas_malloc(sizeof(StreamManager));
  if (stream->obj_ == (jas_stream_obj_t *) NULL)
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "jas_malloc() failed!");
      jas_free(stream);
      return((jas_stream_t *) NULL);
    }
  stream->ops_=stream_ops;
  stream->openmode_=JAS_STREAM_READ | JAS_STREAM_WRITE | JAS_STREAM_BINARY;
  stream->bufbase_=stream->tinybuf_;
  stream->bufsize_=1;
  stream->bufstart_=(&stream->bufbase_[JAS_STREAM_MAXPUTBACK]);
  stream->ptr_=stream->bufstart_;
  stream->bufmode_|=JAS_STREAM_UNBUF & JAS_STREAM_BUFMODEMASK;
  source=(StreamManager *) stream->obj_;
  source->image=image;
  return(stream);
}

#if defined(HAVE_JAS_INIT_LIBRARY)
#  define JAS_CLEANUP_THREAD() jas_cleanup_thread()
#else
#  define JAS_CLEANUP_THREAD()
#endif

#define ThrowJP2ReaderException(code_,reason_,image_)                   \
  {                                                                     \
    for (component=0; component < (long) number_components; component++) \
      MagickFreeResourceLimitedMemory(channel_lut[component]);          \
    if (pixels)                                                         \
      jas_matrix_destroy(pixels);                                       \
    if (jp2_stream)                                                     \
      (void) jas_stream_close(jp2_stream);                              \
    if (jp2_image)                                                      \
      jas_image_destroy(jp2_image);                                     \
    MagickFreeMemory(options);                                          \
    JAS_CLEANUP_THREAD();                                               \
    ThrowReaderException(code_,reason_,image_);                         \
  }

#define ThrowJP2WriterException(code_,reason_,image_)   \
  {                                                     \
    JAS_CLEANUP_THREAD();                               \
    ThrowWriterException(code_,reason_,image_);         \
  }

/*
  Initialize Jasper
*/
#if HAVE_JAS_INIT_LIBRARY
static void *alloc_rlm(struct jas_allocator_s *allocator, size_t size)
{
  char *p;
  (void) allocator;
  /* JasPer expects its allocator to return non-null for zero size */
  p=_MagickAllocateResourceLimitedMemory(size == 0 ? 1 : size);
  /* fprintf(stderr,"alloc_rlm(%p, %zu) -> %p\n", allocator, size, p); */
  return p;
}
static void free_rlm(struct jas_allocator_s *allocator, void *pointer)
{
  (void) allocator;
  /* fprintf(stderr,"free_rlm(%p, %p\n", allocator, pointer); */
  _MagickFreeResourceLimitedMemory(pointer);
}
static void *realloc_rlm(struct jas_allocator_s *allocator, void *pointer,
                         size_t new_size)
{
  char *p;
  (void) allocator;
  p =_MagickReallocateResourceLimitedMemory(pointer,1,new_size,0);
  /* fprintf(stderr,"realloc_rlm(%p, %p, %zu) -> %p\n", allocator, pointer, new_size, p); */
  return p;
}
#endif /* if HAVE_JAS_INIT_LIBRARY */
static MagickPassFail initialize_jasper(ExceptionInfo *exception)
{
  (void) exception;
  if (!jasper_initialized)
    {
#if HAVE_JAS_INIT_LIBRARY
      {
        /* static jas_std_allocator_t allocator; */
        static jas_allocator_t allocator;

        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Initializing JasPer...");
        /*
          Configure the library using the default configuration settings.
        */
        jas_conf_clear();

        /*
          Provide our own resource-limited memory allocation
          functions.

          See src/libjasper/include/jasper/jas_malloc.h
        */

        /*
          Function to clean up the allocator when no longer needed.
          The allocator cannot be used after the clean-up operation is performed.
          This function pointer may be null, in which case the clean-up operation
          is treated as a no-op.
        */
        allocator.cleanup = 0;

        /*
          Function to allocate memory.
          This function should have behavior similar to malloc.
        */
        allocator.alloc = alloc_rlm;

        /*
          Function to deallocate memory.
          This function should have behavior similar to free.
        */
        allocator.free = free_rlm;

        /*
          Function to reallocate memory.
          This function should have behavior similar to realloc.
        */
        allocator.realloc = realloc_rlm;
        /* jas_std_allocator_init(&allocator); */ /* Uses JasPer allocators */
        jas_conf_set_allocator(&allocator); /* Assigns jas_allocator_t to jas_conf.allocator in library */
        /* jas_conf_set_debug_level(cmdopts->debug); */

        /*
          Tell JasPer how much memory it could ever be allowed to use.
        */
        {
          size_t max_mem_gm = (size_t) GetMagickResourceLimit(MemoryResource);
          size_t max_mem_jas = jas_get_total_mem_size();
          if (max_mem_jas == 0)
            max_mem_jas=max_mem_gm;
          jas_conf_set_max_mem_usage(Min(max_mem_jas,max_mem_gm));
        }

        /*
          Inform JasPer that app may be multi-threaded
        */
        jas_conf_set_multithread(JP2_HAVE_THREADS);

        /* Perform global initialization for the JasPer library. */
        if (jas_init_library() == 0)
          {
            jasper_initialized=MagickTrue;
            /* jas_set_debug_level(110); */
          }
        else
          {
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "jas_init_library() failed!");
          }
      }
#else
      {
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Initializing JasPer...");
        if (jas_init() == 0)
          {
            jasper_initialized=MagickTrue;
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Initialized JasPer");
          }
        else
          {
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "jas_init() failed!");
          }
      }
#endif  /* HAVE_JAS_INIT_LIBRARY */

      if (!jasper_initialized)
        {
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Failed to initialize JasPer!");
        }
    }

  return jasper_initialized ? MagickPass : MagickFail;
}


/*
  Cleanup Jasper
*/
static void cleanup_jasper(void)
{
  if (jasper_initialized)
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Destroying JasPer...");
#if HAVE_JAS_INIT_LIBRARY
      /* Perform global cleanup for the JasPer library. */
      jas_cleanup_library();
#else
      jas_cleanup();
#endif /* if HAVE_JAS_INIT_LIBRARY */
      jasper_initialized=MagickFalse;
    }
}

static Image *ReadJP2Image(const ImageInfo *image_info,
                           ExceptionInfo *exception)
{
  Image
    *image;

  long
    y;

  jas_image_t
    *jp2_image = (jas_image_t *) NULL;

  jas_matrix_t
    *pixels = (jas_matrix_t *) NULL;

  jas_stream_ops_t
    StreamOperators =
    {
      BlobRead,
      BlobWrite,
      BlobSeek,
      BlobClose
    };

  jas_stream_t
    *jp2_stream = (jas_stream_t *) NULL;

  register long
    x;

  register PixelPacket
    *q;

  magick_off_t
    pos;

  int
    component,
    components[4],
    number_components=0;

  Quantum
    *channel_lut[4];

  char
    option_keyval[MaxTextExtent],
    *options = NULL;

  unsigned int
    status;

  MagickBool
    jp2_hdr,
    jpc_hdr,
    pgx_hdr;

  /*
    Initialize Jasper
  */
  if (initialize_jasper(exception) != MagickPass)
    {
      return (Image *) NULL;
    }

#if HAVE_JAS_INIT_LIBRARY
  /*
    Perform any per-thread initialization for the JasPer library.
  */
  if (jas_init_thread())
    {
      /* Handle the initialization error. */
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "jas_init_thread() failed!");
      return (Image *) NULL;
    }
#endif /* if HAVE_JAS_INIT_LIBRARY */

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  (void) memset(channel_lut,0,sizeof(channel_lut));
  image=AllocateImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == False)
    ThrowJP2ReaderException(FileOpenError,UnableToOpenFile,image);

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Requested format is \"%s\"",
                        image_info->magick);

  /*
    Get the header and auto-detect apparent format.
  */
  {
    size_t
      magick_length;

    unsigned char
      magick[16];

    const MagickInfo
      *magick_info;

    /* Get current seek position (normally 0) */
    pos=TellBlob(image);

    /* Read header */
    if ((magick_length=ReadBlob(image,sizeof(magick),magick)) != sizeof(magick))
      {
        ThrowJP2ReaderException(CorruptImageError,UnexpectedEndOfFile,image);
      }

    /* Restore seek position */
    if (SeekBlob(image,pos,SEEK_SET) != pos)
      {
        ThrowJP2ReaderException(BlobError,UnableToSeekToOffset,image);
      }

    /* Inspect header to see what it might actually be */
    jp2_hdr=IsJP2(magick,sizeof(magick));
    jpc_hdr=IsJPC(magick,sizeof(magick));
    pgx_hdr=IsPGX(magick,sizeof(magick));

    /*
      If input format was previously auto-detected or specified, then
      assure that header matches what was specified.
    */
    if (((LocaleCompare(image_info->magick,"JP2") == 0) && !jp2_hdr) ||
        (((LocaleCompare(image_info->magick,"JPC") == 0) ||
          (LocaleCompare(image_info->magick,"J2C") == 0)) && !jpc_hdr) ||
        ((LocaleCompare(image_info->magick,"PGX") == 0) && !pgx_hdr))
      {
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Not a \"%s\" file!", image_info->magick);
        ThrowJP2ReaderException(CorruptImageError,ImproperImageHeader,image);
      }

    /*
      Throw exception if header is not one we expect.
    */
    if (!jp2_hdr && !jpc_hdr && !pgx_hdr)
      {
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Header is not a supported type for this coder");
        ThrowJP2ReaderException(CorruptImageError,ImproperImageHeader,image);
      }

    /*
      Check if we are allowed to decode this format.
    */
    if (((magick_info = GetMagickInfo(image_info->magick,exception)) ==
         (const MagickInfo *) NULL) ||
        (magick_info->decoder == (DecoderHandler) NULL))
      {
        ThrowJP2ReaderException(DelegateError,UnableToDecodeImageFile,image);
      }
  }

  /*
    Obtain a JP2 Stream.
  */
  jp2_stream=JP2StreamManager(&StreamOperators, image);
  if (jp2_stream == (jas_stream_t *) NULL)
    ThrowJP2ReaderException(DelegateError,UnableToManageJP2Stream,image);

  /*
    Support passing Jasper options.
  */
  {
    unsigned int
      i;

    MagickBool
      max_samples_specified = MagickFalse;

    for (i=0; i < ArraySize(jasper_dec_options); i++)
      {
        const char
          *option = jasper_dec_options[i];

        const char
          *value;

        if ((value=AccessDefinition(image_info,"jp2",option)) != NULL)
          {
            FormatString(option_keyval,"%s=%.1024s ",option,value);
            ConcatenateString(&options,option_keyval);

            if (LocaleCompare(option,"max_samples") == 0)
              max_samples_specified=MagickTrue;

            /* Setting debug mode seems to require extra assistance */
            if (LocaleCompare(option,"debug") == 0)
              jas_setdbglevel(atoi(value));
          }
      }

    /*
      If max_samples argument was not specified, then pass options
      argument which specifies "max_samples" to cap memory usage.
    */
    if (!max_samples_specified)
      {
        const magick_uint64_t memory_limit = (magick_uint64_t) GetMagickResourceLimit(MemoryResource);
        const magick_uint64_t max_samples = memory_limit/4U * sizeof(magick_uint32_t);

        FormatString(option_keyval,"max_samples=%" MAGICK_UINT64_F "u ", max_samples);
        ConcatenateString(&options,option_keyval);
      }

    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "JP2 options = \"%s\"", options);
  }

  /*
    Decode
  */
  {
    int
      jas_fmt = -1;

    const char *
      jas_fmt_str = NULL;

    if (jp2_hdr)
      jas_fmt_str = "jp2";
    else if (jpc_hdr)
      jas_fmt_str = "jpc";
    else if (pgx_hdr)
      jas_fmt_str = "pgx";

    if (jas_fmt_str != (const char *) NULL)
      {
        jas_fmt = jas_image_strtofmt(jas_fmt_str);
        if (-1 != jas_fmt)
          {
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Decoding %s...", jas_fmt_str);
            jp2_image=jas_image_decode(jp2_stream,jas_fmt,options);
          }
        else
          {
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "JasPer does not support format %s!",
                                  jas_fmt_str);
          }
      }
  }

  MagickFreeMemory(options);

  if (jp2_image == (jas_image_t *) NULL)
    ThrowJP2ReaderException(DelegateError,UnableToDecodeImageFile,image);

  /*
    Validate that we can handle the image and obtain component
    indexes.
  */
  switch (jas_clrspc_fam(jas_image_clrspc(jp2_image)))
    {
    case JAS_CLRSPC_FAM_RGB:
      {
        if (((components[0]=
              jas_image_getcmptbytype(jp2_image,
                                      JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R))) < 0) ||
            ((components[1]=
              jas_image_getcmptbytype(jp2_image,
                                      JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G))) < 0) ||
            ((components[2]=
              jas_image_getcmptbytype(jp2_image,
                                      JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B))) < 0))
          {
            ThrowJP2ReaderException(CorruptImageError,MissingImageChannel,image);
          }
        number_components=3;
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Image is in RGB colorspace family");
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "RED is in channel %d, GREEN is in channel %d, BLUE is in channel %d",
                              components[0],components[1],components[2]);

        if((components[3]=jas_image_getcmptbytype(jp2_image,
                                                  JAS_IMAGE_CT_COLOR(JAS_IMAGE_CT_OPACITY))) > 0)
          {
            image->matte=MagickTrue;
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "OPACITY is in channel %d",components[3]);
            number_components++;
          }
        break;
      }
    case JAS_CLRSPC_FAM_GRAY:
      {
        if ((components[0]=
             jas_image_getcmptbytype(jp2_image,
                                     JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_GRAY_Y))) < 0)
          ThrowJP2ReaderException(CorruptImageError,MissingImageChannel,image);
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Image is in GRAY colorspace family");
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "GRAY is in channel %d",components[0]);
        number_components=1;
        break;
      }
    case JAS_CLRSPC_FAM_YCBCR:
      {
        components[0]=jas_image_getcmptbytype(jp2_image,JAS_IMAGE_CT_YCBCR_Y);
        components[1]=jas_image_getcmptbytype(jp2_image,JAS_IMAGE_CT_YCBCR_CB);
        components[2]=jas_image_getcmptbytype(jp2_image,JAS_IMAGE_CT_YCBCR_CR);
        if ((components[0] < 0) || (components[1] < 0) || (components[2] < 0))
          ThrowJP2ReaderException(CorruptImageError,MissingImageChannel,image);
        number_components=3;
        components[3]=jas_image_getcmptbytype(jp2_image,JAS_IMAGE_CT_OPACITY);
        if (components[3] > 0)
          {
            image->matte=True;
            number_components++;
          }
        image->colorspace=YCbCrColorspace;
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Image is in YCBCR colorspace family");
        break;
      }
    default:
      {
        ThrowJP2ReaderException(CoderError,ColorspaceModelIsNotSupported,image);
      }
    }
  image->columns=jas_image_width(jp2_image);
  image->rows=jas_image_height(jp2_image);
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "columns=%lu rows=%lu components=%d",image->columns,image->rows,
                        number_components);
  for (component=0; component < number_components; component++)
    {
      if(((unsigned long) jas_image_cmptwidth(jp2_image,components[component]) != image->columns) ||
         ((unsigned long) jas_image_cmptheight(jp2_image,components[component]) != image->rows) ||
         (jas_image_cmpttlx(jp2_image, components[component]) != 0) ||
         (jas_image_cmpttly(jp2_image, components[component]) != 0) ||
         (jas_image_cmpthstep(jp2_image, components[component]) != 1) ||
         (jas_image_cmptvstep(jp2_image, components[component]) != 1) ||
         (jas_image_cmptsgnd(jp2_image, components[component]) != false))
        ThrowJP2ReaderException(CoderError,IrregularChannelGeometryNotSupported,image);
    }

  image->matte=number_components > 3;
  for (component=0; component < number_components; component++)
    {
      unsigned int
        component_depth;

      component_depth=jas_image_cmptprec(jp2_image,components[component]);
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Component[%d] depth is %u",component,component_depth);
      if (0 == component)
        image->depth=component_depth;
      else
        image->depth=Max(image->depth,component_depth);
    }
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Image depth is %u",image->depth);
  if (image_info->ping)
    {
      (void) jas_stream_close(jp2_stream);
      jas_image_destroy(jp2_image);
#if HAVE_JAS_INIT_LIBRARY
      /* Perform any per-thread clean-up for the JasPer library. */
      JAS_CLEANUP_THREAD();
#endif /* if HAVE_JAS_INIT_LIBRARY */
      return(image);
    }

  if (CheckImagePixelLimits(image, exception) != MagickPass)
    ThrowJP2ReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);

  /*
    Allocate Jasper pixels.
  */
  pixels=jas_matrix_create(1,(unsigned int) image->columns);
  if (pixels == (jas_matrix_t *) NULL)
    ThrowJP2ReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  /*
    Allocate and populate channel LUTs
  */
  for (component=0; component < (long) number_components; component++)
    {
      unsigned long
        component_depth,
        i,
        max_value;

      double
        scale_to_quantum;

      component_depth=jas_image_cmptprec(jp2_image,components[component]);
      max_value=MaxValueGivenBits(component_depth);
      scale_to_quantum=MaxRGBDouble/max_value;
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Channel %d scale is %g", component, scale_to_quantum);
      channel_lut[component]=MagickAllocateResourceLimitedArray(Quantum *, (size_t) max_value+1,sizeof(Quantum));
      if (channel_lut[component] == (Quantum *) NULL)
        ThrowJP2ReaderException(ResourceLimitError,MemoryAllocationFailed,image);
      for(i=0; i <= max_value; i++)
        (channel_lut[component])[i]=scale_to_quantum*i+0.5;
    }

  /*
    Convert JPEG 2000 pixels.
  */
  for (y=0; y < (long) image->rows; y++)
    {
      q=GetImagePixels(image,0,y,image->columns,1);
      if (q == (PixelPacket *) NULL)
        break;

      if (1 == number_components)
        {
          /* Grayscale */
          (void) jas_image_readcmpt(jp2_image,(short) components[0],0,
                                    (unsigned int) y,
                                    (unsigned int) image->columns,1,pixels);
          for (x=0; x < (long) image->columns; x++)
            {
              q->red=q->green=q->blue=(channel_lut[0])[jas_matrix_getv(pixels,x)];
              q->opacity=OpaqueOpacity;
              q++;
            }
        }
      else
        {
          /* Red */
          (void) jas_image_readcmpt(jp2_image,(short) components[0],0,
                                    (unsigned int) y,
                                    (unsigned int) image->columns,1,pixels);
          for (x=0; x < (long) image->columns; x++)
            q[x].red=(channel_lut[0])[jas_matrix_getv(pixels,x)];

          /* Green */
          (void) jas_image_readcmpt(jp2_image,(short) components[1],0,
                                    (unsigned int) y,
                                    (unsigned int) image->columns,1,pixels);
          for (x=0; x < (long) image->columns; x++)
            q[x].green=(channel_lut[1])[jas_matrix_getv(pixels,x)];

          /* Blue */
          (void) jas_image_readcmpt(jp2_image,(short) components[2],0,
                                    (unsigned int) y,
                                    (unsigned int) image->columns,1,pixels);
          for (x=0; x < (long) image->columns; x++)
            q[x].blue=(channel_lut[2])[jas_matrix_getv(pixels,x)];

          /* Opacity */
          if (number_components > 3)
            {
              (void) jas_image_readcmpt(jp2_image,(short) components[3],0,
                                        (unsigned int) y,
                                        (unsigned int) image->columns,1,pixels);
              for (x=0; x < (long) image->columns; x++)
                q[x].opacity=MaxRGB-(channel_lut[3])[jas_matrix_getv(pixels,x)];
            }
          else
            {
              for (x=0; x < (long) image->columns; x++)
                q[x].opacity=OpaqueOpacity;
            }
        }
      if (!SyncImagePixels(image))
        break;
      if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,LoadImageText,
                                      image->filename,
                                      image->columns,image->rows))
            break;
    }
  if (number_components == 1)
    image->is_grayscale=MagickTrue;
  {
    /*
      Obtain ICC ICM color profile
    */

    jas_cmprof_t
      *cm_profile;

    /* Obtain a pointer to the existing jas_cmprof_t profile handle. */
    cm_profile=jas_image_cmprof(jp2_image);
    if (cm_profile != (jas_cmprof_t *) NULL)
      {
        jas_iccprof_t
          *icc_profile;

        /* Obtain a copy of the jas_iccprof_t ICC profile handle */
        icc_profile=jas_iccprof_createfromcmprof(cm_profile);
        /* or maybe just icc_profile=cm_profile->iccprof */
        if (icc_profile != (jas_iccprof_t *) NULL)
          {
            jas_stream_t
              *icc_stream;

            icc_stream=jas_stream_memopen(NULL,0);
            if ((icc_stream != (jas_stream_t *) NULL) &&
                (jas_iccprof_save(icc_profile,icc_stream) == 0) &&
                (jas_stream_flush(icc_stream) == 0))
              {
                jas_stream_memobj_t
                  *blob;

                blob=(jas_stream_memobj_t *) icc_stream->obj_;
                if (image->logging)
                  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                        "ICC profile: %lu bytes",(unsigned long) blob->len_);
                SetImageProfile(image,"ICM",blob->buf_,blob->len_);

                (void) jas_stream_close(icc_stream);
                jas_iccprof_destroy(icc_profile);
              }
          }
      }
  }

  for (component=0; component < (long) number_components; component++)
    MagickFreeResourceLimitedMemory(channel_lut[component]);
  jas_matrix_destroy(pixels);
  (void) jas_stream_close(jp2_stream);
  MagickFreeMemory(options);
  jas_image_destroy(jp2_image);
  StopTimer(&image->timer);
#if HAVE_JAS_INIT_LIBRARY
  /* Perform any per-thread clean-up for the JasPer library. */
  JAS_CLEANUP_THREAD();
#endif /* if HAVE_JAS_INIT_LIBRARY */
  return(image);
}
#endif /* if defined(HasJP2) */

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r J P 2 I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterJP2Image adds attributes for the JP2 image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterJP2Image method is:
%
%      RegisterJP2Image(void)
%
*/
ModuleExport void RegisterJP2Image(void)
{
#if defined(HasJP2)
  static char
    version[16];

  MagickInfo
    *entry;

  (void) strlcpy(version,"JasPer ",sizeof(version));
  (void) strlcat(version,jas_getversion(),sizeof(version));

#if !defined(EXCLUDE_JP2_SUPPORT) || defined(JAS_ENABLE_JP2_CODEC)
  entry=SetMagickInfo("J2C");
  entry->description="JPEG-2000 Code Stream Syntax";
  entry->version=version;
  entry->module="JP2";
  entry->magick=(MagickHandler) IsJPC;
  entry->adjoin=False;
  entry->seekable_stream=True;
  entry->thread_support=False;
  entry->decoder=(DecoderHandler) ReadJP2Image;
  entry->encoder=(EncoderHandler) WriteJP2Image;
  entry->coder_class=StableCoderClass;
  (void) RegisterMagickInfo(entry);
#endif /* !defined(EXCLUDE_JP2_SUPPORT) || defined(JAS_ENABLE_JP2_CODEC) */

#if !defined(EXCLUDE_JP2_SUPPORT) || defined(JAS_ENABLE_JP2_CODEC)
  entry=SetMagickInfo("JP2");
  entry->description="JPEG-2000 JP2 File Format Syntax";
  entry->version=version;
  entry->module="JP2";
  entry->magick=(MagickHandler) IsJP2;
  entry->adjoin=False;
  entry->seekable_stream=True;
  entry->thread_support=False;
  entry->decoder=(DecoderHandler) ReadJP2Image;
  entry->encoder=(EncoderHandler) WriteJP2Image;
  entry->coder_class=StableCoderClass;
  (void) RegisterMagickInfo(entry);
#endif /* !defined(EXCLUDE_JP2_SUPPORT) || defined(JAS_ENABLE_JP2_CODEC) */

#if !defined(EXCLUDE_JPC_SUPPORT) || defined(JAS_ENABLE_JPC_CODEC)
  entry=SetMagickInfo("JPC");
  entry->description="JPEG-2000 Code Stream Syntax";
  entry->version=version;
  entry->module="JP2";
  entry->magick=(MagickHandler) IsJPC;
  entry->adjoin=False;
  entry->seekable_stream=True;
  entry->thread_support=False;
  entry->decoder=(DecoderHandler) ReadJP2Image;
  entry->encoder=(EncoderHandler) WriteJP2Image;
  entry->coder_class=StableCoderClass;
  (void) RegisterMagickInfo(entry);
#endif /* !defined(EXCLUDE_JPC_SUPPORT) || defined(JAS_ENABLE_JPC_CODEC) */

#if !defined(EXCLUDE_PGX_SUPPORT) || defined(JAS_ENABLE_PGX_CODEC)
  entry=SetMagickInfo("PGX");
  entry->description="JPEG-2000 VM Format";
  entry->version=version;
  entry->module="JP2";
  entry->magick=(MagickHandler) IsPGX;
  entry->adjoin=False;
  entry->seekable_stream=True;
  entry->thread_support=False;
  entry->decoder=(DecoderHandler) ReadJP2Image;
  entry->encoder=(EncoderHandler) WriteJP2Image;
  entry->coder_class=UnstableCoderClass;
  (void) RegisterMagickInfo(entry);
#endif /* !defined(EXCLUDE_PGX_SUPPORT) || defined(JAS_ENABLE_PGX_CODEC) */

#endif /* if defined(HasJP2) */
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r J P 2 I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterJP2Image removes format registrations made by the
%  JP2 module from the list of supported formats.
%
%  The format of the UnregisterJP2Image method is:
%
%      UnregisterJP2Image(void)
%
*/
ModuleExport void UnregisterJP2Image(void)
{
#if defined(HasJP2)
  (void) UnregisterMagickInfo("PGX");
  (void) UnregisterMagickInfo("JPC");
  (void) UnregisterMagickInfo("JP2");
  (void) UnregisterMagickInfo("J2C");

  /*
    Cleanup Jasper
  */
  cleanup_jasper();
#endif /* if defined(HasJP2) */
}

#if defined(HasJP2)
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e J P 2 I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteJP2Image writes an image in the JPEG 2000 image format.
%
%  JP2 support originally written by Nathan Brown, nathanbrown@letu.edu
%
%  The format of the WriteJP2Image method is:
%
%      MagickPassFail WriteJP2Image(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteJP2Image return MagickTrue if the image is written.
%      MagickFalse is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/
static MagickPassFail
WriteJP2Image(const ImageInfo *image_info,Image *image)
{
  char
    magick[MaxTextExtent],
    option_keyval[MaxTextExtent],
    *options = NULL;

  int
    format;

  long
    y;

  jas_image_cmptparm_t
    component_info;

  jas_image_t
    *jp2_image;

  jas_matrix_t
    *jp2_pixels;

  jas_stream_ops_t
    StreamOperators =
    {
      BlobRead,
      BlobWrite,
      BlobSeek,
      BlobClose
    };

  jas_stream_t
    *jp2_stream;

  register const PixelPacket
    *p;

  register int
    x;

  MagickBool
    rate_specified=MagickFalse;

  MagickPassFail
    status;

  int
    component,
    number_components;

  unsigned short
    *lut;

  ImageCharacteristics
    characteristics;

  /*
    Initialize Jasper
  */
  if (initialize_jasper(&image->exception) != MagickPass)
    {
      return MagickFail;
    }

#if HAVE_JAS_INIT_LIBRARY
  /*
    Perform any per-thread initialization for the JasPer library.
  */
  if (jas_init_thread())
    {
      /* Handle the initialization error. */
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "jas_init_thread() failed!");
      return MagickFail;
    }
#endif /* if HAVE_JAS_INIT_LIBRARY */

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    ThrowJP2WriterException(FileOpenError,UnableToOpenFile,image);

  /*
    Ensure that image is in RGB space.
  */
  (void) TransformColorspace(image,RGBColorspace);

  /*
    PGX format requires a grayscale representation
  */
  if (strcmp("PGX",image_info->magick) == 0)
    (void) SetImageType(image,GrayscaleType);

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

  /*
    Support passing Jasper options.
  */
  {
    unsigned int
      i;

    for (i=0; i < ArraySize(jasper_enc_options); i++)
      {
        const char
          *option = jasper_enc_options[i];

        const char
          *value;

        if ((value=AccessDefinition(image_info,"jp2",option)) != NULL)
          {
            if (LocaleCompare(option,"rate") == 0)
              {
                /*
                  It is documented that a rate specification of 1.0 should
                  result in lossless compression.  However, Jasper only
                  provides lossless compression if rate was not specified
                  at all.  Support lossless compression as documented.
                */
                const double rate=atof(value);

                if (rate < 1.0-MagickEpsilon)
                  {
                    FormatString(option_keyval,"%s=%.1024s ",option,value);
                    ConcatenateString(&options,option_keyval);
                    rate_specified=MagickTrue;
                  }
              }
            else
              {
                FormatString(option_keyval,"%s=%.1024s ",option,value);
                ConcatenateString(&options,option_keyval);

                /* Setting debug mode seems to require extra assistance */
                if (LocaleCompare(option,"debug") == 0)
                  jas_setdbglevel(atoi(value));
              }
          }
      }
  }

  /*
    Obtain a JP2 stream.
  */
  jp2_stream=JP2StreamManager(&StreamOperators, image);
  if (jp2_stream == (jas_stream_t *) NULL)
    ThrowJP2WriterException(DelegateError,UnableToManageJP2Stream,image);
  number_components=image->matte ? 4 : 3;
  if ((image_info->type != TrueColorType) &&
      (characteristics.grayscale))
    number_components=1;

  jp2_image=jas_image_create0();
  if (jp2_image == (jas_image_t *) NULL)
    ThrowJP2WriterException(DelegateError,UnableToCreateImage,image);

  for (component=0; component < number_components; component++)
  {
    (void) memset((void *)&component_info,0,sizeof(jas_image_cmptparm_t));
    component_info.tlx=0; /* top left x ordinate */
    component_info.tly=0; /* top left y ordinate */
    component_info.hstep=1; /* horizontal pixels per step */
    component_info.vstep=1; /* vertical pixels per step */
    component_info.width=(unsigned int) image->columns;
    component_info.height=(unsigned int) image->rows;
    component_info.prec=(unsigned int) Max(2,Min(image->depth,16)); /* bits in range */
    component_info.sgnd = false;  /* range is signed value? */

    if (jas_image_addcmpt(jp2_image, component,&component_info)) {
      jas_image_destroy(jp2_image);
      ThrowJP2WriterException(DelegateError,UnableToCreateImageComponent,image);
    }
  }

  /*
    Allocate and compute LUT.
  */
  {
    unsigned long
      i,
      max_value;

    double
      scale_to_component;

    lut=MagickAllocateResourceLimitedArray(unsigned short *,MaxMap+1,sizeof(*lut));
    if (lut == (unsigned short *) NULL)
      {
        jas_image_destroy(jp2_image);
        ThrowJP2WriterException(ResourceLimitError,MemoryAllocationFailed,image);
      }

    max_value=MaxValueGivenBits(component_info.prec);
    scale_to_component=max_value/MaxRGBDouble;
    for(i=0; i <= MaxMap; i++)
        lut[i]=scale_to_component*i+0.5;
  }

  if (number_components == 1)
    {
      /* FIXME: If image has an attached ICC profile, then the profile
         should be transferred and the image colorspace set to
         JAS_CLRSPC_GENGRAY */
      /* sRGB Grayscale */
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Setting SGRAY colorspace");
      jas_image_setclrspc(jp2_image, JAS_CLRSPC_SGRAY);
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Setting GRAY channel to channel 0");
      jas_image_setcmpttype(jp2_image,0,
        JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_GRAY_Y));
    }
  else
    {
      /* FIXME: If image has an attached ICC profile, then the profile
         should be transferred and the image colorspace set to
         JAS_CLRSPC_GENRGB */

      /* sRGB */
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Setting SRGB colorspace");
      jas_image_setclrspc(jp2_image, JAS_CLRSPC_SRGB);
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Setting RED channel to channel 0");
      jas_image_setcmpttype(jp2_image,0,
        JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R));
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Setting GREEN channel to channel 1");
      jas_image_setcmpttype(jp2_image,1,
        JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G));
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Setting BLUE channel to channel 2");
      jas_image_setcmpttype(jp2_image,2,
        JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B));
      if (number_components == 4 )
        {
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
            "Setting OPACITY channel to channel 3");
          jas_image_setcmpttype(jp2_image,3,
            JAS_IMAGE_CT_COLOR(JAS_IMAGE_CT_OPACITY));
        }
    }
  /*
    Convert to JPEG 2000 pixels.
  */
  jp2_pixels=jas_matrix_create(1,(unsigned int) image->columns);
  if (jp2_pixels == (jas_matrix_t *) NULL)
    {
      MagickFreeResourceLimitedMemory(lut);
      jas_image_destroy(jp2_image);
      ThrowJP2WriterException(ResourceLimitError,MemoryAllocationFailed,image);
    }

  for (y=0; y < (long) image->rows; y++)
  {
    p=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
    if (p == (const PixelPacket *) NULL)
      break;
    if (number_components == 1)
      {
        for (x=0; x < (long) image->columns; x++)
          jas_matrix_setv(jp2_pixels,x,lut[ScaleQuantumToMap(PixelIntensityToQuantum(&p[x]))]);
        (void) jas_image_writecmpt(jp2_image,0,0,(unsigned int) y,
                                   (unsigned int) image->columns,1,jp2_pixels);
      }
    else
      {
        for (x=0; x < (long) image->columns; x++)
          jas_matrix_setv(jp2_pixels,x,lut[ScaleQuantumToMap(p[x].red)]);
        (void) jas_image_writecmpt(jp2_image,0,0,(unsigned int) y,
                                   (unsigned int) image->columns,1,jp2_pixels);

        for (x=0; x < (long) image->columns; x++)
          jas_matrix_setv(jp2_pixels,x,lut[ScaleQuantumToMap(p[x].green)]);
        (void) jas_image_writecmpt(jp2_image,1,0,(unsigned int) y,
                                   (unsigned int) image->columns,1,jp2_pixels);

        for (x=0; x < (long) image->columns; x++)
          jas_matrix_setv(jp2_pixels,x,lut[ScaleQuantumToMap(p[x].blue)]);
        (void) jas_image_writecmpt(jp2_image,2,0,(unsigned int) y,
                                   (unsigned int) image->columns,1,jp2_pixels);

        if (number_components > 3)
          for (x=0; x < (long) image->columns; x++)
            jas_matrix_setv(jp2_pixels,x,lut[ScaleQuantumToMap(MaxRGB-p[x].opacity)]);
        (void) jas_image_writecmpt(jp2_image,3,0,(unsigned int) y,
                                   (unsigned int) image->columns,1,jp2_pixels);
      }
    if (image->previous == (Image *) NULL)
      if (QuantumTick(y,image->rows))
        if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                    SaveImageText,image->filename,
                                    image->columns,image->rows))
          break;
  }
  (void) strlcpy(magick,image_info->magick,MaxTextExtent);
  /*
    J2C is an alias for JPC but Jasper only supports "JPC".
  */
  if (LocaleCompare(magick,"j2c") == 0)
    (void) strlcpy(magick,"jpc",sizeof(magick));
  LocaleLower(magick);
  format=jas_image_strtofmt(magick);

  /*
    Provide an emulation of IJG JPEG "quality" by default if rate was
    not specified.
  */
  if (rate_specified == MagickFalse)
    {
      double
        rate=INFINITY;

      /*
        A rough approximation to JPEG v1 quality using JPEG-2000.
        Default "quality" 75 results in a request for 16:1 compression, which
        results in image sizes approximating that of JPEG v1.
      */
      if ((image_info->quality < 100.0-MagickEpsilon) &&
          (MagickArraySize(image->rows,image->columns) > 2500U))
        {
          double
            header_size,
            current_size,
            target_size,
            d;

          d=115-image_info->quality;  /* Best number is 110-115 */
          rate=100.0/(d*d);
          header_size=550.0; /* Base file size. */
          header_size+=((size_t) number_components-1)*142; /* Additional components */
          /* FIXME: Need to account for any ICC profiles here */

          current_size=(double)((image->rows*image->columns*image->depth)/8)*
            number_components;
          target_size=(current_size*rate)+header_size;
          rate=target_size/current_size;
          FormatString(option_keyval,"%s=%g ","rate",rate);
          ConcatenateString(&options,option_keyval);
        }
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Compression rate: %g (%3.2f:1)",rate,1.0/rate);
    }


  if (options)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
       "Jasper options: \"%s\"", options);

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),"Encoding image");
  status=jas_image_encode(jp2_image,jp2_stream,format,options);
  (void) jas_stream_close(jp2_stream);
  MagickFreeMemory(options);
  MagickFreeResourceLimitedMemory(lut);
  jas_matrix_destroy(jp2_pixels);
  jas_image_destroy(jp2_image);
  if (status)
    ThrowJP2WriterException(DelegateError,UnableToEncodeImageFile,image);

#if HAVE_JAS_INIT_LIBRARY
  /* Perform any per-thread clean-up for the JasPer library. */
  JAS_CLEANUP_THREAD();
#endif /* if HAVE_JAS_INIT_LIBRARY */
  return(True);
}
#endif /* if defined(HasJP2) */
