// Copyright 2010 Google Inc. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the COPYING file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS. All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
// -----------------------------------------------------------------------------
//
//  Common types
//
// Author: Skal (pascal.massimino@gmail.com)

#ifndef WEBP_WEBP_TYPES_H_
#define WEBP_WEBP_TYPES_H_

#include <stddef.h>  // for size_t

#ifndef _MSC_VER
#include <inttypes.h>
#if defined(__cplusplus) || !defined(__STRICT_ANSI__) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#define WEBP_INLINE inline
#else
#define WEBP_INLINE
#endif
#else
#if _MSC_VER > 1600
  #include <stdint.h>
  #include <inttypes.h>
#else
 typedef signed   char int8_t;
 typedef unsigned char uint8_t;
 typedef signed   short int16_t;
 typedef unsigned short uint16_t;
 typedef signed   int int32_t;
 typedef unsigned int uint32_t;
 typedef unsigned long long int uint64_t;
 typedef long long int int64_t;

 typedef signed char        int_least8_t;
 typedef short              int_least16_t;
 typedef int                int_least32_t;
 typedef long long          int_least64_t;
 typedef unsigned char      uint_least8_t;
 typedef unsigned short     uint_least16_t;
 typedef unsigned int       uint_least32_t;
 typedef unsigned long long uint_least64_t;

 typedef signed char        int_fast8_t;
 typedef int                int_fast16_t;
 typedef int                int_fast32_t;
 typedef long long          int_fast64_t;
 typedef unsigned char      uint_fast8_t;
 typedef unsigned int       uint_fast16_t;
 typedef unsigned int       uint_fast32_t;
 typedef unsigned long long uint_fast64_t;
 

/* These macros must exactly match those in the Windows SDK's intsafe.h */
 #define INT8_MIN         (-127i8 - 1)
 #define INT16_MIN        (-32767i16 - 1)
 #define INT32_MIN        (-2147483647i32 - 1)
 #define INT64_MIN        (-9223372036854775807i64 - 1)
 #define INT8_MAX         127i8
 #define INT16_MAX        32767i16
 #define INT32_MAX        2147483647i32
 #define INT64_MAX        9223372036854775807i64
 #define UINT8_MAX        0xffui8
 #define UINT16_MAX       0xffffui16
 #define UINT32_MAX       0xffffffffui32
 #define UINT64_MAX       0xffffffffffffffffui64

 #define INT_LEAST8_MIN   INT8_MIN
 #define INT_LEAST16_MIN  INT16_MIN
 #define INT_LEAST32_MIN  INT32_MIN
 #define INT_LEAST64_MIN  INT64_MIN
 #define INT_LEAST8_MAX   INT8_MAX
 #define INT_LEAST16_MAX  INT16_MAX
 #define INT_LEAST32_MAX  INT32_MAX
 #define INT_LEAST64_MAX  INT64_MAX
 #define UINT_LEAST8_MAX  UINT8_MAX
 #define UINT_LEAST16_MAX UINT16_MAX
 #define UINT_LEAST32_MAX UINT32_MAX
 #define UINT_LEAST64_MAX UINT64_MAX

 #define INT_FAST8_MIN    INT8_MIN
 #define INT_FAST16_MIN   INT32_MIN
 #define INT_FAST32_MIN   INT32_MIN
 #define INT_FAST64_MIN   INT64_MIN
 #define INT_FAST8_MAX    INT8_MAX
 #define INT_FAST16_MAX   INT32_MAX
 #define INT_FAST32_MAX   INT32_MAX
 #define INT_FAST64_MAX   INT64_MAX
 #define UINT_FAST8_MAX   UINT8_MAX
 #define UINT_FAST16_MAX  UINT32_MAX
 #define UINT_FAST32_MAX  UINT32_MAX
 #define UINT_FAST64_MAX  UINT64_MAX

#ifdef _WIN64
 #define INTPTR_MIN      INT64_MIN
 #define INTPTR_MAX      INT64_MAX
 #define UINTPTR_MAX     UINT64_MAX
#else /* _WIN64 */
 #define INTPTR_MIN      INT32_MIN
 #define INTPTR_MAX      INT32_MAX
 #define UINTPTR_MAX     UINT32_MAX
#endif /* _WIN64 */

#define INTMAX_MIN       INT64_MIN
#define INTMAX_MAX       INT64_MAX
#define UINTMAX_MAX      UINT64_MAX

#define PTRDIFF_MIN      INTPTR_MIN
#define PTRDIFF_MAX      INTPTR_MAX

#ifndef SIZE_MAX
 #define SIZE_MAX        UINTPTR_MAX
#endif /* SIZE_MAX */

#define SIG_ATOMIC_MIN   INT32_MIN
#define SIG_ATOMIC_MAX   INT32_MAX

#define WCHAR_MIN        0x0000
#define WCHAR_MAX        0xffff

#define WINT_MIN         0x0000
#define WINT_MAX         0xffff

#define _PFX_8   "hh"
#define _PFX_16  "h"
#define _PFX_32  "l"
#define _PFX_64  "ll"

#ifdef _WIN64
#define _PFX_PTR  "ll"
#else
#define _PFX_PTR  "l"
#endif

#ifdef _FAST16_IS_32 /* compiler test */
#define _PFX_F16  _PFX_32
#else /* _FAST16_IS_32 */
#define _PFX_F16  _PFX_16
#endif /* _FAST16_IS_32 */


/* PRINT FORMAT MACROS */
#define PRId8        _PFX_8 "d"
#define PRId16       _PFX_16 "d"
#define PRId32       _PFX_32 "d"
#define PRIdLEAST8   _PFX_8 "d"
#define PRIdLEAST16  _PFX_16 "d"
#define PRIdLEAST32  _PFX_32 "d"
#define PRIdFAST8    _PFX_8 "d"
#define PRIdFAST16   _PFX_F16 "d"
#define PRIdFAST32   _PFX_32 "d"

#define PRIi8        _PFX_8 "i"
#define PRIi16       _PFX_16 "i"
#define PRIi32       _PFX_32 "i"
#define PRIiLEAST8   _PFX_8 "i"
#define PRIiLEAST16  _PFX_16 "i"
#define PRIiLEAST32  _PFX_32 "i"
#define PRIiFAST8    _PFX_8 "i"
#define PRIiFAST16   _PFX_F16 "i"
#define PRIiFAST32   _PFX_32 "i"

#define PRIo8        _PFX_8 "o"
#define PRIo16       _PFX_16 "o"
#define PRIo32       _PFX_32 "o"
#define PRIoLEAST8   _PFX_8 "o"
#define PRIoLEAST16  _PFX_16 "o"
#define PRIoLEAST32  _PFX_32 "o"
#define PRIoFAST8    _PFX_8 "o"
#define PRIoFAST16   _PFX_F16 "o"
#define PRIoFAST32   _PFX_32 "o"

#define PRIu8        _PFX_8 "u"
#define PRIu16       _PFX_16 "u"
#define PRIu32       _PFX_32 "u"
#define PRIuLEAST8   _PFX_8 "u"
#define PRIuLEAST16  _PFX_16 "u"
#define PRIuLEAST32  _PFX_32 "u"
#define PRIuFAST8    _PFX_8 "u"
#define PRIuFAST16   _PFX_F16 "u"
#define PRIuFAST32   _PFX_32 "u"

#define PRIx8        _PFX_8 "x"
#define PRIx16       _PFX_16 "x"
#define PRIx32       _PFX_32 "x"
#define PRIxLEAST8   _PFX_8 "x"
#define PRIxLEAST16  _PFX_16 "x"
#define PRIxLEAST32  _PFX_32 "x"
#define PRIxFAST8    _PFX_8 "x"
#define PRIxFAST16   _PFX_F16 "x"
#define PRIxFAST32   _PFX_32 "x"

#define PRIX8        _PFX_8 "X"
#define PRIX16       _PFX_16 "X"
#define PRIX32       _PFX_32 "X"
#define PRIXLEAST8   _PFX_8 "X"
#define PRIXLEAST16  _PFX_16 "X"
#define PRIXLEAST32  _PFX_32 "X"
#define PRIXFAST8    _PFX_8 "X"
#define PRIXFAST16   _PFX_F16 "X"
#define PRIXFAST32   _PFX_32 "X"

#define PRId64       _PFX_64 "d"
#define PRIdLEAST64  _PFX_64 "d"
#define PRIdFAST64   _PFX_64 "d"
#define PRIdMAX      _PFX_64 "d"
#define PRIdPTR      _PFX_PTR "d"

#define PRIi64       _PFX_64 "i"
#define PRIiLEAST64  _PFX_64 "i"
#define PRIiFAST64   _PFX_64 "i"
#define PRIiMAX      _PFX_64 "i"
#define PRIiPTR      _PFX_PTR "i"

#define PRIo64       _PFX_64 "o"
#define PRIoLEAST64  _PFX_64 "o"
#define PRIoFAST64   _PFX_64 "o"
#define PRIoMAX      _PFX_64 "o"
#define PRIoPTR      _PFX_PTR "o"

#define PRIu64       _PFX_64 "u"
#define PRIuLEAST64  _PFX_64 "u"
#define PRIuFAST64   _PFX_64 "u"
#define PRIuMAX      _PFX_64 "u"
#define PRIuPTR      _PFX_PTR "u"

#define PRIx64       _PFX_64 "x"
#define PRIxLEAST64  _PFX_64 "x"
#define PRIxFAST64   _PFX_64 "x"
#define PRIxMAX      _PFX_64 "x"
#define PRIxPTR      _PFX_PTR "x"

#define PRIX64       _PFX_64 "X"
#define PRIXLEAST64  _PFX_64 "X"
#define PRIXFAST64   _PFX_64 "X"
#define PRIXMAX      _PFX_64 "X"
#define PRIXPTR      _PFX_PTR "X"


/* SCAN FORMAT MACROS */
#define SCNd8        _PFX_8 "d"
#define SCNd16       _PFX_16 "d"
#define SCNd32       _PFX_32 "d"
#define SCNdLEAST8   _PFX_8 "d"
#define SCNdLEAST16  _PFX_16 "d"
#define SCNdLEAST32  _PFX_32 "d"
#define SCNdFAST8    _PFX_8 "d"
#define SCNdFAST16   _PFX_F16 "d"
#define SCNdFAST32   _PFX_32 "d"

#define SCNi8        _PFX_8 "i"
#define SCNi16       _PFX_16 "i"
#define SCNi32       _PFX_32 "i"
#define SCNiLEAST8   _PFX_8 "i"
#define SCNiLEAST16  _PFX_16 "i"
#define SCNiLEAST32  _PFX_32 "i"
#define SCNiFAST8    _PFX_8 "i"
#define SCNiFAST16   _PFX_F16 "i"
#define SCNiFAST32   _PFX_32 "i"

#define SCNo8        _PFX_8 "o"
#define SCNo16       _PFX_16 "o"
#define SCNo32       _PFX_32 "o"
#define SCNoLEAST8   _PFX_8 "o"
#define SCNoLEAST16  _PFX_16 "o"
#define SCNoLEAST32  _PFX_32 "o"
#define SCNoFAST8    _PFX_8 "o"
#define SCNoFAST16   _PFX_F16 "o"
#define SCNoFAST32   _PFX_32 "o"

#define SCNu8        _PFX_8 "u"
#define SCNu16       _PFX_16 "u"
#define SCNu32       _PFX_32 "u"
#define SCNuLEAST8   _PFX_8 "u"
#define SCNuLEAST16  _PFX_16 "u"
#define SCNuLEAST32  _PFX_32 "u"
#define SCNuFAST8    _PFX_8 "u"
#define SCNuFAST16   _PFX_F16 "u"
#define SCNuFAST32   _PFX_32 "u"

#define SCNx8        _PFX_8 "x"
#define SCNx16       _PFX_16 "x"
#define SCNx32       _PFX_32 "x"
#define SCNxLEAST8   _PFX_8 "x"
#define SCNxLEAST16  _PFX_16 "x"
#define SCNxLEAST32  _PFX_32 "x"
#define SCNxFAST8    _PFX_8 "x"
#define SCNxFAST16   _PFX_F16 "x"
#define SCNxFAST32   _PFX_32 "x"

#define SCNd64       _PFX_64 "d"
#define SCNdLEAST64  _PFX_64 "d"
#define SCNdFAST64   _PFX_64 "d"
#define SCNdMAX      _PFX_64 "d"
#define SCNdPTR      _PFX_PTR "d"

#define SCNi64       _PFX_64 "i"
#define SCNiLEAST64  _PFX_64 "i"
#define SCNiFAST64   _PFX_64 "i"
#define SCNiMAX      _PFX_64 "i"
#define SCNiPTR      _PFX_PTR "i"

#define SCNo64       _PFX_64 "o"
#define SCNoLEAST64  _PFX_64 "o"
#define SCNoFAST64   _PFX_64 "o"
#define SCNoMAX      _PFX_64 "o"
#define SCNoPTR      _PFX_PTR "o"

#define SCNu64       _PFX_64 "u"
#define SCNuLEAST64  _PFX_64 "u"
#define SCNuFAST64   _PFX_64 "u"
#define SCNuMAX      _PFX_64 "u"
#define SCNuPTR      _PFX_PTR "u"

#define SCNx64       _PFX_64 "x"
#define SCNxLEAST64  _PFX_64 "x"
#define SCNxFAST64   _PFX_64 "x"
#define SCNxMAX      _PFX_64 "x"
#define SCNxPTR      _PFX_PTR "x"

#endif
#define WEBP_INLINE __forceinline
#endif  /* _MSC_VER */

/* This part added for GraphicsMagick */
#if defined(_MT) && defined(_DLL) && !defined(_WEBPDLL_) && !defined(_LIB)
#   define _WEBPDLL_
#endif
#if defined(_WEBPDLL_)
#   if defined(_VISUALC_)
#       pragma warning( disable : 4273 )
#   endif
#   if !defined(_WEBPLIB_)
#       define WEBP_EXTERN extern __declspec(dllimport)
#       pragma message( "libwebp compiling as DLL import" )
#   else
#       define WEBP_EXTERN extern __declspec(dllexport)
#       pragma message( "libwebp compiling as DLL export" )
#   endif
#endif
/* End of GraphicsMagick part. */

#ifndef WEBP_EXTERN
// This explicitly marks library functions and allows for changing the
// signature for e.g., Windows DLL builds.
# if defined(__GNUC__) && __GNUC__ >= 4
#  define WEBP_EXTERN extern __attribute__ ((visibility ("default")))
# else
#  define WEBP_EXTERN extern
# endif  /* __GNUC__ >= 4 */
#endif  /* WEBP_EXTERN */

// Macro to check ABI compatibility (same major revision number)
#define WEBP_ABI_IS_INCOMPATIBLE(a, b) (((a) >> 8) != ((b) >> 8))

#endif  // WEBP_WEBP_TYPES_H_
