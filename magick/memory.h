/*
  Copyright (C) 2003-2023 GraphicsMagick Group

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Memory Allocation Methods.
*/
#ifndef _MAGICK_MEMORY_H
#define _MAGICK_MEMORY_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef void *(*MagickMallocFunc)(size_t size);
typedef void (*MagickFreeFunc)(void *ptr);
typedef void *(*MagickReallocFunc)(void *ptr, size_t size);

extern MagickExport void
   MagickAllocFunctions(MagickFreeFunc free_func,MagickMallocFunc malloc_func,MagickReallocFunc realloc_func),
  *MagickCloneMemory(void *destination,const void *source,const size_t size) MAGICK_FUNC_NONNULL,
   MagickFree(void *memory),
   MagickFreeAligned(void *memory),
  *MagickMalloc(const size_t size) MAGICK_FUNC_MALLOC MAGICK_FUNC_ALLOC_SIZE_1ARG(1),
  *MagickMallocAligned(const size_t alignment, const size_t size) MAGICK_FUNC_MALLOC MAGICK_FUNC_ALLOC_SIZE_1ARG(2),
  *MagickMallocCleared(const size_t size) MAGICK_FUNC_MALLOC MAGICK_FUNC_ALLOC_SIZE_1ARG(1),
  *MagickRealloc(void *memory,const size_t size) MAGICK_FUNC_MALLOC MAGICK_FUNC_ALLOC_SIZE_1ARG(2),
  *MagickReallocStd(void *memory,const size_t size) MAGICK_FUNC_MALLOC MAGICK_FUNC_ALLOC_SIZE_1ARG(2);

#if defined(MAGICK_IMPLEMENTATION)
#include "magick/memory-private.h"
#endif /* defined(MAGICK_IMPLEMENTATION) */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
