// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file Scenes.h
 *
 * This file provides a variety of scene-specific types which contain the
 * data that those scenes require to render properly.
 */

#ifndef SCENES_H
#define SCENES_H

/** The total number of scenes. */
#define NumScenes 5

/** Enum defining unique IDs for each scene. */
typedef enum eSceneId
{
    Title,
    LevelSelect,
    Play,
    LevelEnd,
    GameEnd
} SceneId;

/** Struct containing data needed for the Title scene. */
typedef struct sTitleScene
{
    Rect TitleRect;
    Rect SetARect;
    Rect SetBRect;
    Rect SoundButtonRect;
} TitleScene;

/** Struct containing data needed for the LevelSelect scene. */
typedef struct sLevelSelectScene
{
    int8_t PageNumber;
    Rect   SetRect;
    Rect   ScoreRect;
    Rect   PrevButtonRect;
    Rect   NextButtonRect;
    Rect   LevelGridRect;
} LevelSelectScene;

/** Struct containing data needed for the Play scene. */
typedef struct sPlayScene
{
    Rect PlayfieldRect;
    Rect HUDRect;
    Rect LevelRect;
    Rect HalfStarsRect;
    Rect ScoreRect;
    Rect RetryButtonRect;
    Rect SoundButtonRect;
} PlayScene;

/** Struct containing data needed for the LevelEnd scene. */
typedef struct sLevelEndScene
{
    Rect LevelRect;
    Rect HalfStarsRect;
    Rect ScoreRect;
    Rect RetryButtonRect;
    Rect NextButtonRect;
} LevelEndScene;

/** Struct containing data needed for the GameEnd scene. */
typedef struct sGameEndScene
{
    Rect SetRect;
    Rect ScoreRect;
} GameEndScene;

#endif
