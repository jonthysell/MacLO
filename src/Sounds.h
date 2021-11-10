// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef SOUNDS_H
#define SOUNDS_H

#include <Sound.h>

#include "MacCommon.h"

typedef struct sSounds
{
    bool          Enabled;
    SndChannelPtr SndChannel;
    Handle        ClickSnd;
    Handle        RetrySnd;
    Handle        DoneSnd;
} Sounds;

void Sounds_Init(Sounds *pSounds);

void Sounds_PlayClickSnd(const Sounds *pSounds);
void Sounds_PlayRetrySnd(const Sounds *pSounds);
void Sounds_PlayDoneSnd(const Sounds *pSounds);

#endif
