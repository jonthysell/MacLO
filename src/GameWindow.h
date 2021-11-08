// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "MacCommon.h"
#include "GameEngine.h"
#include "Bitmaps.h"
#include "Scenes.h"

#define WindowPattern  black

typedef struct sGameWindow
{
    WindowPtr     Window;
    GameEngine    Engine;
    Bitmaps       Bitmaps;
    SceneId       CurrentSceneId;
    TitleScene    TitleScene;
    PlayScene     PlayScene;
    LevelEndScene LevelEndScene;
    GameEndScene  GameEndScene;
} GameWindow;

void GameWindow_Init(GameWindow *pGameWindow);
void GameWindow_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition);

void GameWindow_SetScene(GameWindow *pGameWindow, const SceneId sceneId);
void GameWindow_Show(const GameWindow *pGameWindow);

#endif
