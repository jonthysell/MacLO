// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameWindow.c
 *
 * This file provides implementations for GameWindow.h.
 */

#include "GameWindow.h"
#include "TitleScene.h"
#include "LevelSelectScene.h"
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
    
    // Initialize window buffer
    WindowBuffer_Init(&(pGameWindow->WindowBuffer), pGameWindow->Window);
    
    // Initialize game engine
    GameEngine_Init(&(pGameWindow->Engine));
    
    // Initialize game save
    GameSave_Init(&(pGameWindow->GameSave));
    
    // Load PICT resources
    Bitmaps_Init(&(pGameWindow->Bitmaps));
    
    // Load snd resources
    Sounds_Init(&(pGameWindow->Sounds));
    
    // Setup graphics before first draw
    SetPort(pGameWindow->Window);
    FillRect(&(pGameWindow->Window->portRect), WindowPattern);
    
    // Load data from saved game
    GameSave_LoadData(&(pGameWindow->GameSave), &(pGameWindow->Engine));
    
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
        case LevelSelect:
            LevelSelectScene_Draw(pGameWindow, fullRefresh);
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
        case LevelSelect:
            LevelSelectScene_Click(pGameWindow, pPosition);
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
        case LevelSelect:
            LevelSelectScene_Init(pGameWindow);
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
    GameWindow_Draw(pGameWindow, true); // Always force a full refresh when changing scenes
}

void GameWindow_Show(const GameWindow *pGameWindow)
{
    ShowWindow(pGameWindow->Window);
}

void GameWindow_ClearScores(GameWindow *pGameWindow)
{
    if (ShowConfirm("\pAre you sure you want to clear all scores?"))
    {
        GameEngine_ResetGame(&(pGameWindow->Engine));
        GameSave_SaveData(&(pGameWindow->GameSave), &(pGameWindow->Engine));
        GameWindow_SetScene(pGameWindow, Title);
    }
}
