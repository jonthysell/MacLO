// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef BITMAPS_H
#define BITMAPS_H

#include "MacCommon.h"

#define NumChars 10

typedef struct sBitmaps
{
    PicHandle TitlePict;
    PicHandle NumCharPicts[NumChars];
    PicHandle ACharPict;
    PicHandle BCharPict;
    PicHandle SlashCharPict;
} Bitmaps;

void Bitmaps_Init(Bitmaps *pBitmaps);

void Bitmaps_GetNumberRect(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale, Rect *pDestRect);
void Bitmaps_DrawNumber(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale);

void Bitmaps_DrawAChar(const Bitmaps *pBitmaps, const uint8_t scale);
void Bitmaps_DrawBChar(const Bitmaps *pBitmaps, const uint8_t scale);
void Bitmaps_DrawSlashChar(const Bitmaps *pBitmaps, const uint8_t scale);

#endif
