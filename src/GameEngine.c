// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"
#include "GameEngine.h"

const int8_t PuzzleSize = 5;

const uint8_t MaxStars = 3;
const uint8_t MaxHalfStars = 6;
const uint8_t MinHalfStars = 1;

const uint16_t PerfectScore = 300; // LevelCount * MaxHalfStars

void GameEngine_ToggleSingleLight(GameEngine *pGameEngine, const int8_t x, const int8_t y);

void GameEngine_LoadLevel(GameEngine *pGameEngine, const int8_t level, const bool setB)
{
    pGameEngine->Level = Levels_BoundLevel(level);
    pGameEngine->SetB = setB;
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

uint8_t GameEngine_GetHalfStars(const GameEngine *pGameEngine)
{
    uint8_t halfStarsLost = pGameEngine->Moves <= pGameEngine->Par ? 0 : max(0, (1 + pGameEngine->Moves - pGameEngine->Par) / 2);
    return max(MinHalfStars, MaxHalfStars - halfStarsLost);
}

void GameEngine_ToggleLights(GameEngine *pGameEngine, const int8_t x, const int8_t y)
{
    int8_t targetX = max(0, min(x, PuzzleSize - 1));
    int8_t targetY = max(0, min(y, PuzzleSize - 1));
    
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
