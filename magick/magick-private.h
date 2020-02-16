/*
  Copyright (C) 2003 - 2020 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio
  Copyright 1991-1999 E. I. du Pont de Nemours and Company

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Application Programming Interface declarations.
*/

/*
  Get blocksize to use when accessing the filesystem.
*/
extern size_t
MagickGetFileSystemBlockSize(void) MAGICK_FUNC_PURE;

/*
  Set blocksize to use when accessing the filesystem.
*/
extern void
MagickSetFileSystemBlockSize(const size_t block_size);

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
