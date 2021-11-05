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
    Rect      TitleRect;
} TitleScene;

typedef struct sPlayScene
{
    Rect PlayfieldRect;
    Rect HUDRect;
} PlayScene;

typedef struct sLevelEndScene
{
    Rect temp;
} LevelEndScene;

typedef struct sGameEndScene
{
    Rect temp;
} GameEndScene;

#endif
