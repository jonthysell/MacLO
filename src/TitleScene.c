// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file TitleScene.c
 *
 * This file provides implementations for TitleScene.h.
 */

#include "TitleScene.h"
#include "Bitmaps.h"

/** Scale factor for the text. */
#define TitleTextScale 2

void TitleScene_Init(GameWindow *pGameWindow)
{
    Rect r;
    
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    // Setup Title
    GetPictureRect(pGameWindow->Bitmaps.TitlePict, &(pGameWindow->TitleScene.TitleRect));
    GetBoxRect(pContentRect, Center, &r);
    GetBoxRect(&r, Top, &r);
    CenterRect(&r, &(pGameWindow->TitleScene.TitleRect));
    
    // Setup Set A
    GetScaledPicFrame(pGameWindow->Bitmaps.ACharPict, TitleTextScale, &(pGameWindow->TitleScene.SetARect));
    GetBoxRect(pContentRect, BottomLeft, &r);
    CenterRect(&r, &(pGameWindow->TitleScene.SetARect));
    
    // Setup Set B
    GetScaledPicFrame(pGameWindow->Bitmaps.BCharPict, TitleTextScale, &(pGameWindow->TitleScene.SetBRect));
    GetBoxRect(pContentRect, BottomRight, &r);
    CenterRect(&r, &(pGameWindow->TitleScene.SetBRect));
    
    // Setup sound button
    Bitmaps_GetSoundRect(&(pGameWindow->Bitmaps), TitleTextScale, &(pGameWindow->TitleScene.SoundButtonRect));
    GetBoxRect(pContentRect, Bottom, &r);
    CenterRect(&r, &(pGameWindow->TitleScene.SoundButtonRect));
}

void TitleScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    // Draw Title
    if (fullRefresh)
    {
        DrawPicture(pGameWindow->Bitmaps.TitlePict, &(pGameWindow->TitleScene.TitleRect));
    }
    
    // Draw Set A
    if (fullRefresh)
    {
        MoveTo(pGameWindow->TitleScene.SetARect.left, pGameWindow->TitleScene.SetARect.top);
        Bitmaps_DrawAChar(&(pGameWindow->Bitmaps), TitleTextScale);
    }
    
    // Draw Set B
    if (fullRefresh)
    {
        MoveTo(pGameWindow->TitleScene.SetBRect.left, pGameWindow->TitleScene.SetBRect.top);
        Bitmaps_DrawBChar(&(pGameWindow->Bitmaps), TitleTextScale);
    }
    
    // Draw sound button
    MoveTo(pGameWindow->TitleScene.SoundButtonRect.left, pGameWindow->TitleScene.SoundButtonRect.top);
    Bitmaps_DrawSound(&(pGameWindow->Bitmaps), pGameWindow->Sounds.Enabled, TitleTextScale);
}

void TitleScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SetARect)))
    {
        // Click on Set A button
        GameEngine_NewGame(&(pGameWindow->Engine), false);
        if (GameEngine_HasPlayedLevel(&(pGameWindow->Engine), 0))
        {
            // Not first time, go to level select
            GameWindow_SetScene(pGameWindow, LevelSelect);
        }
        else
        {
            // First time, go straight to play scene
            GameWindow_SetScene(pGameWindow, Play);
            Sounds_PlayRetrySnd(&(pGameWindow->Sounds));
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SetBRect)))
    {
        // Click on Set B button
        GameEngine_NewGame(&(pGameWindow->Engine), true);
        if (GameEngine_HasPlayedLevel(&(pGameWindow->Engine), 0))
        {
            // Not first time, go to level select
            GameWindow_SetScene(pGameWindow, LevelSelect);
        }
        else
        {
            // First time, go straight to play scene
            GameWindow_SetScene(pGameWindow, Play);
            Sounds_PlayRetrySnd(&(pGameWindow->Sounds));
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->TitleScene.SoundButtonRect)))
    {
        // Click on sound button
        GameWindow_ToggleSound(pGameWindow);
    }
}
