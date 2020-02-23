/*
  Copyright (C) 2003-2020 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio
  Copyright 1991-1999 E. I. du Pont de Nemours and Company

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagickMagick Exception Methods.
*/

extern MagickPassFail
  InitializeMagickExceptionHandling(void);

extern void
  DestroyMagickExceptionHandling(void);

#if !defined(MAGICK_FUNC_NORETURN)
#  define MAGICK_NORETURN_EXIT exit(1)
#else
#  define MAGICK_NORETURN_EXIT
#endif

#  if defined(MAGICK_IDBASED_MESSAGES)

#    define MagickMsg(severity_,msg_) GetLocaleMessageFromID(MGK_##severity_##msg_)

/* Severity ID translated. */
#    define ThrowException(exception_,severity_,reason_,description_) \
  (ThrowLoggedException(exception_,severity_,GetLocaleMessageFromID(\
    MGK_##severity_##reason_),description_,GetMagickModule()))

/* No IDs translated */
#    define ThrowException2(exception_,severity_,reason_,description_) \
  (ThrowLoggedException(exception_,severity_,reason_,description_,\
    GetMagickModule()))

/* Severity and description IDs translated */
#    define ThrowException3(exception_,severity_,reason_,description_) \
  (ThrowLoggedException(exception_,severity_,GetLocaleMessageFromID(\
    MGK_##severity_##reason_),GetLocaleMessageFromID(\
    MGK_##severity_##description_),GetMagickModule()))

#    define MagickError(severity_,reason_,description_) \
  (_MagickError(severity_,GetLocaleMessageFromID(MGK_##severity_##reason_),\
    description_))

#    define MagickFatalError(severity_,reason_,description_) \
  (_MagickFatalError(severity_,GetLocaleMessageFromID(\
    MGK_##severity_##reason_),description_));MAGICK_NORETURN_EXIT

#    define MagickWarning(severity_,reason_,description_) \
  (_MagickWarning(severity_,GetLocaleMessageFromID(MGK_##severity_##reason_),\
    description_))

#    define MagickError2(severity_,reason_,description_) \
  (_MagickError(severity_,reason_,description_))

#    define MagickFatalError2(severity_,reason_,description_) \
  (_MagickFatalError(severity_,reason_,description_));MAGICK_NORETURN_EXIT

#    define MagickWarning2(severity_,reason_,description_) \
  (_MagickWarning(severity_,reason_,description_))

#    define MagickError3(severity_,reason_,description_) \
  (_MagickError(severity_,GetLocaleMessageFromID(MGK_##severity_##reason_),\
    GetLocaleMessageFromID(MGK_##severity_##description_)))

#    define MagickFatalError3(severity_,reason_,description_) \
  (_MagickFatalError(severity_,GetLocaleMessageFromID(MGK_##severity_##reason_),\
    GetLocaleMessageFromID(MGK_##severity_##description_)));MAGICK_NORETURN_EXIT

#    define MagickWarning3(severity_,reason_,description_) \
  (_MagickWarning(severity_,GetLocaleMessageFromID(MGK_##severity_##reason_),\
    GetLocaleMessageFromID(MGK_##severity_##description_)))
/* end #if defined(MAGICK_IDBASED_MESSAGES) */
#  else

#    define MagickMsg(severity_,msg_) GetLocaleExceptionMessage(severity_,#msg_)

#    define ThrowException(exception_,severity_,reason_,description_) \
  (ThrowLoggedException(exception_,severity_,#reason_,description_,GetMagickModule()))

#    define ThrowException2(exception_,severity_,reason_,description_) \
  (ThrowLoggedException(exception_,severity_,reason_,description_,GetMagickModule()))

#    define ThrowException3(exception_,severity_,reason_,description_) \
  (ThrowLoggedException(exception_,severity_,#reason_,#description_,GetMagickModule()))

#    define MagickError(severity_,reason_,description_) \
  (_MagickError(severity_,#reason_,description_))

#    define MagickFatalError(severity_,reason_,description_) \
  (_MagickFatalError(severity_,#reason_,description_));MAGICK_NORETURN_EXIT

#    define MagickWarning(severity_,reason_,description_) \
  (_MagickWarning(severity_,#reason_,description_))

#    define MagickError2(severity_,reason_,description_) \
  (_MagickError(severity_,reason_,description_))

#    define MagickFatalError2(severity_,reason_,description_) \
  (_MagickFatalError(severity_,reason_,description_));MAGICK_NORETURN_EXIT

#    define MagickWarning2(severity_,reason_,description_) \
  (_MagickWarning(severity_,reason_,description_))

#    define MagickError3(severity_,reason_,description_) \
  (_MagickError(severity_,#reason_,#description_))

#    define MagickFatalError3(severity_,reason_,description_) \
  (_MagickFatalError(severity_,#reason_,#description_));MAGICK_NORETURN_EXIT

#    define MagickWarning3(severity_,reason_,description_) \
  (_MagickWarning(severity_,#reason_,#description_))

#  endif

#define ThrowBinaryException(severity_,reason_,description_) \
do { \
  if (image != (Image *) NULL) \
    { \
      ThrowException(&image->exception,severity_,reason_,description_); \
    } \
  return(MagickFail); \
} while (0);

#define ThrowBinaryException2(severity_,reason_,description_) \
do { \
  if (image != (Image *) NULL) \
    { \
      ThrowException2(&image->exception,severity_,reason_,description_); \
    } \
  return(MagickFail); \
} while (0);

#define ThrowBinaryException3(severity_,reason_,description_) \
do { \
  if (image != (Image *) NULL) \
    { \
      ThrowException3(&image->exception,severity_,reason_,description_); \
    } \
  return(MagickFail); \
} while (0);

#define ThrowImageException(code_,reason_,description_) \
do { \
  ThrowException(exception,code_,reason_,description_); \
  return((Image *) NULL); \
} while (0);

#define ThrowImageException2(code_,reason_,description_) \
do { \
  ThrowException2(exception,code_,reason_,description_); \
  return((Image *) NULL); \
} while (0);

#define ThrowImageException3(code_,reason_,description_) \
do { \
  ThrowException3(exception,code_,reason_,description_); \
  return((Image *) NULL); \
} while (0);

#define ThrowReaderException(code_,reason_,image_) \
do { \
  if (code_ > exception->severity) \
    { \
      ThrowException(exception,code_,reason_,image_ ? (image_)->filename : 0); \
    } \
  if (image_) \
    { \
       CloseBlob(image_); \
       DestroyImageList(image_); \
    } \
  return((Image *) NULL); \
} while (0);

#define ThrowWriterException(code_,reason_,image_) \
do { \
  assert(image_ != (Image *) NULL); \
  ThrowException(&(image_)->exception,code_,reason_,(image_)->filename); \
  if (image_info->adjoin) \
    while ((image_)->previous != (Image *) NULL) \
      (image_)=(image_)->previous; \
  CloseBlob(image_); \
  return(MagickFail); \
} while (0);

#define ThrowWriterException2(code_,reason_,image_) \
do { \
  assert(image_ != (Image *) NULL); \
  ThrowException2(&(image_)->exception,code_,reason_,(image_)->filename); \
  if (image_info->adjoin) \
    while ((image_)->previous != (Image *) NULL) \
      (image_)=(image_)->previous; \
  CloseBlob(image_); \
  return(MagickFail); \
} while (0);

#define ThrowWriterException3(code_,reason_,image_) \
do { \
  assert(image_ != (Image *) NULL); \
  ThrowException3(&(image_)->exception,code_,reason_,(image_)->filename); \
  if (image_info->adjoin) \
    while ((image_)->previous != (Image *) NULL) \
      (image_)=(image_)->previous; \
  CloseBlob(image_); \
  return(MagickFail); \
} while (0);

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
