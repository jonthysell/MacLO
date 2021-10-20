// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"

void GameWindow_SetLightRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t c, const int8_t r);
void GameWindow_DrawPlayfield(const GameWindow *pGameWindow, Boolean fullRefresh);
void GameWindow_DrawHUD(const GameWindow *pGameWindow, Boolean fullRefresh);

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
    pGameWindow->PlayfieldRect.top = PlayfieldMargin;
    pGameWindow->PlayfieldRect.bottom = pGameWindow->Window->portRect.bottom - PlayfieldMargin;
    pGameWindow->PlayfieldRect.left = pGameWindow->PlayfieldRect.top;
    pGameWindow->PlayfieldRect.right = pGameWindow->PlayfieldRect.bottom;
    
    pGameWindow->HUDRect.top = HUDMargin;
    pGameWindow->HUDRect.bottom = pGameWindow->Window->portRect.bottom - HUDMargin;
    pGameWindow->HUDRect.left = pGameWindow->PlayfieldRect.right + HUDMargin;
    pGameWindow->HUDRect.right = pGameWindow->Window->portRect.right - HUDMargin;
        
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
        FillRect(pContentRect, WindowPattern);
    }
    
    GameWindow_DrawPlayfield(pGameWindow, fullRefresh);
    GameWindow_DrawHUD(pGameWindow, fullRefresh);
}

void GameWindow_SetLightRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t c, const int8_t r)
{
    pRect->top = pGameWindow->PlayfieldRect.top + PlayfieldPadding + LightMargin + (r * (LightMargin + LightSize));
    pRect->bottom = pRect->top + LightSize;
    pRect->left = pGameWindow->PlayfieldRect.left + PlayfieldPadding + LightMargin + (c * (LightMargin + LightSize));
    pRect->right = pRect->left + LightSize;
}

void GameWindow_DrawPlayfield(const GameWindow *pGameWindow, Boolean fullRefresh)
{
    int8_t r, c;
    Rect lightRect;
    
    SetPort(pGameWindow->Window);
    
    if (fullRefresh)
    {
        // Fill background
        FillRoundRect(&(pGameWindow->PlayfieldRect), PlayfieldCornerSize, PlayfieldCornerSize, PlayfieldPattern);
    }
    
    // Draw lights
    for (r = 0; r < PuzzleSize; r++)
    {
        for (c = 0; c < PuzzleSize; c++)
        {
            GameWindow_SetLightRect(pGameWindow, &lightRect, c, r);
            
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
}

void GameWindow_DrawHUD(const GameWindow *pGameWindow, Boolean fullRefresh)
{
    SetPort(pGameWindow->Window);
    
    if (fullRefresh)
    {
        // Fill background
        FillRoundRect(&(pGameWindow->HUDRect), HUDCornerSize, HUDCornerSize, HUDPattern);
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
            for (c = 0; c < PuzzleSize; c++)
            {
                GameWindow_SetLightRect(pGameWindow, &lightRect, c, r);
                
                if (PtInRect(*pPosition, &lightRect))
                {
                    GameEngine_ToggleLights(&(pGameWindow->Engine), c, r);
                    GameWindow_Draw(pGameWindow, false);
                    break;
                }
            }
        }
       
    }
}
