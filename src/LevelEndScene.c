// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "LevelEndScene.h"

#define LevelTextScale 4
#define HalfStarScale  3
#define ScoreTextScale 1

void LevelEndScene_Init(GameWindow *pGameWindow)
{
    Rect r;
    
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    // Setup level
    GetScaledPicFrame(pGameWindow->Engine.SetB ? pGameWindow->Bitmaps.BCharPict : pGameWindow->Bitmaps.ACharPict, LevelTextScale, &(pGameWindow->LevelEndScene.LevelRect));
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), 1 + pGameWindow->Engine.Level, LevelTextScale, &r);
    ConcatenateRect(&(pGameWindow->LevelEndScene.LevelRect), &r, &(pGameWindow->LevelEndScene.LevelRect));

    GetBoxRect(pContentRect, Top, &r);
    CenterRect(&r, &(pGameWindow->LevelEndScene.LevelRect));

    // Setup half-stars
    Bitmaps_GetHalfStarsRect(&(pGameWindow->Bitmaps), GameEngine_GetHalfStars(&(pGameWindow->Engine)), MaxStars, HalfStarScale, &(pGameWindow->LevelEndScene.HalfStarsRect));
    
    GetBoxRect(pContentRect, Center, &r);
    CenterRect(&r, &(pGameWindow->LevelEndScene.HalfStarsRect));
    
    // Setup score
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), pGameWindow->Engine.Score, ScoreTextScale, &(pGameWindow->LevelEndScene.ScoreRect));
    GetScaledPicFrame(pGameWindow->Bitmaps.SlashCharPict, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->LevelEndScene.ScoreRect), &r, &(pGameWindow->LevelEndScene.ScoreRect));
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->LevelEndScene.ScoreRect), &r, &(pGameWindow->LevelEndScene.ScoreRect));
    
    GetBoxRect(pContentRect, Bottom, &r);
    CenterRect(&r, &(pGameWindow->LevelEndScene.ScoreRect));
    
    // Setup retry button
    GetPictureRect(pGameWindow->Bitmaps.RetryButtonPict, &(pGameWindow->LevelEndScene.RetryButtonRect));
    
    GetBoxRect(pContentRect, BottomLeft, &r);
    CenterRect(&r, &(pGameWindow->LevelEndScene.RetryButtonRect));
    
    // Setup next button
    GetPictureRect(pGameWindow->Bitmaps.NextButtonPict, &(pGameWindow->LevelEndScene.NextButtonRect));
    
    GetBoxRect(pContentRect, BottomRight, &r);
    CenterRect(&r, &(pGameWindow->LevelEndScene.NextButtonRect));
}

void LevelEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    // Draw level
    MoveTo(pGameWindow->LevelEndScene.LevelRect.left, pGameWindow->LevelEndScene.LevelRect.top);
    if (pGameWindow->Engine.SetB)
    {
        Bitmaps_DrawBChar(&(pGameWindow->Bitmaps), LevelTextScale);
    }
    else
    {
        Bitmaps_DrawAChar(&(pGameWindow->Bitmaps), LevelTextScale);
    }
    Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), 1 + pGameWindow->Engine.Level, LevelTextScale);
    
    // Draw half-stars
    MoveTo(pGameWindow->LevelEndScene.HalfStarsRect.left, pGameWindow->LevelEndScene.HalfStarsRect.top);
    Bitmaps_DrawHalfStars(&(pGameWindow->Bitmaps), GameEngine_GetHalfStars(&(pGameWindow->Engine)), MaxStars, HalfStarScale);
    
    // Draw score
    MoveTo(pGameWindow->LevelEndScene.ScoreRect.left, pGameWindow->LevelEndScene.ScoreRect.top);
    Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), pGameWindow->Engine.Score, ScoreTextScale);
    Bitmaps_DrawSlashChar(&(pGameWindow->Bitmaps), ScoreTextScale);
    Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale);
    
    // Draw retry button
    DrawPicture(pGameWindow->Bitmaps.RetryButtonPict, &(pGameWindow->LevelEndScene.RetryButtonRect));
    
    // Draw next button
    DrawPicture(pGameWindow->Bitmaps.NextButtonPict, &(pGameWindow->LevelEndScene.NextButtonRect));
}

void LevelEndScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    if (PtInRect(*pPosition, &(pGameWindow->LevelEndScene.RetryButtonRect)))
    {
        GameEngine_ResetLevel(&(pGameWindow->Engine));
        GameWindow_SetScene(pGameWindow, Play);
    }
    else if (PtInRect(*pPosition, &(pGameWindow->LevelEndScene.NextButtonRect)))
    {
        GameEngine_NextLevel(&(pGameWindow->Engine));
        GameWindow_SetScene(pGameWindow, GameEngine_IsGameOver(&(pGameWindow->Engine)) ? GameEnd : Play);
    }
}
