// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"
#include "GameEngine.h"

const int8_t PuzzleSize = 5;

const uint8_t MaxStars = 3;
const uint8_t MaxHalfStars = 6;
const uint8_t MinHalfStars = 1;

const uint16_t PerfectScore = 300; // LevelCount * MaxHalfStars

void GameEngine_LoadLevel(GameEngine *pGameEngine, const int8_t level, const bool setB);
uint8_t GameEngine_CalculateHalfStars(const uint16_t par, const uint16_t moves);
void GameEngine_ToggleSingleLight(GameEngine *pGameEngine, const int8_t x, const int8_t y);

void GameEngine_NewGame(GameEngine *pGameEngine, const bool setB)
{
    pGameEngine->Score = 0;
    GameEngine_LoadLevel(pGameEngine, 0, setB);
}

void GameEngine_NextLevel(GameEngine *pGameEngine)
{
    if (GameEngine_IsCompleted(pGameEngine))
    {
        pGameEngine->Score += GameEngine_GetHalfStars(pGameEngine);
        GameEngine_LoadLevel(pGameEngine, pGameEngine->Level + 1, pGameEngine->SetB);
    }
}

void GameEngine_ResetLevel(GameEngine *pGameEngine)
{
    GameEngine_LoadLevel(pGameEngine, pGameEngine->Level, pGameEngine->SetB);
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
