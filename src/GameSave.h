// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameSave.h
 *
 * This file provides a GameSave type which manages saving scores to disk.
 */

#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "GameEngine.h"

/** Struct containing handle to the save resource. */
typedef struct sGameSave
{
    Handle Save;
} GameSave;

/**
 * Initializes the GameSave.
 * @param pGameSave The GameSave.
 */
void GameSave_Init(GameSave *pSaveGame);

/**
 * Loads data from the GameSave into the GameEngine.
 * @param pGameSave The GameSave.
 * @param pGameEngine The GameEngine.
 */
void GameSave_LoadData(const GameSave *pSaveGame, GameEngine *pGameEngine);

/**
 * Saves data from the GameEngine into the GameSave.
 * @param pGameSave The GameSave.
 * @param pGameEngine The GameEngine.
 */
void GameSave_SaveData(GameSave *pSaveGame, const GameEngine *pGameEngine);

#endif
