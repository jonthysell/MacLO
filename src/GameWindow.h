// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "MacCommon.h"
#include "GameEngine.h"

#define PlayfieldMargin 5
#define LightMargin     10
#define LightSize       50
#define LightCornerSize 10

typedef struct GameWindow
{
    WindowPtr  Window;
    GameEngine Engine;
    Rect       PlayfieldRect;
} GameWindow;

void GameWindow_Init(GameWindow *pGameWindow);

void GameWindow_Draw(const GameWindow *pGameWindow, Boolean fullRefresh);
void GameWindow_Show(const GameWindow *pGameWindow);

void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
