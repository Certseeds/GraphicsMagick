/*
  Copyright (C) 2003-2020 GraphicsMagick Group

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Temporary File Management
*/

#ifndef _MAGICK_TEMPFILE_H
#define _MAGICK_TEMPFILE_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* defined(__cplusplus) || defined(c_plusplus) */

typedef enum
{
  BinaryFileIOMode,
  TextFileIOMode
} FileIOMode;

MagickExport MagickPassFail
  AcquireTemporaryFileName(char *filename),
  LiberateTemporaryFile(char *filename);

MagickExport int
  AcquireTemporaryFileDescriptor(char *filename);

MagickExport FILE *
  AcquireTemporaryFileStream(char *filename,FileIOMode mode);

#if defined(MAGICK_IMPLEMENTATION)
#  include "magick/tempfile-private.h"
#endif /* MAGICK_IMPLEMENTATION */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* defined(__cplusplus) || defined(c_plusplus) */

#endif /* _MAGICK_TEMPFILE_H */

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
