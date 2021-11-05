// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Bitmaps.h"

#define NumChars             10

#define TitlePictResID       BaseResID
#define NumCharPictBaseResID (TitlePictResID + 1)
#define ACharPictResID       (NumCharPictBaseResID + NumChars)
#define BCharPictResID       (ACharPictResID + 1)
#define SlashCharPictResID   (BCharPictResID + 1)

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