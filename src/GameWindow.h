// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "MacCommon.h"
#include "GameEngine.h"
#include "Scenes.h"

#define WindowPattern black

typedef struct GameWindow
{
    WindowPtr  Window;
    GameEngine Engine;
    SceneId    CurrentSceneId;
    bool       SceneIsInitialized[NumScenes];
    TitleScene TitleScene;
    PlayScene  PlayScene;
} GameWindow;

void GameWindow_Init(GameWindow *pGameWindow);
void GameWindow_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition);

void GameWindow_SetScene(GameWindow *pGameWindow, const SceneId sceneId);
void GameWindow_Show(const GameWindow *pGameWindow);

#endif
