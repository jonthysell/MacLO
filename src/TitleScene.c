// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "TitleScene.h"
#include "Bitmaps.h"

#define TitleTextScale 2

void TitleScene_Init(GameWindow *pGameWindow)
{
    Rect r;
    
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    // Setup Title
    GetPictureRect(pGameWindow->Bitmaps.TitlePict, &(pGameWindow->TitleScene.TitleRect));
    CenterRect(pContentRect, &(pGameWindow->TitleScene.TitleRect));
    
    // Setup Set A
    GetScaledPicFrame(pGameWindow->Bitmaps.ACharPict, TitleTextScale, &(pGameWindow->TitleScene.SetARect));
    GetBoxRect(pContentRect, BottomLeft, &r);
    CenterRect(&r, &(pGameWindow->TitleScene.SetARect));
    
    // Setup Set B
    GetScaledPicFrame(pGameWindow->Bitmaps.BCharPict, TitleTextScale, &(pGameWindow->TitleScene.SetBRect));
    GetBoxRect(pContentRect, BottomRight, &r);
    CenterRect(&r, &(pGameWindow->TitleScene.SetBRect));
    
    // Setup sound button
    Bitmaps_GetSoundRect(&(pGameWindow->Bitmaps), pGameWindow->Sounds.Enabled, TitleTextScale, &(pGameWindow->TitleScene.SoundButtonRect));
    GetBoxRect(pContentRect, Bottom, &r);
    CenterRect(&r, &(pGameWindow->TitleScene.SoundButtonRect));
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
    
    // Draw sound button
    MoveTo(pGameWindow->TitleScene.SoundButtonRect.left, pGameWindow->TitleScene.SoundButtonRect.top);
    Bitmaps_DrawSound(&(pGameWindow->Bitmaps), pGameWindow->Sounds.Enabled, TitleTextScale);
}

void TitleScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SetARect)))
    {
        Sounds_PlayClickSnd(&(pGameWindow->Sounds));
        GameEngine_NewGame(&(pGameWindow->Engine), false);
        GameWindow_SetScene(pGameWindow, Play);
    }
    else if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SetBRect)))
    {
        Sounds_PlayClickSnd(&(pGameWindow->Sounds));
        GameEngine_NewGame(&(pGameWindow->Engine), true);
        GameWindow_SetScene(pGameWindow, Play);
    }
    else if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SoundButtonRect)))
    {
        pGameWindow->Sounds.Enabled = !pGameWindow->Sounds.Enabled;
        GameWindow_Draw(pGameWindow, false);
    }
}
