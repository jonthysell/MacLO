// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef LEVELENDSCENE_H
#define LEVELENDSCENE_H

#include "GameWindow.h"

void LevelEndScene_Init(GameWindow *pGameWindow);
void LevelEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void LevelEndScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
