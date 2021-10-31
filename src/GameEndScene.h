// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEENDSCENE_H
#define GAMEENDSCENE_H

#include "GameWindow.h"

void GameEndScene_Init(GameWindow *pGameWindow);
void GameEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void GameEndScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
