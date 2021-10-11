// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef STDINT_H
#define STDINT_H

#include <limits.h>

#if !defined(UINT8_MAX) && defined(UCHAR_MAX) && (UCHAR_MAX) == 0xFFU
typedef unsigned char uint8_t;
typedef signed char int8_t;
#define UINT8_MAX UCHAR_MAX
#define INT8_MAX CHAR_MAX
#define INT8_MIN CHAR_MIN
#endif

#if !defined(UINT16_MAX) && defined(USHRT_MAX) && (USHRT_MAX) == 0xFFFFU
typedef unsigned short uint16_t;
typedef signed short int16_t;
#define UINT16_MAX USHRT_MAX
#define INT16_MAX SHRT_MAX
#define INT16_MIN SHRT_MIN
#endif

#if !defined(UINT32_MAX) && defined(UINT_MAX) && (UINT_MAX) == 0xFFFFFFFFUL
typedef unsigned int uint32_t;
typedef signed int int32_t;
#define UINT32_MAX UINT_MAX
#define INT32_MAX INT_MAX
#define INT32_MIN INT_MIN
#endif

#if !defined(UINT32_MAX) && defined(ULONG_MAX) && (ULONG_MAX) == 0xFFFFFFFFUL
typedef unsigned long uint32_t;
typedef signed long int32_t;
#define UINT32_MAX ULONG_MAX
#define INT32_MAX LONG_MAX
#define INT32_MIN LONG_MIN
#endif

#endif