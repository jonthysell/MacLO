// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file GameWindow.h
 *
 * This file provides the GameWindow type, which, as MacLO is essentially
 * played entirely within one Window, essentially manages the entire game.
 * GameWindow keeps track of the core GameEngine as well as the current scene,
 * which it calls to handle rendering and to handle user interaction based
 * on the state of both.
 */

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "MacCommon.h"
#include "WindowBuffer.h"
#include "GameEngine.h"
#include "GameSave.h"
#include "Bitmaps.h"
#include "Sounds.h"
#include "Scenes.h"

/** The background pattern of the window. */
#define WindowPattern  black

/** Struct containing everything the game needs. */
typedef struct sGameWindow
{
    WindowPtr        Window;
    WindowBuffer     WindowBuffer;
    GameEngine       Engine;
    GameSave         GameSave;
    Bitmaps          Bitmaps;
    Sounds           Sounds;
    SceneId          CurrentSceneId;
    TitleScene       TitleScene;
    LevelSelectScene LevelSelectScene;
    PlayScene        PlayScene;
    LevelEndScene    LevelEndScene;
    GameEndScene     GameEndScene;
} GameWindow;

/**
 * Initializes the GameWindow.
 * @param pGameWindow The GameWindow.
 */
void GameWindow_Init(GameWindow *pGameWindow);

/**
 * Draws the GameWindow.
 * @param pGameWindow The GameWindow.
 * @param fullRefresh Whether or not the whole screen needs to be redrawn.
 */
void GameWindow_Draw(const GameWindow *pGameWindow, bool fullRefresh);

/**
 * Handles clicks on the GameWindow.
 * @param pGameWindow The GameWindow.
 * @param pPosition The local position where the click occured.
 */
void GameWindow_Click(GameWindow *pGameWindow, const Point *pPosition);

/**
 * Changes the GameWindow to the given scene.
 * @param pGameWindow The GameWindow.
 * @param sceneId The new scene.
 */
void GameWindow_SetScene(GameWindow *pGameWindow, const SceneId sceneId);

/**
 * Activates the GameWindow.
 * @param pGameWindow The GameWindow.
 */
void GameWindow_Show(const GameWindow *pGameWindow);

/**
 * Toggles whether sound is enabled/disabled for the GameWindow.
 * @param pGameWindow The GameWindow.
 */
void GameWindow_ToggleSound(GameWindow *pGameWindow);

/**
 * Resets the level scores of the GameWindow.
 * @param pGameWindow The GameWindow.
 */
void GameWindow_ClearScores(GameWindow *pGameWindow);

#endif
