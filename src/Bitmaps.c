// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <OSUtils.h>

#include "Bitmaps.h"

#define BasePictResID        BaseResID

#define TitlePictResID       0
#define NumCharPictBaseResID (TitlePictResID + 1)
#define ACharPictResID       (NumCharPictBaseResID + NumCharPictCount)
#define BCharPictResID       (ACharPictResID + 1)
#define SlashCharPictResID   (BCharPictResID + 1)
#define StarPictBaseResID    (SlashCharPictResID + 1)
#define PrevButtonPictResID  (StarPictBaseResID + StarPictCount)
#define NextButtonPictResID  (PrevButtonPictResID + 1)
#define RetryButtonPictResID (NextButtonPictResID + 1)
#define SoundOffPictResID    (RetryButtonPictResID + 1)
#define SoundOnPictResID     (SoundOffPictResID + 1)
#define LightOffPictResID    (SoundOnPictResID + 1)
#define LightOnPictResID     (LightOffPictResID + 1)

#define TotalPictCount       (LightOnPictResID + 1)

#define StarRectPadding      2

const int16_t MonthOffset[] = {
    0,   // Jan
    31,  // Feb
    60,  // Mar
    91,  // Apr
    121, // May
    152, // Jun
    182, // Jul
    213, // Aug
    244, // Sep
    274, // Oct
    305, // Nov
    335, // Dec
};

int16_t Bitmaps_GetOverrideBaseResID();

PicHandle Bitmaps_GetPict(const int16_t holidayResID, const int16_t offset);

void Bitmaps_Init(Bitmaps *pBitmaps)
{
    int16_t i, baseResID;
    
    baseResID = Bitmaps_GetOverrideBaseResID();
    
    // Load title
    pBitmaps->TitlePict = Bitmaps_GetPict(baseResID, TitlePictResID);
    if (pBitmaps->TitlePict == nil)
    {
        ShowError("\pTitle PICT resource missing!", true);
    }
    
    // Load number chars
    for (i = 0; i < NumCharPictCount; i++)
    {
        pBitmaps->NumCharPicts[i] = Bitmaps_GetPict(baseResID, NumCharPictBaseResID + i);
        if (pBitmaps->NumCharPicts[i] == nil)
        {
            ShowError("\pNumber char PICT resource missing!", true);
        }
    }
    
    // Load "A" char
    pBitmaps->ACharPict = Bitmaps_GetPict(baseResID, ACharPictResID);
    if (pBitmaps->ACharPict == nil)
    {
        ShowError("\pA char PICT resource missing!", true);
    }
    
    // Load "B" char
    pBitmaps->BCharPict = Bitmaps_GetPict(baseResID, BCharPictResID);
    if (pBitmaps->BCharPict == nil)
    {
        ShowError("\pB char PICT resource missing!", true);
    }
    
    // Load "/" char
    pBitmaps->SlashCharPict = Bitmaps_GetPict(baseResID, SlashCharPictResID);
    if (pBitmaps->SlashCharPict == nil)
    {
        ShowError("\pSlash char PICT resource missing!", true);
    }
    
    // Load half-stars
    for (i = 0; i < StarPictCount; i++)
    {
        pBitmaps->StarPicts[i] = Bitmaps_GetPict(baseResID, StarPictBaseResID + i);
        if (pBitmaps->StarPicts[i] == nil)
        {
            ShowError("\pStar PICT resource missing!", true);
        }
    }
    
    // Load slash char
    pBitmaps->SlashCharPict = Bitmaps_GetPict(baseResID, SlashCharPictResID);
    if (pBitmaps->SlashCharPict == nil)
    {
        ShowError("\pSlash char PICT resource missing!", true);
    }
    
    // Load prev button
    pBitmaps->PrevButtonPict = Bitmaps_GetPict(baseResID, PrevButtonPictResID);
    if (pBitmaps->PrevButtonPict == nil)
    {
        ShowError("\pPrev button PICT resource missing!", true);
    }
    
    // Load next button
    pBitmaps->NextButtonPict = Bitmaps_GetPict(baseResID, NextButtonPictResID);
    if (pBitmaps->NextButtonPict == nil)
    {
        ShowError("\pNext button PICT resource missing!", true);
    }
    
    // Load retry button
    pBitmaps->RetryButtonPict = Bitmaps_GetPict(baseResID, RetryButtonPictResID);
    if (pBitmaps->RetryButtonPict == nil)
    {
        ShowError("\pRetry button PICT resource missing!", true);
    }
    
    // Load sound off
    pBitmaps->SoundOffPict = Bitmaps_GetPict(baseResID, SoundOffPictResID);
    if (pBitmaps->SoundOffPict == nil)
    {
        ShowError("\pSound off PICT resource missing!", true);
    }
    
    // Load sound on
    pBitmaps->SoundOnPict = Bitmaps_GetPict(baseResID, SoundOnPictResID);
    if (pBitmaps->SoundOnPict == nil)
    {
        ShowError("\pSound on PICT resource missing!", true);
    }
    
    // Load light off
    pBitmaps->LightOffPict = Bitmaps_GetPict(baseResID, LightOffPictResID);
    if (pBitmaps->LightOffPict == nil)
    {
        ShowError("\pLight off PICT resource missing!", true);
    }
    
    // Load light on
    pBitmaps->LightOnPict = Bitmaps_GetPict(baseResID, LightOnPictResID);
    if (pBitmaps->LightOnPict == nil)
    {
        ShowError("\pLight on PICT resource missing!", true);
    }
}

int16_t Bitmaps_GetOverrideBaseResID()
{
    uint32_t seconds;
    DateTimeRec dateTime;
    int16_t dayOfYear;
    
    GetDateTime(&seconds);
    Secs2Date(seconds, &dateTime);
    
    // Calculate "day number" (1 - 366, always assume leap year)
    dayOfYear = MonthOffset[dateTime.month - 1];
    dayOfYear += dateTime.day;
    
    return BasePictResID + (dayOfYear * TotalPictCount);
}

PicHandle Bitmaps_GetPict(const int16_t baseResID, const int16_t offset)
{
    PicHandle pic;
    pic = (PicHandle)Get1Resource('PICT', baseResID + offset);
    
    if (pic == nil)
    {
        // No override pic, get default
        pic = (PicHandle)Get1Resource('PICT', BasePictResID + offset);
    }
    
    return pic;
}

void Bitmaps_GetNumberRect(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale, Rect *pDestRect)
{
    bool started;
    uint32_t k, digit, remainder;
    Rect digitRect;
    
    pDestRect->top = 0;
    pDestRect->left = 0;
    pDestRect->bottom = 0;
    pDestRect->right = 0;
    
    if (number == 0)
    {
        GetScaledPicFrame(pBitmaps->NumCharPicts[0], scale, &digitRect);
        ConcatenateRect(pDestRect, &digitRect, pDestRect);
        return;
    }
        
    started = false;
    remainder = number;
    
    for (k = 1000000000UL; k > 0; k = k / 10)
    {
        digit = remainder / k;
        remainder = remainder % k;
    
        if (started || (digit > 0 && digit < 10))
        {
            GetScaledPicFrame(pBitmaps->NumCharPicts[digit], scale, &digitRect);
            ConcatenateRect(pDestRect, &digitRect, pDestRect);
            started = true;
        }
    }
}

void Bitmaps_DrawNumber(const Bitmaps *pBitmaps, const uint32_t number, const uint8_t scale)
{
    bool started;
    uint32_t k, digit, remainder;
    
    if (number == 0)
    {
        DrawScaledPic(pBitmaps->NumCharPicts[0], scale);
        return;
    }
    
    started = false;
    remainder = number;
    
    for (k = 1000000000UL; k > 0; k = k / 10)
    {
        digit = remainder / k;
        remainder = remainder % k;
    
        if (started || (digit > 0 && digit < 10))
        {
            DrawScaledPic(pBitmaps->NumCharPicts[digit], scale);
            started = true;
        }
    }
}

void Bitmaps_DrawAChar(const Bitmaps *pBitmaps, const uint8_t scale)
{
    DrawScaledPic(pBitmaps->ACharPict, scale);
}

void Bitmaps_DrawBChar(const Bitmaps *pBitmaps, const uint8_t scale)
{
    DrawScaledPic(pBitmaps->BCharPict, scale);
}

void Bitmaps_DrawSlashChar(const Bitmaps *pBitmaps, const uint8_t scale)
{
    DrawScaledPic(pBitmaps->SlashCharPict, scale);
}

void Bitmaps_GetHalfStarsRect(const Bitmaps *pBitmaps, const uint8_t maxStars, const uint8_t scale, Rect *pDestRect)
{
    uint8_t stars;
    Rect starRect, paddingRect;
    
    pDestRect->top = 0;
    pDestRect->left = 0;
    pDestRect->bottom = 0;
    pDestRect->right = 0;
    
    if (maxStars == 0)
    {
        return;
    }
    
    GetScaledPicFrame(pBitmaps->StarPicts[0], scale, &starRect);
    paddingRect = starRect;
    paddingRect.right = paddingRect.left + (StarRectPadding * scale);
    
    ConcatenateRect(pDestRect, &starRect, pDestRect);
    
    for (stars = 1; stars < maxStars; stars++)
    {
        ConcatenateRect(pDestRect, &paddingRect, pDestRect);
        ConcatenateRect(pDestRect, &starRect, pDestRect);
    }
}

void Bitmaps_DrawHalfStars(const Bitmaps *pBitmaps, const uint8_t halfStars, const uint8_t maxStars, const uint8_t scale)
{
    Point penPosition;
    uint8_t i, progress, drawn;
    
    progress = halfStars;
    drawn = 0;
    
    for (i = StarPictCount - 1; i > 0; i--)
    {
        while (drawn < maxStars && progress >= i)
        {
            DrawScaledPic(pBitmaps->StarPicts[i], scale);
            GetPen(&penPosition);
            MoveTo(penPosition.h + (StarRectPadding * scale), penPosition.v);
            progress -= i;
            drawn++;
        }
    }
    
    for (; drawn < maxStars; drawn++)
    {
        DrawScaledPic(pBitmaps->StarPicts[0], scale);
        GetPen(&penPosition);
        MoveTo(penPosition.h + (StarRectPadding * scale), penPosition.v);
    }
}

void Bitmaps_GetSoundRect(const Bitmaps *pBitmaps, const uint8_t scale, Rect *pDestRect)
{
    Rect r;
    
    GetScaledPicFrame(pBitmaps->SoundOffPict, scale, pDestRect);
    GetScaledPicFrame(pBitmaps->SoundOnPict, scale, &r);
    ConcatenateRect(pDestRect, &r, pDestRect);
}

void Bitmaps_DrawSound(const Bitmaps *pBitmaps, const bool enabled, const uint8_t scale)
{
    Point penPosition;
    Rect r;
    
    DrawScaledPic(pBitmaps->SoundOffPict, scale);
    if (enabled)
    {
        DrawScaledPic(pBitmaps->SoundOnPict, scale);
    }
    else
    {
        GetScaledPicFrame(pBitmaps->SoundOnPict, scale, &r);
        GetPen(&penPosition);
        OffsetRect(&r, penPosition.h, penPosition.v);
        FillRect(&r, black);
    }
}
