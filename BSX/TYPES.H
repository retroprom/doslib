#ifndef BSX_TYPES_H
#define BSX_TYPES_H

#include <sys/types.h>
#include <bsx/bool.h>

typedef unsigned char  byte_t;
typedef unsigned int   word_t;
typedef unsigned long  dword_t;

typedef signed char   int8_t;
typedef signed int    int16_t;
typedef signed long   int32_t;

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;

typedef unsigned int  seg_t;
#define SEG_FP(seg) ((char far *)MK_FP(seg,0))

#endif
