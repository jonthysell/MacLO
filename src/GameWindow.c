// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"

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
    
    GameEngine_LoadLevel(&(pGameWindow->Engine), 0, false);
    
    CenterWindow(pGameWindow->Window);
}

void GameWindow_Draw(GameWindow *pGameWindow)
{
    SetPort(pGameWindow->Window);
    
    MoveTo(10, 20);
    DrawString("\pHello MacLO");
}

void GameWindow_Show(GameWindow *pGameWindow)
{
    ShowWindow(pGameWindow->Window);
}
