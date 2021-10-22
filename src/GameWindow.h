// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "MacCommon.h"
#include "GameEngine.h"

#define WindowPattern       black

#define PlayfieldMargin     4
#define PlayfieldPadding    2
#define PlayfieldCornerSize 12
#define LightMargin         6
#define LightSize           50
#define LightCornerSize     8
#define PlayfieldPattern    ltGray

#define HUDMargin     PlayfieldMargin
#define HUDCornerSize PlayfieldCornerSize
#define HUDPattern    PlayfieldPattern

typedef enum GameMode
{
    Play,
    LevelComplete,
    GameComplete
} GameMode;

typedef struct GameWindow
{
    WindowPtr  Window;
    GameEngine Engine;
    GameMode   GameMode;
    Rect       PlayfieldRect;
    Rect       HUDRect;
} GameWindow;

void GameWindow_Init(GameWindow *pGameWindow);

void GameWindow_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void GameWindow_Show(const GameWindow *pGameWindow);

void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
