// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameEndScene.h
 *
 * This file provides the functions to initialize, draw, and respond to
 * clicks when the GameWindow is set to the LevelSelect scene.
 */

#ifndef GAMEENDSCENE_H
#define GAMEENDSCENE_H

#include "GameWindow.h"

/**
 * Initializes the GameEnd scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 */
void GameEndScene_Init(GameWindow *pGameWindow);

/**
 * Draws the GameEnd scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param fullRefresh Whether or not the whole scene needs to be redrawn.
 */
void GameEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);

/**
 * Handles clicks on the GameEnd scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param pPosition The local position where the click occured.
 */
void GameEndScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
