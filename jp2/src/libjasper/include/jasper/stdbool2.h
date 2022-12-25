#ifndef __STDBOOL2_H__
#define __STDBOOL2_H__


#if defined(_MSC_VER) && _MSC_VER < 1500
 #ifndef __cplusplus
  #define bool int
 #endif
#else
 #include <stdbool.h>
#endif


#endif