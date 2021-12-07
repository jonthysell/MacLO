// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file TitleScene.h
 *
 * This file provides the functions to initialize, draw, and respond to
 * clicks when the GameWindow is set to the Title scene.
 */

#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "GameWindow.h"

/**
 * Initializes the Title scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 */
void TitleScene_Init(GameWindow *pGameWindow);

/**
 * Draws the Title scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param fullRefresh Whether or not the whole scene needs to be redrawn.
 */
void TitleScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);

/**
 * Handles clicks on the Title scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param pPosition The local position where the click occured.
 */
void TitleScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
