// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef LEVELSELECTSCENE_H
#define LEVELSELECTSCENE_H

#include "GameWindow.h"

void LevelSelectScene_Init(GameWindow *pGameWindow);
void LevelSelectScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void LevelSelectScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
