// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file Levels.h
 *
 * This file provides functions for loading the light puzzles, or levels,
 * as well as the "par" for each level. Each light puzzle is stored as 25
 * bits within a 32-bit integer.
 */

#ifndef LEVELS_H
#define LEVELS_H

#include "stdint.h"
#include "stdbool.h"

/** The number of levels in each set. */
#define LevelCount 50

/** The number of sets. */
#define SetCount   2

/**
 * Gets the lights for a given set and level number.
 * @param level The level number.
 * @param setB Whether or not to load from Set B.
 * @return The lights.
 */
uint32_t Levels_GetLightsForLevel(const int8_t level, const bool setB);

/**
 * Gets the minimum number of toggles to solve a given level number.
 * @param level The level number.
 * @return The minimum number of toggles to complete the level.
 */
uint16_t Levels_GetParForLevel(const int8_t level);

#endif
