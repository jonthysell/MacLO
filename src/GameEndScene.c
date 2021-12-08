// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameEndScene.c
 *
 * This file provides implementations for GameEndScene.h.
 */

#include "GameEndScene.h"

/** Scale factor for the A/B set text. */
#define SetTextScale   6

/** Scale factor for the score text. */
#define ScoreTextScale 3

void GameEndScene_Init(GameWindow *pGameWindow)
{
    Rect r;
    
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    // Setup set
    GetScaledPicFrame(pGameWindow->Bitmaps.StarPicts[StarPictCount - 1], SetTextScale, &r);
    GetScaledPicFrame(pGameWindow->Engine.SetB ? pGameWindow->Bitmaps.BCharPict : pGameWindow->Bitmaps.ACharPict, SetTextScale, &(pGameWindow->GameEndScene.SetRect));
    ConcatenateRect(&r, &(pGameWindow->GameEndScene.SetRect), &(pGameWindow->GameEndScene.SetRect));
    ConcatenateRect(&(pGameWindow->GameEndScene.SetRect), &r, &(pGameWindow->GameEndScene.SetRect));
    
    GetBoxRect(pContentRect, Top, &r);
    GetBoxRect(&r, Bottom, &r);
    CenterRect(&r, &(pGameWindow->GameEndScene.SetRect));
    
    // Setup score
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale, &(pGameWindow->GameEndScene.ScoreRect));
    GetScaledPicFrame(pGameWindow->Bitmaps.SlashCharPict, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->GameEndScene.ScoreRect), &r, &(pGameWindow->GameEndScene.ScoreRect));
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->GameEndScene.ScoreRect), &r, &(pGameWindow->GameEndScene.ScoreRect));
    
    GetBoxRect(pContentRect, Bottom, &r);
    GetBoxRect(&r, Top, &r);
    CenterRect(&r, &(pGameWindow->GameEndScene.ScoreRect));
}

void GameEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    // Draw set
    MoveTo(pGameWindow->GameEndScene.SetRect.left, pGameWindow->GameEndScene.SetRect.top);
    DrawScaledPic(pGameWindow->Bitmaps.StarPicts[StarPictCount - 1], SetTextScale);
    if (pGameWindow->Engine.SetB)
    {
        Bitmaps_DrawBChar(&(pGameWindow->Bitmaps), SetTextScale);
    }
    else
    {
        Bitmaps_DrawAChar(&(pGameWindow->Bitmaps), SetTextScale);
    }
    DrawScaledPic(pGameWindow->Bitmaps.StarPicts[StarPictCount - 1], SetTextScale);
    
    // Draw score
    MoveTo(pGameWindow->GameEndScene.ScoreRect.left, pGameWindow->GameEndScene.ScoreRect.top);
    Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale);
    Bitmaps_DrawSlashChar(&(pGameWindow->Bitmaps), ScoreTextScale);
    Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale);
}

void GameEndScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    // Do nothing
}
