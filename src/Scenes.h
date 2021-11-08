// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef SCENES_H
#define SCENES_H

#define NumScenes 4

typedef enum eSceneId
{
    Title,
    Play,
    LevelEnd,
    GameEnd
} SceneId;

typedef struct sTitleScene
{
    Rect TitleRect;
    Rect SetARect;
    Rect SetBRect;
} TitleScene;

typedef struct sPlayScene
{
    Rect PlayfieldRect;
    Rect HUDRect;
    Rect LevelRect;
    Rect HalfStarsRect;
    Rect ScoreRect;
    Rect RetryButtonRect;
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
