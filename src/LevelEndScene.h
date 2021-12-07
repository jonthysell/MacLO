// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file LevelEndScene.h
 *
 * This file provides the functions to initialize, draw, and respond to
 * clicks when the GameWindow is set to the LevelEnd scene.
 */

#ifndef LEVELENDSCENE_H
#define LEVELENDSCENE_H

#include "GameWindow.h"

/**
 * Initializes the LevelEnd scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 */
void LevelEndScene_Init(GameWindow *pGameWindow);

/**
 * Draws the LevelEnd scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param fullRefresh Whether or not the whole scene needs to be redrawn.
 */
void LevelEndScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);

/**
 * Handles clicks on the LevelEnd scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param pPosition The local position where the click occured.
 */
void LevelEndScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
