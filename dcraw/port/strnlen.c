
#include <stdio.h>


/** Implementation of posix' strnlen for systems where it's not available.
 *
 * Returns the number of characters before a null-byte in the string pointed
 * to by str, unless there's no null-byte before maxlen. In the latter case
 * maxlen is returned. */
unsigned strnlen(const char *s, unsigned maxlen)
{
  register const char *e;
  unsigned n;

  for(e=s, n=0; *e && n<maxlen; e++, n++)
    ;
  return n;
}
