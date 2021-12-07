// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file Bitmaps.h
 *
 * This file provides a Bitmaps type which contains handles to every
 * picture resource used by the game, as well as functions for loading
 * and drawing those pictures.
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#include "MacCommon.h"

/** The number of numeric digit pictures. */
#define NumCharPictCount 10

/** The number of star pictures. */
#define StarPictCount    3

/** Struct containing handles to every picture resource. */
typedef struct sBitmaps
{
    PicHandle TitlePict;
    PicHandle NumCharPicts[NumCharPictCount];
    PicHandle ACharPict;
    PicHandle BCharPict;
    PicHandle SlashCharPict;
    PicHandle StarPicts[StarPictCount];
    PicHandle PrevButtonPict;
    PicHandle NextButtonPict;
    PicHandle RetryButtonPict;
    PicHandle SoundOffPict;
    PicHandle SoundOnPict;
    PicHandle LightOffPict;
    PicHandle LightOnPict;
} Bitmaps;

/**
 * Initializes the Bitmaps by loading each picture resource.
 * @param pBitmaps The Bitmaps.
 */
void Bitmaps_Init(Bitmaps *pBitmaps);

/**
 * Gets the rect bounding a number drawn using the (scaled) pictures.
 * @param pBitmaps The Bitmaps.
 * @param number The target number.
 * @param scale The scale factor.
 * @param pDestRect The Rect bounding the scaled picture.
 */
void Bitmaps_GetNumberRect(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale, Rect *pDestRect);

/**
 * Draws a number using the (scaled) pictures at the pen's location.
 * @param pBitmaps The Bitmaps.
 * @param number The target number.
 * @param scale The scale factor.
 */
void Bitmaps_DrawNumber(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale);

/**
 * Draws an "A" using the (scaled) picture at the pen's location.
 * @param pBitmaps The Bitmaps.
 * @param scale The scale factor.
 */
void Bitmaps_DrawAChar(const Bitmaps *pBitmaps, const uint8_t scale);

/**
 * Draws a "B" using the (scaled) picture at the pen's location.
 * @param pBitmaps The Bitmaps.
 * @param scale The scale factor.
 */
void Bitmaps_DrawBChar(const Bitmaps *pBitmaps, const uint8_t scale);

/**
 * Draws an "/" using the (scaled) picture at the pen's location.
 * @param pBitmaps The Bitmaps.
 * @param scale The scale factor.
 */
void Bitmaps_DrawSlashChar(const Bitmaps *pBitmaps, const uint8_t scale);

/**
 * Gets the rect bounding stars drawn using the (scaled) pictures.
 * @param pBitmaps The Bitmaps.
 * @param maxStars The number of stars.
 * @param scale The scale factor.
 * @param pDestRect The Rect bounding the scaled picture.
 */
void Bitmaps_GetHalfStarsRect(const Bitmaps *pBitmaps, const uint8_t maxStars, const uint8_t scale, Rect *pDestRect);

/**
 * Draws (partially) filled stars using the (scaled) pictures.
 * @param pBitmaps The Bitmaps.
 * @param halfStars The number of half-stars to fill.
 * @param maxStars The total number of stars.
 * @param scale The scale factor.
 */
void Bitmaps_DrawHalfStars(const Bitmaps *pBitmaps, const uint8_t halfStars, const uint8_t maxStars, const uint8_t scale);

/**
 * Gets the rect bounding the sound icon using the (scaled) pictures.
 * @param pBitmaps The Bitmaps.
 * @param scale The scale factor.
 * @param pDestRect The Rect bounding the scaled picture.
 */
void Bitmaps_GetSoundRect(const Bitmaps *pBitmaps, const uint8_t scale, Rect *pDestRect);

/**
 * Draws the sound icon using the (scaled) pictures.
 * @param pBitmaps The Bitmaps.
 * @param enabled Whether sound is enabled or not.
 * @param scale The scale factor.
 */
void Bitmaps_DrawSound(const Bitmaps *pBitmaps, const bool enabled, const uint8_t scale);

#endif
