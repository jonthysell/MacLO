// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Bitmaps.h"

#define TitlePictResID       BaseResID
#define NumCharPictBaseResID (TitlePictResID + 1)
#define ACharPictResID       (NumCharPictBaseResID + NumCharPictCount)
#define BCharPictResID       (ACharPictResID + 1)
#define SlashCharPictResID   (BCharPictResID + 1)
#define StarPictBaseResID    (SlashCharPictResID + 1)
#define NextButtonPictResID  (StarPictBaseResID + StarPictCount)
#define RetryButtonPictResID (NextButtonPictResID + 1)

#define StarRectPadding 2

void Bitmaps_Init(Bitmaps *pBitmaps)
{
    int16_t i;
    
    // Load title
    pBitmaps->TitlePict = GetPicture(TitlePictResID);
    if (pBitmaps->TitlePict == nil)
    {
        ShowError("\pTitle PICT resource missing!", true);
    }
    
    // Load number chars
    for (i = 0; i < NumCharPictCount; i++)
    {
        pBitmaps->NumCharPicts[i] = GetPicture(NumCharPictBaseResID + i);
        if (pBitmaps->NumCharPicts[i] == nil)
        {
            ShowError("\pNumber char PICT resource missing!", true);
        }
    }
    
    // Load "A" char
    pBitmaps->ACharPict = GetPicture(ACharPictResID);
    if (pBitmaps->ACharPict == nil)
    {
        ShowError("\pA char PICT resource missing!", true);
    }
    
    // Load "B" char
    pBitmaps->BCharPict = GetPicture(BCharPictResID);
    if (pBitmaps->BCharPict == nil)
    {
        ShowError("\pB char PICT resource missing!", true);
    }
    
    // Load "/" char
    pBitmaps->SlashCharPict = GetPicture(SlashCharPictResID);
    if (pBitmaps->SlashCharPict == nil)
    {
        ShowError("\pSlash char PICT resource missing!", true);
    }
    
    // Load half-stars
    for (i = 0; i < StarPictCount; i++)
    {
        pBitmaps->StarPicts[i] = GetPicture(StarPictBaseResID + i);
        if (pBitmaps->StarPicts[i] == nil)
        {
            ShowError("\pStar PICT resource missing!", true);
        }
    }
    
    // Load next button
    pBitmaps->SlashCharPict = GetPicture(SlashCharPictResID);
    if (pBitmaps->SlashCharPict == nil)
    {
        ShowError("\pSlash char PICT resource missing!", true);
    }
    
    // Load next button
    pBitmaps->NextButtonPict = GetPicture(NextButtonPictResID);
    if (pBitmaps->NextButtonPict == nil)
    {
        ShowError("\pNext button PICT resource missing!", true);
    }
    
    // Load retry button
    pBitmaps->RetryButtonPict = GetPicture(RetryButtonPictResID);
    if (pBitmaps->RetryButtonPict == nil)
    {
        ShowError("\pRetry button PICT resource missing!", true);
    }
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

void Bitmaps_GetHalfStarsRect(const Bitmaps *pBitmaps, const uint8_t halfStars, const uint8_t maxStars, const uint8_t scale, Rect *pDestRect)
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
        MoveTo(penPosition.h + (StarRectPadding * scale), penPosition.v);
    }
}
