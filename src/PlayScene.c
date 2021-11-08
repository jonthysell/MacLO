// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "PlayScene.h"

#define PlayfieldMargin     4
#define PlayfieldPadding    2
#define PlayfieldCornerSize 12
#define LightMargin         6
#define LightSize           50
#define LightCornerSize     12
#define PlayfieldPattern    ltGray

#define HUDMargin     PlayfieldMargin
#define HUDCornerSize PlayfieldCornerSize
#define HUDPattern    PlayfieldPattern

#define LevelTextScale 3
#define HalfStarScale  2
#define ScoreTextScale 1

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
    Bitmaps_GetHalfStarsRect(&(pGameWindow->Bitmaps), GameEngine_GetHalfStars(&(pGameWindow->Engine)), MaxStars, HalfStarScale, &(pGameWindow->PlayScene.HalfStarsRect));
    
    GetBoxRect(&(pGameWindow->PlayScene.HUDRect), Center, &r);
    CenterRect(&r, &(pGameWindow->PlayScene.HalfStarsRect));
    
    // Setup score
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), pGameWindow->Engine.Score, ScoreTextScale, &(pGameWindow->PlayScene.ScoreRect));
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
        FrameRoundRect(&(pGameWindow->PlayScene.HUDRect), HUDCornerSize, HUDCornerSize);
        ForeColor(blackColor);
    }
    
    // Draw Playfield
    
    // Draw lights
    for (r = 0; r < PuzzleSize; r++)
    {
        for (c = 0; c < PuzzleSize; c++)
        {
            PlayScene_SetLightRect(pGameWindow, &lightRect, c, r);
            
            if (GameEngine_GetLight(&(pGameWindow->Engine), c, r))
            {
                // Draw ON light
                FillRoundRect(&lightRect, LightCornerSize, LightCornerSize, white);
            }
            else
            {
                // Draw OFF light
                FillRoundRect(&lightRect, LightCornerSize, LightCornerSize, dkGray);
            }
        }
    }
    
    // Draw HUD
    
    // Draw level
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
    
    // Draw half-stars
    MoveTo(pGameWindow->PlayScene.HalfStarsRect.left, pGameWindow->PlayScene.HalfStarsRect.top);
    Bitmaps_DrawHalfStars(&(pGameWindow->Bitmaps), GameEngine_GetHalfStars(&(pGameWindow->Engine)), MaxStars, HalfStarScale);
    
    // Draw score
    MoveTo(pGameWindow->PlayScene.ScoreRect.left, pGameWindow->PlayScene.ScoreRect.top);
    Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), pGameWindow->Engine.Score, ScoreTextScale);
    Bitmaps_DrawSlashChar(&(pGameWindow->Bitmaps), ScoreTextScale);
    Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale);
    
    // Draw retry button
    DrawPicture(pGameWindow->Bitmaps.RetryButtonPict, &(pGameWindow->PlayScene.RetryButtonRect));
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
                    GameEngine_ToggleLights(&(pGameWindow->Engine), c, r);
                    GameWindow_Draw(pGameWindow, false);
                    break;
                }
            }
        }
        
        if (GameEngine_IsCompleted(&(pGameWindow->Engine)))
        {
            // Level was completed in the last click
            GameWindow_Draw(pGameWindow, false);
            GameWindow_SetScene(pGameWindow, LevelEnd);
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->PlayScene.HUDRect)))
    {
        // Click within HUD
        
        if (PtInRect(*pPosition, &(pGameWindow->PlayScene.RetryButtonRect)))
        {
            GameEngine_ResetLevel(&(pGameWindow->Engine));
            GameWindow_Draw(pGameWindow, false);
        }
    }
}
