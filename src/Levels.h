// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef LEVELS_H
#define LEVELS_H

#include "stdint.h"
#include "stdbool.h"

#define LevelCount 50

uint32_t Levels_GetLightsForLevel(const int8_t level, const bool setB);

uint16_t Levels_GetParForLevel(const int8_t level);

#endif
