#ifndef __STDBOOL2_H__
#define __STDBOOL2_H__


#if defined(_MSC_VER) && _MSC_VER <= 1600
 #ifndef __cplusplus
  #define bool int
  #define false 0
  #define true 1
 #endif
#else
 #include <stdbool.h>
#endif


#endif
