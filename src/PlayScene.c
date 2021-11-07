// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "PlayScene.h"

#define PlayfieldMargin     4
#define PlayfieldPadding    2
#define PlayfieldCornerSize 12
#define LightMargin         6
#define LightSize           50
#define LightCornerSize     8
#define PlayfieldPattern    ltGray

#define HUDMargin     PlayfieldMargin
#define HUDCornerSize PlayfieldCornerSize
#define HUDPattern    PlayfieldPattern

#define LevelTextScale 2

void PlayScene_Init(GameWindow *pGameWindow)
{
    Rect r1, r2;

    // Setup Playfield
    pGameWindow->PlayScene.PlayfieldRect.top = PlayfieldMargin;
    pGameWindow->PlayScene.PlayfieldRect.bottom = pGameWindow->Window->portRect.bottom - PlayfieldMargin;
    pGameWindow->PlayScene.PlayfieldRect.left = pGameWindow->PlayScene.PlayfieldRect.top;
    pGameWindow->PlayScene.PlayfieldRect.right = pGameWindow->PlayScene.PlayfieldRect.bottom;
    
    // Setup HUD
    pGameWindow->PlayScene.HUDRect.top = HUDMargin;
    pGameWindow->PlayScene.HUDRect.bottom = pGameWindow->Window->portRect.bottom - HUDMargin;
    pGameWindow->PlayScene.HUDRect.left = pGameWindow->PlayScene.PlayfieldRect.right + HUDMargin;
    pGameWindow->PlayScene.HUDRect.right = pGameWindow->Window->portRect.right - HUDMargin;
    
    // Setup Level
    GetScaledPicFrame(pGameWindow->Engine.SetB ? pGameWindow->Bitmaps.BCharPict : pGameWindow->Bitmaps.ACharPict, LevelTextScale, &r1);
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), 1 + pGameWindow->Engine.Level, LevelTextScale, &r2);
    ConcatenateRect(&r1, &r2, &(pGameWindow->PlayScene.LevelRect));
    
    GetBoxRect(&(pGameWindow->PlayScene.HUDRect), Top, &r1);
    GetBoxRect(&r1, Bottom, &r2);
    CenterRect(&r2, &(pGameWindow->PlayScene.LevelRect));
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
        FillRoundRect(&(pGameWindow->PlayScene.PlayfieldRect), PlayfieldCornerSize, PlayfieldCornerSize, PlayfieldPattern);
        //FillRoundRect(&(pGameWindow->PlayScene.HUDRect), HUDCornerSize, HUDCornerSize, HUDPattern);
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
                FillRoundRect(&lightRect, LightCornerSize, LightCornerSize, black);
            }
        }
    }
    
    // Draw HUD
    
    // Draw Level
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
    
    // Draw Stars
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
            GameWindow_SetScene(pGameWindow, LevelEnd);
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->PlayScene.HUDRect)))
    {
        // Click within HUD
    }
}
