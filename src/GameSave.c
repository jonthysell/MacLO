// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameSave.c
 *
 * This file provides implementations for GameSave.h.
 */

#include "GameSave.h"
#include "MacCommon.h"

/** The save resource type. */
#define SaveResType 'SAVE'

/** The save resource ID. */
#define SaveResID   128

/** The save resource ID. */
#define SaveResSize (sizeof(uint8_t) * SetCount * LevelCount)

void GameSave_Init(GameSave *pGameSave)
{
    pGameSave->Save = GetOrAddResource(SaveResType, SaveResID, SaveResSize, EmptyString);
    if (pGameSave->Save == nil)
    {
        ShowError("\pGame's SAVE resource couldn't be created!", true);
    }
}

void GameSave_LoadData(const GameSave *pSaveGame, GameEngine *pGameEngine)
{
    int8_t level, scoreA, scoreB;
    bool resetA, resetB;
    
    HLock(pSaveGame->Save);
    
    resetA = false;
    resetB = false;
    
    for (level = 0; level < LevelCount; level++)
    {
        scoreA = min(MaxHalfStars, (*pSaveGame->Save)[level]);
        resetA = resetA || (scoreA < MinHalfStars);
        pGameEngine->ScoresA[level] = resetA ? 0 : scoreA;
        
        scoreB = min(MaxHalfStars, (*pSaveGame->Save)[LevelCount + level]);
        resetB = resetB || (scoreB < MinHalfStars);
        pGameEngine->ScoresB[level] = resetB ? 0 : scoreB;
    }
    
    HUnlock(pSaveGame->Save);
}

void GameSave_SaveData(GameSave *pSaveGame, const GameEngine *pGameEngine)
{
    int8_t level;
    bool dataChanged;
    
    HLock(pSaveGame->Save);
    
    dataChanged = false;
    for (level = 0; level < LevelCount; level++)
    {
        dataChanged = dataChanged
                      || ((*pSaveGame->Save)[level] != pGameEngine->ScoresA[level])
                      || ((*pSaveGame->Save)[LevelCount + level] != pGameEngine->ScoresB[level]);
        
        (*pSaveGame->Save)[level] = pGameEngine->ScoresA[level];
        (*pSaveGame->Save)[LevelCount + level] = pGameEngine->ScoresB[level];
    }
    
    HUnlock(pSaveGame->Save);
    
    if (dataChanged)
    {
        ChangedResource(pSaveGame->Save);
        WriteResource(pSaveGame->Save);
    }
}
