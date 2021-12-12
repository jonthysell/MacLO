// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file Sounds.c
 *
 * This file provides implementations for Sounds.h.
 */

#include "Sounds.h"

/** The first snd resource ID. */
#define SndBaseResID  8192

/** The click snd resource ID. */
#define ClickSndResID SndBaseResID

/** The retry snd resource ID. */
#define RetrySndResID (ClickSndResID + 1)

/** The done snd resource ID. */
#define DoneSndResID  (RetrySndResID + 1)

/** Whether or not sound is enabled by default. */
#define DefaultEnabled  true

/** Whether or not to play sound async. */
#define PlaySoundsAsync false

void Sounds_Init(Sounds *pSounds)
{
    pSounds->Enabled = DefaultEnabled;
    
    pSounds->ClickSnd = Get1Resource('snd ', ClickSndResID);
    if (pSounds->ClickSnd == nil)
    {
        ShowError("\pClick snd resource missing!", true);
    }
    
    pSounds->RetrySnd = Get1Resource('snd ', RetrySndResID);
    if (pSounds->RetrySnd == nil)
    {
        ShowError("\pRetry snd resource missing!", true);
    }
    
    pSounds->DoneSnd = Get1Resource('snd ', DoneSndResID);
    if (pSounds->DoneSnd == nil)
    {
        ShowError("\pDone snd resource missing!", true);
    }
}

void Sounds_PlayClickSnd(const Sounds *pSounds)
{
    if (pSounds->Enabled)
    {
        HLock(pSounds->ClickSnd);
        SndPlay(nil, pSounds->ClickSnd, PlaySoundsAsync);
        HUnlock(pSounds->ClickSnd);
    }
}

void Sounds_PlayRetrySnd(const Sounds *pSounds)
{
    if (pSounds->Enabled)
    {
        HLock(pSounds->RetrySnd);
        SndPlay(nil, pSounds->RetrySnd, PlaySoundsAsync);
        HUnlock(pSounds->RetrySnd);
    }
}

void Sounds_PlayDoneSnd(const Sounds *pSounds)
{
    if (pSounds->Enabled)
    {
        HLock(pSounds->DoneSnd);
        SndPlay(nil, pSounds->DoneSnd, PlaySoundsAsync);
        HUnlock(pSounds->DoneSnd);
    }
}
