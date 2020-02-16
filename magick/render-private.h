/*
  Copyright (C) 2003 - 2020 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  Drawing methods.
*/

typedef struct _ElementInfo
{
  double
    cx,
    cy,
    major,
    minor,
    angle;
} ElementInfo;

typedef struct _PrimitiveInfo
{
  PointInfo
    point;

  size_t
    coordinates;

  PrimitiveType
    primitive;

  PaintMethod
    method;

  char
    *text;

  /*
    "flags" indicates:

       bit 0:  shape/subpath is closed (e.g., rectangle, path with 'z' or 'Z')

    Macro arg "pi" is a PrimitiveInfo *.
    Macro arg "zero_or_one" should be 0 (turn off) or 1 (turn on).
  */
  unsigned long
    flags;
#define PRIMINF_CLEAR_FLAGS(pi) ((pi)->flags=0)
#define PRIMINF_GET_IS_CLOSED_SUBPATH(pi) ((MagickBool)((pi)->flags&1U))
#define PRIMINF_SET_IS_CLOSED_SUBPATH(pi,zero_or_one) ((pi)->flags=((pi)->flags&(~1U))|(unsigned long)zero_or_one)
} PrimitiveInfo;

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
