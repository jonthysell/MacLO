// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameEngine.c
 *
 * This file provides implementations for GameEngine.h.
 */

#include "Common.h"
#include "GameEngine.h"

const int8_t PuzzleSize = 5;

const uint8_t MaxStars = 3;
const uint8_t MaxHalfStars = 6;
const uint8_t MinHalfStars = 1;

const uint16_t PerfectScore = 300; // LevelCount * MaxHalfStars

/**
 * Loads the given level as the current level.
 * @param level The level.
 * @param setB The set.
 */
void GameEngine_LoadLevel(GameEngine *pGameEngine, const int8_t level, const bool setB);

/**
 * Gets the number of half-stars to award given the par for the level, and the
 * number of moves already taken.
 * @param par The par for the level.
 * @param moves The number of moves.
 * @return The number of half-stars.
 */
uint8_t GameEngine_CalculateHalfStars(const uint16_t par, const uint16_t moves);

/**
 * Toggles the single light at the given coordinates.
 * @param pGameEngine The GameEngine.
 * @param x The x coordinate of the light.
 * @param y The y coordinate of the light.
 */
void GameEngine_ToggleSingleLight(GameEngine *pGameEngine, const int8_t x, const int8_t y);

void GameEngine_Init(GameEngine *pGameEngine)
{
    int8_t level;
    
    for (level = 0; level < LevelCount; level++)
    {
        pGameEngine->ScoresA[level] = 0;
        pGameEngine->ScoresB[level] = 0;
    }
    
    pGameEngine->Level = -1;
    pGameEngine->SetB = false;
    pGameEngine->PreviousLights = 0;
    pGameEngine->Lights = 0;
    pGameEngine->Par = 0;
    pGameEngine->Moves = 0;
}

void GameEngine_NewGame(GameEngine *pGameEngine, const bool setB)
{
    int8_t level, startLevel;
    
    pGameEngine->SetB = setB;
    
    startLevel = 0;
    for (level = 0; level < LevelCount; level++)
    {
        // Find the first uncompleted level
        if (GameEngine_GetScore(pGameEngine, level) == 0)
        {
            startLevel = level;
            break;
        }
    }
    
    GameEngine_StartLevel(pGameEngine, startLevel);
}

void GameEngine_ResetGame(GameEngine *pGameEngine)
{
    int8_t level;
    
    for (level = 0; level < LevelCount; level++)
    {
        pGameEngine->ScoresA[level] = 0;
        pGameEngine->ScoresB[level] = 0;
    }
}

void GameEngine_StartLevel(GameEngine *pGameEngine, const int8_t level)
{
    GameEngine_LoadLevel(pGameEngine, level, pGameEngine->SetB);
}

void GameEngine_CompleteLevel(GameEngine *pGameEngine)
{
    if (GameEngine_IsCompleted(pGameEngine))
    {
        if (pGameEngine->SetB)
        {
            pGameEngine->ScoresB[pGameEngine->Level] = max(GameEngine_GetHalfStars(pGameEngine), pGameEngine->ScoresB[pGameEngine->Level]);
        }
        else
        {
            pGameEngine->ScoresA[pGameEngine->Level] = max(GameEngine_GetHalfStars(pGameEngine), pGameEngine->ScoresA[pGameEngine->Level]);
        }
    }
}

void GameEngine_NextLevel(GameEngine *pGameEngine)
{
    if (GameEngine_IsCompleted(pGameEngine))
    {
        GameEngine_StartLevel(pGameEngine, pGameEngine->Level + 1);
    }
}

void GameEngine_ResetLevel(GameEngine *pGameEngine)
{
    GameEngine_StartLevel(pGameEngine, pGameEngine->Level);
}

void GameEngine_LoadLevel(GameEngine *pGameEngine, const int8_t level, const bool setB)
{
    pGameEngine->Level = level;
    pGameEngine->SetB = setB;
    pGameEngine->PreviousLights = pGameEngine->Lights;
    pGameEngine->Lights = Levels_GetLightsForLevel(pGameEngine->Level, setB);
    pGameEngine->Par = Levels_GetParForLevel(pGameEngine->Level);
    pGameEngine->Moves = 0;
}

bool GameEngine_GetLight(const GameEngine *pGameEngine, const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PuzzleSize && y >= 0 && y < PuzzleSize)
    {
        return bitRead(pGameEngine->Lights, y * PuzzleSize + x);
    }

    return false;
}

bool GameEngine_IsEnabled(const GameEngine *pGameEngine, const int8_t level)
{
    return level == 0 || (level < LevelCount && GameEngine_GetScore(pGameEngine, level - 1) > 0);
}

bool GameEngine_IsCompleted(const GameEngine *pGameEngine)
{
    return pGameEngine->Lights == 0;
}

bool GameEngine_IsGameOver(const GameEngine *pGameEngine)
{
    return pGameEngine->Level >= LevelCount;
}

uint8_t GameEngine_GetHalfStars(const GameEngine *pGameEngine)
{
    return GameEngine_CalculateHalfStars(pGameEngine->Par, pGameEngine->Moves);
}

uint8_t GameEngine_GetScore(const GameEngine *pGameEngine, const int8_t level)
{
    return pGameEngine->SetB ? pGameEngine->ScoresB[level] : pGameEngine->ScoresA[level];
}

uint16_t GameEngine_GetTotalScore(const GameEngine *pGameEngine)
{
    uint8_t level;
    uint16_t score;
    
    score = 0;
    for (level = 0; level < LevelCount; level++)
    {
        score += GameEngine_GetScore(pGameEngine, level);
    }
    
    return score;
}

uint8_t GameEngine_CalculateHalfStars(const uint16_t par, const uint16_t moves)
{
    uint8_t halfStarsLost = moves <= par ? 0 : max(0, (1 + moves - par) / 2);
    return max(MinHalfStars, MaxHalfStars - halfStarsLost);
}

void GameEngine_ToggleLights(GameEngine *pGameEngine, const int8_t x, const int8_t y)
{
    int8_t targetX = max(0, min(x, PuzzleSize - 1));
    int8_t targetY = max(0, min(y, PuzzleSize - 1));
    
    pGameEngine->PreviousLights = pGameEngine->Lights;
    
    GameEngine_ToggleSingleLight(pGameEngine, targetX, targetY);
    GameEngine_ToggleSingleLight(pGameEngine, targetX + 1, targetY);
    GameEngine_ToggleSingleLight(pGameEngine, targetX, targetY + 1);
    GameEngine_ToggleSingleLight(pGameEngine, targetX - 1, targetY);
    GameEngine_ToggleSingleLight(pGameEngine, targetX, targetY - 1);
    
    pGameEngine->Moves++;    
}

void GameEngine_ToggleSingleLight(GameEngine *pGameEngine, const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PuzzleSize && y >= 0 && y < PuzzleSize)
    {
        bitToggle(pGameEngine->Lights, y * PuzzleSize + x);
    }
}

bool GameEngine_LightChanged(const GameEngine *pGameEngine, const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PuzzleSize && y >= 0 && y < PuzzleSize)
    {
        return bitRead(pGameEngine->Lights, y * PuzzleSize + x) != bitRead(pGameEngine->PreviousLights, y * PuzzleSize + x);
    }
    
    return false;
}

bool GameEngine_HalfStarsChanged(const GameEngine *pGameEngine)
{
    return pGameEngine->Moves == 0 ||
        GameEngine_CalculateHalfStars(pGameEngine->Par, pGameEngine->Moves - 1) != GameEngine_GetHalfStars(pGameEngine);
}
