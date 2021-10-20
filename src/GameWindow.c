// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"

void GameWindow_DrawPlayfield(const GameWindow *pGameWindow);

void GameWindow_Init(GameWindow *pGameWindow)
{
    if (pGameWindow->Window != nil)
    {
        ShowError("\pGameWindow already initialized!", false);
    }
    
    pGameWindow->Window = GetNewWindow(BaseResID, nil, MoveToFront);
    
    if (pGameWindow->Window == nil)
    {
        ShowError("\pGameWindow resource WIND BaseResID missing!", true);
    }
    
    // Setup rects
    pGameWindow->PlayfieldRect.left = PlayfieldMargin;
    pGameWindow->PlayfieldRect.top = PlayfieldMargin;
    pGameWindow->PlayfieldRect.right = (2 * PlayfieldMargin) + (PuzzleSize * (LightSize + LightMargin)) - LightMargin;
    pGameWindow->PlayfieldRect.bottom = (2 * PlayfieldMargin) + (PuzzleSize * (LightSize + LightMargin)) - LightMargin;;
    
    // Load first level
    GameEngine_LoadLevel(&(pGameWindow->Engine), 0, false);
    
}

void GameWindow_Draw(const GameWindow *pGameWindow, Boolean fullRefresh)
{
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    SetPort(pGameWindow->Window);
    
    if (fullRefresh)
    {
        // Fill background
        ForeColor(blackColor);
        PaintRect(pContentRect);
    }
    
    GameWindow_DrawPlayfield(pGameWindow);
}

void GameWindow_DrawPlayfield(const GameWindow *pGameWindow)
{
    int8_t r, c;
    Rect lightRect;
    
    SetPort(pGameWindow->Window);
    
    // Draw lights
    for (r = 0; r < PuzzleSize; r++)
    {
        lightRect.top = PlayfieldMargin + (r * (LightMargin + LightSize));
        lightRect.bottom = lightRect.top + LightSize;
        
        for (c = 0; c < PuzzleSize; c++)
        {
            lightRect.left = PlayfieldMargin + (c * (LightMargin + LightSize));
            lightRect.right = lightRect.left + LightSize;
            
            if (GameEngine_GetLight(&(pGameWindow->Engine), c, r))
            {
                // Draw ON light
                ForeColor(whiteColor);
                PaintRoundRect(&lightRect, LightCornerSize, LightCornerSize);
            }
            else
            {
                // Draw OFF light
                ForeColor(blackColor);
                PaintRoundRect(&lightRect, LightCornerSize, LightCornerSize);
                ForeColor(whiteColor);
                FrameRoundRect(&lightRect, LightCornerSize, LightCornerSize);
            }
        }
    }
}

void GameWindow_Show(const GameWindow *pGameWindow)
{
    ShowWindow(pGameWindow->Window);
}

void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    int8_t r, c;
    Rect lightRect;
    
    if (PtInRect(*pPosition, &(pGameWindow->PlayfieldRect)))
    {
        for (r = 0; r < PuzzleSize; r++)
        {
            lightRect.top = PlayfieldMargin + (r * (LightMargin + LightSize));
            lightRect.bottom = lightRect.top + LightSize;
        
            for (c = 0; c < PuzzleSize; c++)
            {
                lightRect.left = PlayfieldMargin + (c * (LightMargin + LightSize));
                lightRect.right = lightRect.left + LightSize;
                
                if (PtInRect(*pPosition, &lightRect))
                {
                    GameEngine_ToggleLights(&(pGameWindow->Engine), c, r);
                    GameWindow_DrawPlayfield(pGameWindow);
                    break;
                }
            }
        }
       
    }
}
