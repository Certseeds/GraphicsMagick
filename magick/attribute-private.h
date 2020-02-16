/*
  Copyright (C) 2003-2020 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  Private Methods to Get/Set/Destroy Image Text Attributes.
*/

/* Assign value of attribute to double if attribute exists for key */
#define MagickAttributeToDouble(image,key,variable) \
{ \
    const ImageAttribute \
      *attribute; \
\
  if ((attribute=GetImageAttribute(image,key))) \
  { \
    variable=strtod(attribute->value,(char **) NULL); \
  } \
}

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
