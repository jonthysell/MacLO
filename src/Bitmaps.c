// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Bitmaps.h"

#define TitlePictResID       BaseResID
#define NumCharPictBaseResID (TitlePictResID + 1)
#define ACharPictResID       (NumCharPictBaseResID + NumChars)
#define BCharPictResID       (ACharPictResID + 1)
#define SlashCharPictResID   (BCharPictResID + 1)

void Bitmaps_DrawScaledPic(const PicHandle pic, const uint8_t scale);

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
    for (i = 0; i < NumChars; i++)
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
}

void Bitmaps_DrawScaledPic(const PicHandle pic, const uint8_t scale)
{
    Point penPosition;
    Rect destRect;
    
    GetPen(&penPosition);
    GetScaledPicFrame(pic, scale, &destRect);
    
    OffsetRect(&destRect, penPosition.h, penPosition.v);
    
    DrawPicture(pic, &destRect);
    MoveTo(destRect.right, destRect.top);
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
        Bitmaps_DrawScaledPic(pBitmaps->NumCharPicts[0], scale);
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
            Bitmaps_DrawScaledPic(pBitmaps->NumCharPicts[digit], scale);
            started = true;
        }
    }
}

void Bitmaps_DrawAChar(const Bitmaps *pBitmaps, const uint8_t scale)
{
    Bitmaps_DrawScaledPic(pBitmaps->ACharPict, scale);
}

void Bitmaps_DrawBChar(const Bitmaps *pBitmaps, const uint8_t scale)
{
    Bitmaps_DrawScaledPic(pBitmaps->BCharPict, scale);
}

void Bitmaps_DrawSlashChar(const Bitmaps *pBitmaps, const uint8_t scale)
{
    Bitmaps_DrawScaledPic(pBitmaps->SlashCharPict, scale);
}
