// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file LevelEndScene.c
 *
 * This file provides implementations for LevelEndScene.h.
 */

#include "LevelEndScene.h"

/** Scale factor for the level text. */
#define LevelTextScale 4

/** Scale factor for the stars. */
#define HalfStarScale  3

/** Scale factor for score text. */
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
    Bitmaps_GetHalfStarsRect(&(pGameWindow->Bitmaps), MaxStars, HalfStarScale, &(pGameWindow->LevelEndScene.HalfStarsRect));
    
    GetBoxRect(pContentRect, Center, &r);
    CenterRect(&r, &(pGameWindow->LevelEndScene.HalfStarsRect));
    
    // Setup score
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale, &(pGameWindow->LevelEndScene.ScoreRect));
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
    if (fullRefresh)
    {
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
    }
    
    // Draw half-stars
    if (fullRefresh)
    {
        MoveTo(pGameWindow->LevelEndScene.HalfStarsRect.left, pGameWindow->LevelEndScene.HalfStarsRect.top);
        Bitmaps_DrawHalfStars(&(pGameWindow->Bitmaps), GameEngine_GetHalfStars(&(pGameWindow->Engine)), MaxStars, HalfStarScale);
    }
    
    // Draw score
    if (fullRefresh)
    {
        MoveTo(pGameWindow->LevelEndScene.ScoreRect.left, pGameWindow->LevelEndScene.ScoreRect.top);
        Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale);
        Bitmaps_DrawSlashChar(&(pGameWindow->Bitmaps), ScoreTextScale);
        Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale);
    }
    
    // Draw retry button
    if (fullRefresh)
    {
        DrawPicture(pGameWindow->Bitmaps.RetryButtonPict, &(pGameWindow->LevelEndScene.RetryButtonRect));
    
    }
    
    // Draw next button
    if (fullRefresh)
    {
        DrawPicture(pGameWindow->Bitmaps.NextButtonPict, &(pGameWindow->LevelEndScene.NextButtonRect));
    }
}

void LevelEndScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    if (PtInRect(*pPosition, &(pGameWindow->LevelEndScene.RetryButtonRect)))
    {
        // Clicked on retry button
        GameEngine_ResetLevel(&(pGameWindow->Engine));
        GameWindow_SetScene(pGameWindow, Play);
        Sounds_PlayRetrySnd(&(pGameWindow->Sounds));
    }
    else if (PtInRect(*pPosition, &(pGameWindow->LevelEndScene.NextButtonRect)))
    {
        // Clicked on next button
        if (GameEngine_IsLastLevel(&(pGameWindow->Engine)))
        {
            // Finished the last level, go to game end scene
            GameWindow_SetScene(pGameWindow, GameEnd);
            Sounds_PlayDoneSnd(&(pGameWindow->Sounds));
        }
        else
        {
            if (GameEngine_HasPlayedLevel(&(pGameWindow->Engine), pGameWindow->Engine.Level + 1))
            {
                // Next level has been played before, assume they're
                // replaying old levels and return to level select scene
                GameWindow_SetScene(pGameWindow, LevelSelect);
            }
            else
            {
                // First time for next level, load and go to play scene
                GameEngine_NextLevel(&(pGameWindow->Engine));
                GameWindow_SetScene(pGameWindow, Play);
                Sounds_PlayRetrySnd(&(pGameWindow->Sounds));
            }
        }
    }
}
