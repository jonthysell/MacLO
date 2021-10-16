// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "MacCommon.h"
#include "GameEngine.h"

typedef struct GameWindow
{
    WindowPtr Window;
    GameEngine Engine;
} GameWindow;

void GameWindow_Init(GameWindow *pGameWindow);
void GameWindow_Draw(GameWindow *pGameWindow);
void GameWindow_Show(GameWindow *pGameWindow);

#endif
