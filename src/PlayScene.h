// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file PlayScene.h
 *
 * This file provides the functions to initialize, draw, and respond to
 * clicks when the GameWindow is set to the Play scene.
 */

#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "GameWindow.h"

/**
 * Initializes the Play scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 */
void PlayScene_Init(GameWindow *pGameWindow);

/**
 * Draws the Play scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param fullRefresh Whether or not the whole scene needs to be redrawn.
 */
void PlayScene_Draw(const GameWindow *pGameWindow, bool fullRefresh);

/**
 * Handles clicks on the Play scene for the given GameWindow.
 * @param pGameWindow The GameWindow.
 * @param pPosition The local position where the click occured.
 */
void PlayScene_Click(GameWindow *pGameWindow, const Point *pPosition);

#endif
