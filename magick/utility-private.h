/*
  Copyright (C) 2003 - 2020 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio
  Copyright 1991-1999 E. I. du Pont de Nemours and Company

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Utility Methods.
*/

/*
  Force argument into range accepted by <ctype.h> functions.
*/
#define CTYPE_ARG(value) ((int) ((unsigned char) (value)))

#if !defined(HAVE_STRLCAT)
#  define strlcat(dst,src,size) MagickStrlCat(dst,src,size)
#endif

#if !defined(HAVE_STRLCPY)
#  define strlcpy(dst,src,size) MagickStrlCpy(dst,src,size)
#endif

extern double MagickFmin(const double x, const double y) MAGICK_FUNC_CONST;
extern double MagickFmax(const double x, const double y) MAGICK_FUNC_CONST;

extern MagickExport MagickPassFail MagickAtoFChk(const char *str, double *value);
extern MagickExport MagickPassFail MagickAtoIChk(const char *str, int *value);
extern MagickExport MagickPassFail MagickAtoUIChk(const char *str, unsigned int *value);
extern MagickExport MagickPassFail MagickAtoLChk(const char *str, long *value);
extern MagickExport MagickPassFail MagickAtoULChk(const char *str, unsigned long *value);
extern MagickExport long MagickDoubleToLong(const double dval/*, ExceptionInfo *exception*/);

/*
  Compute a value which is the next kilobyte power of 2 larger than
  the requested value or MaxTextExtent, whichever is larger.

  The objective is to round up the size quickly (and in repeatable
  steps) in order to reduce the number of memory copies due to realloc
  for strings which grow rapidly, while producing a reasonable size
  for smaller strings.
*/
#define MagickRoundUpStringLength(size) \
{ \
  size_t \
    _rounded; \
 \
  for (_rounded=256U; _rounded < (Max(size,256)); _rounded *= 2); \
  size=_rounded; \
}

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
