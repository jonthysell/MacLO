// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "MacCommon.h"

typedef struct GameWindow
{
	WindowPtr Window;
} GameWindow;

void GameWindow_Init(GameWindow *gameWindow);

#endif
