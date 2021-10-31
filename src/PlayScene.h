// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "GameWindow.h"

void PlayScene_Init(GameWindow *pGameWindow);
void PlayScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void PlayScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
