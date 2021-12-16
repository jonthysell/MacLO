// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameEngine.h
 *
 * This file provides the GameEngine type, which manages the the game of
 * Light Out, including current level information and the user's progress.
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Levels.h"

/** The size (width and height) of a puzzle. */
extern const int8_t PuzzleSize;

/** The max number of full stars for completing a puzzle. */
extern const uint8_t MaxStars;

/** The max number of half-stars for completing a puzzle. */
extern const uint8_t MaxHalfStars;

/** The min number of half-stars for completing a puzzle. */
extern const uint8_t MinHalfStars;

/** The max number of half-stars for completing every puzzle in a set. */
extern const uint16_t PerfectScore;

/** Struct containing all the data needed for a game. */
typedef struct GameEngine
{
    uint8_t  ScoresA[LevelCount];
    uint8_t  ScoresB[LevelCount];
    int8_t   Level;
    bool     SetB;
    uint32_t Lights;
    uint32_t PreviousLights;
    uint16_t Par;
    uint16_t Moves;
} GameEngine;

/**
 * Initializes the GameEngine.
 * @param pGameEngine The GameEngine.
 */
void GameEngine_Init(GameEngine *pGameEngine);

/**
 * Starts a new game, selecting the first unfinshed level in the set.
 * @param pGameEngine The GameEngine.
 * @param setB The set.
 */
void GameEngine_NewGame(GameEngine *pGameEngine, const bool setB);

/**
 * Resets the scores for all levels to zero.
 * @param pGameEngine The GameEngine.
 */
void GameEngine_ResetGame(GameEngine *pGameEngine);

/**
 * Starts the given level.
 * @param pGameEngine The GameEngine.
 * @param level The level to start.
 */
void GameEngine_StartLevel(GameEngine *pGameEngine, const int8_t level);

/**
 * Marks the current level as complete, saving the score.
 * @param pGameEngine The GameEngine.
 */
void GameEngine_CompleteLevel(GameEngine *pGameEngine);

/**
 * Advances the game to the next level in the set.
 * @param pGameEngine The GameEngine.
 */
void GameEngine_NextLevel(GameEngine *pGameEngine);

/**
 * Resets the current level to its initial state.
 * @param pGameEngine The GameEngine.
 */
void GameEngine_ResetLevel(GameEngine *pGameEngine);

/**
 * Gets the state of the light at the given coordinates.
 * @param pGameEngine The GameEngine.
 * @param x The x coordinate of the light.
 * @param y The y coordinate of the light.
 * @return Whether the light is on or not.
 */
bool GameEngine_GetLight(const GameEngine *pGameEngine, const int8_t x, const int8_t y);

/**
 * Gets whether the current level has been completed.
 * @param pGameEngine The GameEngine.
 * @return Whether all of the lights are off.
 */
bool GameEngine_IsCompleted(const GameEngine *pGameEngine);

/**
 * Gets whether or not the given level can be played.
 * @param pGameEngine The GameEngine.
 * @param level The level.
 * @return Whether the level can be played.
 */
bool GameEngine_IsEnabled(const GameEngine *pGameEngine, const int8_t level);

/**
 * Gets whether the current level is the last of a set.
 * @param pGameEngine The GameEngine.
 * @return Whether the current level is the last of a set.
 */
bool GameEngine_IsLastLevel(const GameEngine *pGameEngine);

/**
 * Gets whether the given level has been completed before.
 * @param pGameEngine The GameEngine.
 * @param level The level.
 * @return Whether the given level has been completed before.
 */
bool GameEngine_HasPlayedLevel(const GameEngine *pGameEngine, const int8_t level);

/**
 * Gets the number of half-stars the user stands to earn given the current
 * state of the level they're trying to solve.
 * @param pGameEngine The GameEngine.
 * @return The number of half-stars.
 */
uint8_t GameEngine_GetHalfStars(const GameEngine *pGameEngine);

/**
 * Gets the number of half-stars the user won for a given level.
 * @param pGameEngine The GameEngine.
 * @param level The level.
 * @return The number of half-stars won.
 */
uint8_t GameEngine_GetScore(const GameEngine *pGameEngine, const int8_t level);

/**
 * Gets the total number of half-stars the user has won across the set.
 * @param pGameEngine The GameEngine.
 * @return The total number of half-stars won.
 */
uint16_t GameEngine_GetTotalScore(const GameEngine *pGameEngine);

/**
 * Toggles the lights centered at the given coordinates.
 * @param pGameEngine The GameEngine.
 * @param x The x coordinate of the center light.
 * @param y The y coordinate of the center light.
 */
void GameEngine_ToggleLights(GameEngine *pGameEngine, const int8_t x, const int8_t y);

/**
 * Gets whether the given light changed after the last toggle.
 * @param pGameEngine The GameEngine.
 * @param x The x coordinate of the light.
 * @param y The y coordinate of the light.
 * @return Whether the light changed.
 */
bool GameEngine_LightChanged(const GameEngine *pGameEngine, const int8_t x, const int8_t y);

/**
 * Gets whether the number of half-stars changed after the last toggle.
 * @param pGameEngine The GameEngine.
 * @return Whether the number of half-stars changed.
 */
bool GameEngine_HalfStarsChanged(const GameEngine *pGameEngine);

#endif
