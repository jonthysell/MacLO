// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "LevelEndScene.h"
#include "GameEndScene.h"

void GameWindow_Init(GameWindow *pGameWindow)
{
    if (pGameWindow->Window != nil)
    {
        ShowError("\pGameWindow already initialized!", false);
    }
    
    pGameWindow->Window = GetNewWindow(BaseResID, nil, MoveToFront);
    
    if (pGameWindow->Window == nil)
    {
        ShowError("\pGameWindow WIND resource missing!", true);
    }
    
    // Load PICT resources
    Bitmaps_Init(&(pGameWindow->Bitmaps));
    
    // Load snd resources
    Sounds_Init(&(pGameWindow->Sounds));
    
    // Initialize window buffer
    WindowBuffer_Init(&(pGameWindow->WindowBuffer), pGameWindow->Window);
    
    // Setup graphics before first draw
    SetPort(pGameWindow->Window);
    FillRect(&(pGameWindow->Window->portRect), WindowPattern);
    
    GameWindow_SetScene(pGameWindow, Title);
}

void GameWindow_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    GrafPtr oldPort;
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    // Save the current port
    GetPort(&oldPort);
    
    WindowBuffer_StartDraw(&(pGameWindow->WindowBuffer));
    
    if (fullRefresh)
    {
        // Fill background
        FillRect(pContentRect, WindowPattern);
    }
    
    switch (pGameWindow->CurrentSceneId)
    {
        case Title:
            TitleScene_Draw(pGameWindow, fullRefresh);
            break;
        case Play:
            PlayScene_Draw(pGameWindow, fullRefresh);
            break;
        case LevelEnd:
            LevelEndScene_Draw(pGameWindow, fullRefresh);
            break;
        case GameEnd:
            GameEndScene_Draw(pGameWindow, fullRefresh);
            break;
    }
    
    WindowBuffer_EndDraw(&(pGameWindow->WindowBuffer));
    
    SetPort(oldPort);
}

void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    switch (pGameWindow->CurrentSceneId)
    {
        case Title:
            TitleScene_Click(pGameWindow, pPosition);
            break;
        case Play:
            PlayScene_Click(pGameWindow, pPosition);
            break;
        case LevelEnd:
            LevelEndScene_Click(pGameWindow, pPosition);
            break;
        case GameEnd:
            GameEndScene_Click(pGameWindow, pPosition);
            break;
    }
}

void GameWindow_SetScene(GameWindow *pGameWindow, const SceneId sceneId)
{
    switch (sceneId)
    {
        case Title:
            TitleScene_Init(pGameWindow);
            break;
        case Play:
            PlayScene_Init(pGameWindow);
            break;
        case LevelEnd:
            LevelEndScene_Init(pGameWindow);
            break;
        case GameEnd:
            GameEndScene_Init(pGameWindow);
            break;
    }
    pGameWindow->CurrentSceneId = sceneId;
    GameWindow_Draw(pGameWindow, true);
}

void GameWindow_Show(const GameWindow *pGameWindow)
{
    ShowWindow(pGameWindow->Window);
}
