// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "TitleScene.h"
#include "Bitmaps.h"

#define TitleTextScale 2

void TitleScene_Init(GameWindow *pGameWindow)
{
    Rect r;
    
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    // Setup rects
    GetPictureRect(pGameWindow->Bitmaps.TitlePict, &(pGameWindow->TitleScene.TitleRect));
    CenterRect(pContentRect, &(pGameWindow->TitleScene.TitleRect));
    
    GetBoxRect(pContentRect, BottomLeft, &r);
    GetScaledPicFrame(pGameWindow->Bitmaps.ACharPict, TitleTextScale, &(pGameWindow->TitleScene.SetARect));
    CenterRect(&r, &(pGameWindow->TitleScene.SetARect));
    
    GetBoxRect(pContentRect, BottomRight, &r);
    GetScaledPicFrame(pGameWindow->Bitmaps.BCharPict, TitleTextScale, &(pGameWindow->TitleScene.SetBRect));
    CenterRect(&r, &(pGameWindow->TitleScene.SetBRect));
}

void TitleScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    // Draw Title
    DrawPicture(pGameWindow->Bitmaps.TitlePict, &(pGameWindow->TitleScene.TitleRect));
    
    // Draw Set A
    MoveTo(pGameWindow->TitleScene.SetARect.left, pGameWindow->TitleScene.SetARect.top);
    Bitmaps_DrawAChar(&(pGameWindow->Bitmaps), TitleTextScale);
    
    // Draw Set B
    MoveTo(pGameWindow->TitleScene.SetBRect.left, pGameWindow->TitleScene.SetBRect.top);
    Bitmaps_DrawBChar(&(pGameWindow->Bitmaps), TitleTextScale);
}

void TitleScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SetARect)))
    {
        GameEngine_NewGame(&(pGameWindow->Engine), false);
        GameWindow_SetScene(pGameWindow, Play);
    }
    else if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SetBRect)))
    {
        GameEngine_NewGame(&(pGameWindow->Engine), true);
        GameWindow_SetScene(pGameWindow, Play);
    }
}
