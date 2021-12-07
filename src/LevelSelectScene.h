// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file LevelSelectScene.h
 *
 * This file provides the functions to initialize, draw, and respond to
 * clicks when the GameWindow is set to the LevelSelect scene.
 */

#ifndef LEVELSELECTSCENE_H
#define LEVELSELECTSCENE_H

#include "GameWindow.h"

/**
 * Initializes the LevelSelect scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 */
void LevelSelectScene_Init(GameWindow *pGameWindow);

/**
 * Draws the LevelSelect scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param fullRefresh Whether or not the whole scene needs to be redrawn.
 */
void LevelSelectScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);

/**
 * Handles clicks on the LevelSelect scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param pPosition The local position where the click occured.
 */
void LevelSelectScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
