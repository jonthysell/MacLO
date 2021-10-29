// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Levels.h"

extern const int8_t PuzzleSize;

extern const uint8_t MaxStars;
extern const uint8_t MaxHalfStars;
extern const uint8_t MinHalfStars;

extern const uint16_t PerfectScore;

typedef struct GameEngine
{
    uint16_t Score;
    int8_t   Level;
    bool     SetB;
    uint32_t Lights;
    uint16_t Par;
    uint16_t Moves;
} GameEngine;

void GameEngine_NewGame(GameEngine *pGameEngine, const bool setB);

void GameEngine_NextLevel(GameEngine *pGameEngine);

void GameEngine_ResetLevel(GameEngine *pGameEngine);

bool GameEngine_GetLight(const GameEngine *pGameEngine, const int8_t x, const int8_t y);

bool GameEngine_IsCompleted(const GameEngine *pGameEngine);

uint8_t GameEngine_GetHalfStars(const GameEngine *pGameEngine);

void GameEngine_ToggleLights(GameEngine *pGameEngine, const int8_t x, const int8_t y);

#endif
