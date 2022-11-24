/*
  Copyright (C) 2018 - 2022 GraphicsMagick Group

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Image Private declarations.
*/

/*
  Maximum unsigned RGB value which fits in the specified bits

  If bits <= 0, then zero is returned.  If bits exceeds bits in unsigned long,
  then max value of unsigned long is returned.

  Emulates ((1U << bits)-1) but without the overflow problems.
*/
#define MaxValueGivenBits(bits)                                         \
  ((unsigned long)                                                      \
   ((bits <= 0) ? 0 :                                                   \
    ((0x01UL << (Min(sizeof(unsigned long)*8U,(size_t)bits)-1)) +       \
     ((0x01UL << (Min(sizeof(unsigned long)*8U,(size_t)bits)-1))-1))))

/*
  ImageExtra allows for expansion of Image without increasing its
  size.  The internals are defined only in this private header file.
  Clients using the library can access the internals via the access
  functions provided by image.h.
*/
typedef struct _ImageExtra
{
  Image
    *clip_mask,       /* Private, clipping mask to apply when updating pixels */
    *composite_mask;  /* Private, compositing mask to apply when updating pixels */
} ImageExtra;

#define ImageGetClipMaskInlined(i) (&i->extra->clip_mask)

#define ImageGetCompositeMaskInlined(i) (&i->extra->composite_mask)

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
