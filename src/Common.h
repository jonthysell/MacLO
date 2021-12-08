// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file Common.h
 *
 * This file includes some common utility functions and macros.
 */

#ifndef COMMON_H
#define COMMON_H

#include "stdbool.h"
#include "stdint.h"

/** Get the minimum of a and b. */
#define min(a,b) ((a)<(b)?(a):(b))

/** Get the maximum of a and b. */
#define max(a,b) ((a)>(b)?(a):(b))

/** Gets the bit within value. */
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

/** Sets the bit within value. */
#define bitSet(value, bit) ((value) |= (1UL << (bit)))

/** Clears the bit within value. */
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))

/** Toggles the bit within value. */
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))

/** Sets the bit within value to bitValue. */
#define bitWrite(value, bit, bitValue) ((bitValue) ? bitSet(value, bit) : bitClear(value, bit))

#endif
