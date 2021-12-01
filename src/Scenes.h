// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef SCENES_H
#define SCENES_H

#define NumScenes 4

typedef enum eSceneId
{
    Title,
    LevelSelect,
    Play,
    LevelEnd,
    GameEnd
} SceneId;

typedef struct sTitleScene
{
    Rect TitleRect;
    Rect SetARect;
    Rect SetBRect;
    Rect SoundButtonRect;
} TitleScene;

typedef struct sLevelSelectScene
{
    int8_t PageNumber;
    Rect   SetRect;
    Rect   ScoreRect;
    Rect   PrevButtonRect;
    Rect   NextButtonRect;
    Rect   LevelGridRect;
} LevelSelectScene;

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

typedef struct sLevelEndScene
{
    Rect LevelRect;
    Rect HalfStarsRect;
    Rect ScoreRect;
    Rect RetryButtonRect;
    Rect NextButtonRect;
} LevelEndScene;

typedef struct sGameEndScene
{
    Rect SetRect;
    Rect ScoreRect;
} GameEndScene;

#endif
