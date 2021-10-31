// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameEndScene.h"

void GameEndScene_Init(GameWindow *pGameWindow)
{
}

void GameEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    Str255 scoreStr;
    
    SetPort(pGameWindow->Window);
    
    // TODO: Proper level end
    if (fullRefresh)
    {
    }
    
    MoveTo(100, 100);
    DrawString("\pGame complete! Click to continue.");
    
    MoveTo(100, 125);
    DrawString("\pScore: ");
    NumToString((long)(pGameWindow->Engine.Score), &scoreStr);
    DrawString(scoreStr);
    DrawString("\p/300");
}

void GameEndScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    // TODO: Proper click handling
    
    GameWindow_SetScene(pGameWindow, Title);
}
