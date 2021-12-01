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
    uint8_t  ScoresA[LevelCount];
    uint8_t  ScoresB[LevelCount];
    int8_t   Level;
    bool     SetB;
    uint32_t Lights;
    uint32_t PreviousLights;
    uint16_t Par;
    uint16_t Moves;
} GameEngine;

void GameEngine_Init(GameEngine *pGameEngine);

void GameEngine_NewGame(GameEngine *pGameEngine, const bool setB);

void GameEngine_ResetGame(GameEngine *pGameEngine);

void GameEngine_StartLevel(GameEngine *pGameEngine, const uint8_t level);

void GameEngine_CompleteLevel(GameEngine *pGameEngine);

void GameEngine_NextLevel(GameEngine *pGameEngine);

void GameEngine_ResetLevel(GameEngine *pGameEngine);

bool GameEngine_GetLight(const GameEngine *pGameEngine, const int8_t x, const int8_t y);

bool GameEngine_IsCompleted(const GameEngine *pGameEngine);

bool GameEngine_IsEnabled(const GameEngine *pGameEngine, const int8_t level);

bool GameEngine_IsGameOver(const GameEngine *pGameEngine);

uint8_t GameEngine_GetHalfStars(const GameEngine *pGameEngine);

uint8_t GameEngine_GetScore(const GameEngine *pGameEngine, const int8_t level);

uint16_t GameEngine_GetTotalScore(const GameEngine *pGameEngine);

void GameEngine_ToggleLights(GameEngine *pGameEngine, const int8_t x, const int8_t y);

bool GameEngine_LightChanged(const GameEngine *pGameEngine, const int8_t x, const int8_t y);

bool GameEngine_HalfStarsChanged(const GameEngine *pGameEngine);

#endif
