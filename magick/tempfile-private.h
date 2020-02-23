/*
  Copyright (C) 2003-2020 GraphicsMagick Group

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Temporary File Management
*/

#define ThrowReaderTemporaryFileException(filename) \
{ \
  if ((image) == (Image *) NULL) \
    { \
    ThrowException(exception,FileOpenError,UnableToCreateTemporaryFile, \
      filename); \
    } \
  else \
    { \
      ThrowException(exception,FileOpenError,UnableToCreateTemporaryFile, \
        filename); \
      CloseBlob(image); \
      DestroyImageList(image); \
    } \
  return((Image *) NULL); \
}
#define ThrowWriterTemporaryFileException(filename) \
{ \
  assert(image != (Image *) NULL); \
  ThrowException(&(image)->exception,FileOpenError, \
    UnableToCreateTemporaryFile,filename); \
  if (image_info->adjoin) \
    while ((image)->previous != (Image *) NULL) \
      (image)=(image)->previous; \
  CloseBlob(image); \
  return(False); \
}

MagickExport void
  DestroyTemporaryFiles(void),
  PurgeTemporaryFiles(void),
  PurgeTemporaryFilesAsyncSafe(void);

extern MagickPassFail
  InitializeTemporaryFiles(void);

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
