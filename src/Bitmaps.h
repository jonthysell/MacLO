// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef BITMAPS_H
#define BITMAPS_H

#include "MacCommon.h"

#define NumCharPictCount 10
#define StarPictCount    3

typedef struct sBitmaps
{
    PicHandle TitlePict;
    PicHandle NumCharPicts[NumCharPictCount];
    PicHandle ACharPict;
    PicHandle BCharPict;
    PicHandle SlashCharPict;
    PicHandle StarPicts[StarPictCount];
    PicHandle NextButtonPict;
    PicHandle RetryButtonPict;
    PicHandle SoundOffPict;
    PicHandle SoundOnPict;
    PicHandle LightOffPict;
    PicHandle LightOnPict;
} Bitmaps;

void Bitmaps_Init(Bitmaps *pBitmaps);

void Bitmaps_GetNumberRect(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale, Rect *pDestRect);
void Bitmaps_DrawNumber(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale);

void Bitmaps_DrawAChar(const Bitmaps *pBitmaps, const uint8_t scale);
void Bitmaps_DrawBChar(const Bitmaps *pBitmaps, const uint8_t scale);
void Bitmaps_DrawSlashChar(const Bitmaps *pBitmaps, const uint8_t scale);

void Bitmaps_GetHalfStarsRect(const Bitmaps *pBitmaps, const uint8_t halfStars, const uint8_t maxStars, const uint8_t scale, Rect *pDestRect);
void Bitmaps_DrawHalfStars(const Bitmaps *pBitmaps, const uint8_t halfStars, const uint8_t maxStars, const uint8_t scale);

void Bitmaps_GetSoundRect(const Bitmaps *pBitmaps, const bool enabled, const uint8_t scale, Rect *pDestRect);
void Bitmaps_DrawSound(const Bitmaps *pBitmaps, const bool enabled, const uint8_t scale);

#endif
