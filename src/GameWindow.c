// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"

void GameWindow_Init(GameWindow *gameWindow)
{
    if (gameWindow->Window != nil)
    {
        ShowError("\pGameWindow already initialized!", false);
    }
    
    gameWindow->Window = GetNewWindow(kBaseResID, nil, kMoveToFront);
    
    if (gameWindow->Window == nil)
    {
        ShowError("\pGameWindow resource WIND kBaseResID missing!", true);
    }
    
    CenterWindow(gameWindow->Window);
    
    ShowWindow(gameWindow->Window);
    SetPort(gameWindow->Window);
    
    MoveTo(10, 20);
    DrawString("\pHello MacLO");
}


