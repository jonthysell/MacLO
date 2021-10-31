// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "LevelEndScene.h"

void LevelEndScene_Init(GameWindow *pGameWindow)
{
}

void LevelEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    Str255 halfStarsStr;
    
    SetPort(pGameWindow->Window);
    
    // TODO: Proper level end
    if (fullRefresh)
    {
    }
    
    MoveTo(100, 100);
    DrawString("\pLevel complete! Click to continue.");
    
    MoveTo(100, 125);
    DrawString("\pReceived ");
    NumToString((long)GameEngine_GetHalfStars(&(pGameWindow->Engine)), &halfStarsStr);
    DrawString(halfStarsStr);
    DrawString("\p/6 half-stars.");
    
    MoveTo(100, 200);
    DrawString("\pRetry level.");
    
    MoveTo(350, 200);
    DrawString("\pNext level.");
}

void LevelEndScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    // TODO: Proper click handling
    
    if (pPosition->h < ((pGameWindow->Window->portRect.right - pGameWindow->Window->portRect.left) / 2))
    {
        GameEngine_ResetLevel(&(pGameWindow->Engine));
    }
    else
    {
        GameEngine_NextLevel(&(pGameWindow->Engine));
    }
    
    GameWindow_SetScene(pGameWindow, GameEngine_IsGameOver(&(pGameWindow->Engine)) ? GameEnd : Play);
}
