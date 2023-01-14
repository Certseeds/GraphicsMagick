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

#define BackgroundColor "#ffffffffffff"  /* white */
#define BackgroundColorInit(q) \
  do { SetRedSample(q,MaxRGB); \
    SetGreenSample(q,MaxRGB); \
    SetBlueSample(q,MaxRGB); \
    SetOpacitySample(q,0U); } while(0)

#define BorderColor "#dfdfdfdfdfdf"  /* gray */
#define BorderColorInit(q) \
  do { \
    SetGraySample(q,ScaleShortToQuantum(0xdfdf)); \
    SetOpacitySample(q,0); \
  } while(0)

#define ForegroundColor "#000000000000"  /* black */
#define ForegroundColorInit(q) \
  do { \
    SetGraySample(q,0); \
    SetOpacitySample(q,0); } \
  while(0)

#define HighlightColor "#f1f100001e1e" /* light red */
#define HighlightColorInit(q) \
  do { SetRedSample(q,ScaleShortToQuantum(0xf1f1)); \
    SetGreenSample(q,ScaleShortToQuantum(0x000)); \
    SetBlueSample(q,ScaleShortToQuantum(0x1e1e)); \
    SetOpacitySample(q,0); \
  } while(0)

#define MatteColor "#bdbdbdbdbdbd"  /* gray */
#define MatteColorInit(q) \
  do { \
    SetGraySample(q,ScaleShortToQuantum(0xbdbd)); \
    SetOpacitySample(q,0); \
  } while(0)

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
