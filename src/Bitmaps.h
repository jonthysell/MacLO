// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef BITMAPS_H
#define BITMAPS_H

#include "MacCommon.h"

typedef struct sBitmaps
{
    PicHandle TitlePict;
    PicHandle NumCharPicts[10];
    PicHandle ACharPict;
    PicHandle BCharPict;
    PicHandle SlashCharPict;
} Bitmaps;

void Bitmaps_Init(Bitmaps *pBitmaps);

#endif
