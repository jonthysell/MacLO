// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file stdint.h
 *
 * This file backports the fixed-width integer types from C99 to C89.
 */

#ifndef STDINT_H
#define STDINT_H

#include <limits.h>

#if !defined(UINT8_MAX) && defined(UCHAR_MAX) && (UCHAR_MAX) == 0xFFU

/** Unsigned integer type with width of exactly 8 bits. */
typedef unsigned char uint8_t;

/** Signed integer type with width of exactly 8 bits. */
typedef signed char int8_t;

/** The max value of an uint8_t. */
#define UINT8_MAX UCHAR_MAX

/** The max value of an int8_t. */
#define INT8_MAX CHAR_MAX

/** The min value of an int8_t. */
#define INT8_MIN CHAR_MIN

#endif

#if !defined(UINT16_MAX) && defined(USHRT_MAX) && (USHRT_MAX) == 0xFFFFU

/** Unsigned integer type with width of exactly 16 bits. */
typedef unsigned short uint16_t;

/** Signed integer type with width of exactly 16 bits. */
typedef signed short int16_t;

/** The max value of an uint16_t. */
#define UINT16_MAX USHRT_MAX

/** The max value of an int16_t. */
#define INT16_MAX SHRT_MAX

/** The min value of an int16_t. */
#define INT16_MIN SHRT_MIN

#endif

#if !defined(UINT32_MAX) && defined(ULONG_MAX) && (ULONG_MAX) == 0xFFFFFFFFUL

/** Unsigned integer type with width of exactly 32 bits. */
typedef unsigned long uint32_t;

/** Signed integer type with width of exactly 32 bits. */
typedef signed long int32_t;

/** The max value of an uint32_t. */
#define UINT32_MAX ULONG_MAX

/** The max value of an int32_t. */
#define INT32_MAX LONG_MAX

/** The min value of an int32_t. */
#define INT32_MIN LONG_MIN

#endif

#endif
