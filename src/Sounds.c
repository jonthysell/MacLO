// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <GestaltEqu.h>

#include "Sounds.h"

#define SndBaseResId  8192

#define ClickSndResID SndBaseResId
#define RetrySndResID (ClickSndResID + 1)
#define DoneSndResID  (RetrySndResID + 1)

#define DefaultEnabled  true
#define PlaySoundsAsync true

void Sounds_Init(Sounds *pSounds)
{
    OSErr err;
    int32_t sysVersion;
    
    pSounds->Enabled = DefaultEnabled;
    pSounds->SndChannel = nil;
    
    err = Gestalt(gestaltSystemVersion, &sysVersion);
    if (err == noErr && sysVersion >= 0x0700)
    {
        // Only create a shared sound channel on System 7
        // or above in order to cheaply support async sound
        SndNewChannel(&(pSounds->SndChannel), 0, 0, nil);
    }
    
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
        SndPlay(pSounds->SndChannel, pSounds->ClickSnd, PlaySoundsAsync);
        HUnlock(pSounds->ClickSnd);
    }
}

void Sounds_PlayRetrySnd(const Sounds *pSounds)
{
    if (pSounds->Enabled)
    {
        HLock(pSounds->RetrySnd);
        SndPlay(pSounds->SndChannel, pSounds->RetrySnd, PlaySoundsAsync);
        HUnlock(pSounds->RetrySnd);
    }
}

void Sounds_PlayDoneSnd(const Sounds *pSounds)
{
    if (pSounds->Enabled)
    {
        HLock(pSounds->DoneSnd);
        SndPlay(pSounds->SndChannel, pSounds->DoneSnd, PlaySoundsAsync);
        HUnlock(pSounds->DoneSnd);
    }
}
