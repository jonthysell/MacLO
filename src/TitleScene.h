// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "GameWindow.h"

void TitleScene_Init(GameWindow *pGameWindow);
void TitleScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);
void TitleScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
