// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "TitleScene.h"

#define TitlePictResID BaseResID

void TitleScene_Init(GameWindow *pGameWindow)
{
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    pGameWindow->TitleScene.TitlePict = GetPicture(TitlePictResID);
    
    if (pGameWindow->TitleScene.TitlePict == nil)
    {
        ShowError("\pTitle PICT resource missing!", true);
    }
    
    // Setup rects
    pGameWindow->TitleScene.TitleRect = (**(pGameWindow->TitleScene.TitlePict)).picFrame;
    CenterRect(pContentRect, &(pGameWindow->TitleScene.TitleRect));
}

void TitleScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    SetPort(pGameWindow->Window);
    
    // TODO: Proper title
    if (fullRefresh)
    {
    }
    
    // Draw Title PICT
    DrawPicture(pGameWindow->TitleScene.TitlePict, &(pGameWindow->TitleScene.TitleRect));
    
    ForeColor(blackColor);
    TextFace(bold + outline);
    
    MoveTo(100, pGameWindow->TitleScene.TitleRect.bottom + 30);
    DrawString("\pSet A");
    
    MoveTo(350, pGameWindow->TitleScene.TitleRect.bottom + 30);
    DrawString("\pSet B");
}

void TitleScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    bool setB;
    
    // TODO: Proper click handling
    
    if (pPosition->h < ((pGameWindow->Window->portRect.right - pGameWindow->Window->portRect.left) / 2))
    {
        setB = false;
    }
    else
    {
        setB = true;
    }

    GameEngine_NewGame(&(pGameWindow->Engine), setB);
    
    GameWindow_SetScene(pGameWindow, Play);
}
