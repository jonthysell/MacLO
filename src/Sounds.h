// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file Sounds.h
 *
 * This file provides a Sounds type which contains handles to every
 * sound resource used by the game, as well as functions for playing them.
 */

#ifndef SOUNDS_H
#define SOUNDS_H

#include <Sound.h>

#include "MacCommon.h"

/** Struct containing handles to every sound resource. */
typedef struct sSounds
{
    bool          Enabled;
    Handle        ClickSnd;
    Handle        RetrySnd;
    Handle        DoneSnd;
} Sounds;

/**
 * Initializes the Sounds by loading each sound resource.
 * @param pSounds The Sounds.
 */
void Sounds_Init(Sounds *pSounds);

/**
 * Plays the "click" sound.
 * @param pSounds The Sounds.
 */
void Sounds_PlayClickSnd(const Sounds *pSounds);

/**
 * Plays the "retry" sound.
 * @param pSounds The Sounds.
 */
void Sounds_PlayRetrySnd(const Sounds *pSounds);

/**
 * Plays the "done" sound.
 * @param pSounds The Sounds.
 */
void Sounds_PlayDoneSnd(const Sounds *pSounds);

#endif
