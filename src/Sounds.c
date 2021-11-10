// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Sounds.h"

#define ClickSndResID BaseResID
#define RetrySndResID (ClickSndResID + 1)
#define DoneSndResID  (RetrySndResID + 1)

#define DefaultEnabled  true
#define PlaySoundsAsync true

void Sounds_Init(Sounds *pSounds)
{
    pSounds->Enabled = DefaultEnabled;
    
    SndNewChannel(&(pSounds->SndChannel), 0, 0, nil);
    
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
        SndPlay(pSounds->SndChannel, pSounds->ClickSnd, PlaySoundsAsync);
    }
}

void Sounds_PlayRetrySnd(const Sounds *pSounds)
{
    if (pSounds->Enabled)
    {
        SndPlay(pSounds->SndChannel, pSounds->RetrySnd, PlaySoundsAsync);
    }
}

void Sounds_PlayDoneSnd(const Sounds *pSounds)
{
    if (pSounds->Enabled)
    {
        SndPlay(pSounds->SndChannel, pSounds->DoneSnd, PlaySoundsAsync);
    }
}
