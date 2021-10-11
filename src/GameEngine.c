// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"
#include "GameEngine.h"

const int8_t PuzzleSize = 5;

const uint8_t MaxStars = 3;
const uint8_t MaxHalfStars = 6;
const uint8_t MinHalfStars = 1;

const uint16_t PerfectScore = 300; // LevelCount * MaxHalfStars

void GameEngine_LoadLevel(GameEngine *engine, const int8_t level, const bool setB)
{
    engine->Level = Levels_BoundLevel(level);
    engine->Lights = Levels_GetLightsForLevel(engine->Level, setB);
    engine->Par = Levels_GetParForLevel(engine->Level);
    engine->Moves = 0;
}

bool GameEngine_GetLight(const GameEngine *engine, const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PuzzleSize && y >= 0 && y < PuzzleSize)
    {
        return bitRead(engine->Lights, y * PuzzleSize + x);
    }

    return false;
}

bool GameEngine_IsCompleted(const GameEngine *engine)
{
    return engine->Lights == 0;
}

uint8_t GameEngine_GetHalfStars(const GameEngine *engine)
{
    uint8_t halfStarsLost = engine->Moves <= engine->Par ? 0 : max(0, (1 + engine->Moves - engine->Par) / 2);
    return max(MinHalfStars, MaxHalfStars - halfStarsLost);
}

void GameEngine_ToggleSingleLight(GameEngine *engine, const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PuzzleSize && y >= 0 && y < PuzzleSize)
    {
        bitToggle(engine->Lights, y * PuzzleSize + x);
    }
}

void GameEngine_ToggleLights(GameEngine *engine, const int8_t x, const int8_t y)
{
    int8_t targetX = max(0, min(x, PuzzleSize - 1));
    int8_t targetY = max(0, min(y, PuzzleSize - 1));
    
    GameEngine_ToggleSingleLight(engine, targetX, targetY);
    GameEngine_ToggleSingleLight(engine, targetX + 1, targetY);
    GameEngine_ToggleSingleLight(engine, targetX, targetY + 1);
    GameEngine_ToggleSingleLight(engine, targetX - 1, targetY);
    GameEngine_ToggleSingleLight(engine, targetX, targetY - 1);
    
    engine->Moves++;    
}
