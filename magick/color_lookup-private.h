/*
  Copyright (C) 2003 - 2020 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Private Color Lookup Methods.
*/

/*
  Information about a named color (Internal).
*/
typedef struct _ColorInfo
{
  char
    *path,
    *name;

  ComplianceType
    compliance;

  PixelPacket
    color;

  unsigned int
    stealth;

  unsigned long
    signature;

  struct _ColorInfo
    *previous,
    *next;
} ColorInfo;

extern const ColorInfo
  *GetColorInfo(const char *name, ExceptionInfo *exception);

extern ColorInfo
  **GetColorInfoArray(ExceptionInfo *exception);

extern void
  DestroyColorInfo(void);

extern unsigned int
  ListColorInfo(FILE *file,ExceptionInfo *exception);

extern MagickPassFail
  InitializeColorInfo(void);

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
