// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Sounds.h"

#define SndBaseResId  8192

#define ClickSndResID SndBaseResId
#define RetrySndResID (ClickSndResID + 1)
#define DoneSndResID  (RetrySndResID + 1)

#define DefaultEnabled  true
#define PlaySoundsAsync false

void Sounds_Init(Sounds *pSounds)
{
    pSounds->Enabled = DefaultEnabled;
    
    pSounds->ClickSnd = GetResource('snd ', ClickSndResID);
    if (pSounds->ClickSnd == nil)
    {
        ShowError("\pClick snd resource missing!", true);
    }
    
    pSounds->RetrySnd = GetResource('snd ', RetrySndResID);
    if (pSounds->RetrySnd == nil)
    {
        ShowError("\pRetry snd resource missing!", true);
    }
    
    pSounds->DoneSnd = GetResource('snd ', DoneSndResID);
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
