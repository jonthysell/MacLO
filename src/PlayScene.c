// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file PlayScene.c
 *
 * This file provides implementations for PlayScene.h.
 */

#include "PlayScene.h"

/** Margin around the Playfield area. */
#define PlayfieldMargin     4

/** Padding within the Playfield area. */
#define PlayfieldPadding    2

/** Corner size of the Playfield area. */
#define PlayfieldCornerSize 12

/** Margin around each light. */
#define LightMargin         6

/** Size (width and height) of each light. */
#define LightSize           50

/** Margin around the HUD area. */
#define HUDMargin PlayfieldMargin

/** Scale factor for the level text. */
#define LevelTextScale 3

/** Scale factor for the stars. */
#define HalfStarScale  2

/** Scale factor for the score text. */
#define ScoreTextScale 1

/**
 * Gets the Rect of the light at the given coordinates.
 * @param pGameWindow The GameWindow.
 * @param pRect. The Rect of the light.
 * @param c The column.
 * @param r The row.
 */
void PlayScene_SetLightRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t c, const int8_t r);

void PlayScene_Init(GameWindow *pGameWindow)
{
    Rect r;
    
    const Rect *pContentRect = &(pGameWindow->Window->portRect);

    // Setup Playfield
    pGameWindow->PlayScene.PlayfieldRect.top = PlayfieldMargin;
    pGameWindow->PlayScene.PlayfieldRect.bottom = pContentRect->bottom - PlayfieldMargin;
    pGameWindow->PlayScene.PlayfieldRect.left = pGameWindow->PlayScene.PlayfieldRect.top;
    pGameWindow->PlayScene.PlayfieldRect.right = pGameWindow->PlayScene.PlayfieldRect.bottom;
    
    // Setup HUD
    pGameWindow->PlayScene.HUDRect.top = HUDMargin;
    pGameWindow->PlayScene.HUDRect.bottom = pContentRect->bottom - HUDMargin;
    pGameWindow->PlayScene.HUDRect.left = pGameWindow->PlayScene.PlayfieldRect.right + HUDMargin;
    pGameWindow->PlayScene.HUDRect.right = pContentRect->right - HUDMargin;
    
    // Setup level
    GetScaledPicFrame(pGameWindow->Engine.SetB ? pGameWindow->Bitmaps.BCharPict : pGameWindow->Bitmaps.ACharPict, LevelTextScale, &(pGameWindow->PlayScene.LevelRect));
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), 1 + pGameWindow->Engine.Level, LevelTextScale, &r);
    ConcatenateRect(&(pGameWindow->PlayScene.LevelRect), &r, &(pGameWindow->PlayScene.LevelRect));

    GetBoxRect(&(pGameWindow->PlayScene.HUDRect), Top, &r);
    CenterRect(&r, &(pGameWindow->PlayScene.LevelRect));

    // Setup half-stars
    Bitmaps_GetHalfStarsRect(&(pGameWindow->Bitmaps), MaxStars, HalfStarScale, &(pGameWindow->PlayScene.HalfStarsRect));
    
    GetBoxRect(&(pGameWindow->PlayScene.HUDRect), Center, &r);
    CenterRect(&r, &(pGameWindow->PlayScene.HalfStarsRect));
    
    // Setup score
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale, &(pGameWindow->PlayScene.ScoreRect));
    GetScaledPicFrame(pGameWindow->Bitmaps.SlashCharPict, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->PlayScene.ScoreRect), &r, &(pGameWindow->PlayScene.ScoreRect));
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->PlayScene.ScoreRect), &r, &(pGameWindow->PlayScene.ScoreRect));
    
    GetBoxRect(&(pGameWindow->PlayScene.HUDRect), Bottom, &r);
    CenterRect(&r, &(pGameWindow->PlayScene.ScoreRect));
    
    // Setup retry button
    GetPictureRect(pGameWindow->Bitmaps.RetryButtonPict, &(pGameWindow->PlayScene.RetryButtonRect));
    
    GetBoxRect(&(pGameWindow->PlayScene.HUDRect), BottomLeft, &r);
    CenterRect(&r, &(pGameWindow->PlayScene.RetryButtonRect));
    
    // Setup sound button
    Bitmaps_GetSoundRect(&(pGameWindow->Bitmaps), 1, &(pGameWindow->PlayScene.SoundButtonRect));
    GetBoxRect(&(pGameWindow->PlayScene.HUDRect), BottomRight, &r);
    CenterRect(&r, &(pGameWindow->PlayScene.SoundButtonRect));
}

void PlayScene_SetLightRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t c, const int8_t r)
{
    pRect->top = pGameWindow->PlayScene.PlayfieldRect.top + PlayfieldPadding + LightMargin + (r * (LightMargin + LightSize));
    pRect->bottom = pRect->top + LightSize;
    pRect->left = pGameWindow->PlayScene.PlayfieldRect.left + PlayfieldPadding + LightMargin + (c * (LightMargin + LightSize));
    pRect->right = pRect->left + LightSize;
}

void PlayScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    int8_t r, c;
    Rect lightRect;
    
    if (fullRefresh)
    {
        // Fill backgrounds
        ForeColor(whiteColor);
        FrameRoundRect(&(pGameWindow->PlayScene.PlayfieldRect), PlayfieldCornerSize, PlayfieldCornerSize);
        ForeColor(blackColor);
    }
    
    // Draw Playfield
    
    // Draw lights
    for (r = 0; r < PuzzleSize; r++)
    {
        for (c = 0; c < PuzzleSize; c++)
        {
            if (fullRefresh || GameEngine_LightChanged(&(pGameWindow->Engine), c, r))
            {
                PlayScene_SetLightRect(pGameWindow, &lightRect, c, r);
                
                if (GameEngine_GetLight(&(pGameWindow->Engine), c, r))
                {
                    // Draw ON light
                    DrawPicture(pGameWindow->Bitmaps.LightOnPict, &lightRect);
                }
                else
                {
                    // Draw OFF light
                    DrawPicture(pGameWindow->Bitmaps.LightOffPict, &lightRect);
                }
            }
        }
    }
    
    // Draw HUD
    
    // Draw level
    if (fullRefresh)
    {
        MoveTo(pGameWindow->PlayScene.LevelRect.left, pGameWindow->PlayScene.LevelRect.top);
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
    if (fullRefresh || GameEngine_HalfStarsChanged(&(pGameWindow->Engine)))
    {
        MoveTo(pGameWindow->PlayScene.HalfStarsRect.left, pGameWindow->PlayScene.HalfStarsRect.top);
        Bitmaps_DrawHalfStars(&(pGameWindow->Bitmaps), GameEngine_GetHalfStars(&(pGameWindow->Engine)), MaxStars, HalfStarScale);
    }
    
    // Draw score
    if (fullRefresh)
    {
        MoveTo(pGameWindow->PlayScene.ScoreRect.left, pGameWindow->PlayScene.ScoreRect.top);
        Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale);
        Bitmaps_DrawSlashChar(&(pGameWindow->Bitmaps), ScoreTextScale);
        Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale);
    }
    
    // Draw retry button
    if (fullRefresh)
    {
        DrawPicture(pGameWindow->Bitmaps.RetryButtonPict, &(pGameWindow->PlayScene.RetryButtonRect));
    }
    
    // Draw sound button
    MoveTo(pGameWindow->PlayScene.SoundButtonRect.left, pGameWindow->PlayScene.SoundButtonRect.top);
    Bitmaps_DrawSound(&(pGameWindow->Bitmaps), pGameWindow->Sounds.Enabled, 1);
}

void PlayScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    int8_t r, c;
    Rect lightRect;
    
    if (PtInRect(*pPosition, &(pGameWindow->PlayScene.PlayfieldRect)))
    {
        // Click within Playfield
        for (r = 0; r < PuzzleSize; r++)
        {
            for (c = 0; c < PuzzleSize; c++)
            {
                PlayScene_SetLightRect(pGameWindow, &lightRect, c, r);
                
                if (PtInRect(*pPosition, &lightRect))
                {
                    // Toggle clicked-on light
                    GameEngine_ToggleLights(&(pGameWindow->Engine), c, r);
                    GameWindow_Draw(pGameWindow, false);
                    Sounds_PlayClickSnd(&(pGameWindow->Sounds));
                    break;
                }
            }
        }
        
        if (GameEngine_IsCompleted(&(pGameWindow->Engine)))
        {
            // Level was completed in the last click
            GameEngine_CompleteLevel(&(pGameWindow->Engine));
            GameWindow_Draw(pGameWindow, false);
            GameSave_SaveData(&(pGameWindow->GameSave), &(pGameWindow->Engine));
            GameWindow_SetScene(pGameWindow, LevelEnd);
            Sounds_PlayDoneSnd(&(pGameWindow->Sounds));
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->PlayScene.HUDRect)))
    {
        // Click within HUD
        
        if (PtInRect(*pPosition, &(pGameWindow->PlayScene.RetryButtonRect)))
        {
            // Click on retry button, reset level
            GameEngine_ResetLevel(&(pGameWindow->Engine));
            GameWindow_Draw(pGameWindow, false);
            Sounds_PlayRetrySnd(&(pGameWindow->Sounds));
        }
        else if (PtInRect(*pPosition, &(pGameWindow->PlayScene.SoundButtonRect)))
        {
            // Click on sound button
            GameWindow_ToggleSound(pGameWindow);
        }
    }
}
