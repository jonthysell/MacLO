// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"

void GameWindow_SetLightRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t c, const int8_t r);

void GameWindow_DrawPlayMode(const GameWindow *pGameWindow, bool fullRefresh);
void GameWindow_DrawLevelCompleteMode(const GameWindow *pGameWindow, bool fullRefresh);

void GameWindow_ClickPlayMode(GameWindow *pGameWindow, const Point *pPosition);
void GameWindow_ClickLevelCompleteMode(GameWindow *pGameWindow, const Point *pPosition);

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
    
    pGameWindow->GameMode = Play;
    
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

void GameWindow_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    SetPort(pGameWindow->Window);
    
    if (fullRefresh)
    {
        // Fill background
        FillRect(pContentRect, WindowPattern);
    }
    
    switch (pGameWindow->GameMode)
    {
        case Play:
            GameWindow_DrawPlayMode(pGameWindow, fullRefresh);
            break;
        case LevelComplete:
            GameWindow_DrawLevelCompleteMode(pGameWindow, fullRefresh);
            break;
    }
}

void GameWindow_SetLightRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t c, const int8_t r)
{
    pRect->top = pGameWindow->PlayfieldRect.top + PlayfieldPadding + LightMargin + (r * (LightMargin + LightSize));
    pRect->bottom = pRect->top + LightSize;
    pRect->left = pGameWindow->PlayfieldRect.left + PlayfieldPadding + LightMargin + (c * (LightMargin + LightSize));
    pRect->right = pRect->left + LightSize;
}

void GameWindow_DrawPlayMode(const GameWindow *pGameWindow, bool fullRefresh)
{
    int8_t r, c;
    Rect lightRect;
    Str255 levelStr, parStr, movesStr;
    
    SetPort(pGameWindow->Window);
    
    if (fullRefresh)
    {
        // Fill backgrounds
        FillRoundRect(&(pGameWindow->PlayfieldRect), PlayfieldCornerSize, PlayfieldCornerSize, PlayfieldPattern);
        FillRoundRect(&(pGameWindow->HUDRect), HUDCornerSize, HUDCornerSize, HUDPattern);
    }
    
    // Draw Playfield
    
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
    
    // Draw HUD
    
    ForeColor(blackColor);
    TextFace(bold + outline);
    
    // Draw Level
    MoveTo(pGameWindow->HUDRect.left + 10, pGameWindow->HUDRect.top + 20);
    DrawString("\pLevel: ");
    NumToString((long)(pGameWindow->Engine.Level), &levelStr);
    DrawString(levelStr);
    
    // Draw Par
    MoveTo(pGameWindow->HUDRect.left + 10, pGameWindow->HUDRect.top + 40);
    DrawString("\pPar: ");
    NumToString((long)(pGameWindow->Engine.Par), &parStr);
    DrawString(parStr);
    
    // Draw Moves
    MoveTo(pGameWindow->HUDRect.left + 10, pGameWindow->HUDRect.top + 60);
    DrawString("\pMoves: ");
    NumToString((long)(pGameWindow->Engine.Moves), &movesStr);
    DrawString(movesStr);
}

void GameWindow_DrawLevelCompleteMode(const GameWindow *pGameWindow, bool fullRefresh)
{
    SetPort(pGameWindow->Window);
    
    // TODO: Proper level complete
    if (fullRefresh)
    {
    }
    
    MoveTo(100, 100);
    DrawString("\pLevel Complete! Click to continue.");
}

void GameWindow_Show(const GameWindow *pGameWindow)
{
    ShowWindow(pGameWindow->Window);
}

void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    switch (pGameWindow->GameMode)
    {
        case Play:
            GameWindow_ClickPlayMode(pGameWindow, pPosition);
            break;
        case LevelComplete:
            GameWindow_ClickLevelCompleteMode(pGameWindow, pPosition);
            break;
    }
}

void GameWindow_ClickPlayMode(GameWindow *pGameWindow, const Point *pPosition)
{
    int8_t r, c;
    Rect lightRect;
    
    if (PtInRect(*pPosition, &(pGameWindow->PlayfieldRect)))
    {
        // Click within Playfield
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
        
        if (GameEngine_IsCompleted(&(pGameWindow->Engine)))
        {
            // Level was completed in the last click
            pGameWindow->GameMode = LevelComplete;
            GameWindow_Draw(pGameWindow, true);
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->HUDRect)))
    {
        // Click within HUD
    }
}

void GameWindow_ClickLevelCompleteMode(GameWindow *pGameWindow, const Point *pPosition)
{
    // TODO: Proper click handling
    GameEngine_LoadLevel(&(pGameWindow->Engine), pGameWindow->Engine.Level + 1, pGameWindow->Engine.SetB);
    pGameWindow->GameMode = Play;
    GameWindow_Draw(pGameWindow, true);
}
