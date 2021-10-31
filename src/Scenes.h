// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef SCENES_H
#define SCENES_H

#define NumScenes 4

typedef enum SceneId
{
    Title,
    Play,
    LevelEnd,
    GameEnd
} SceneId;

typedef struct TitleScene
{
    PicHandle TitlePict;
    Rect      TitleRect;
} TitleScene;

typedef struct PlayScene
{
    Rect PlayfieldRect;
    Rect HUDRect;
} PlayScene;

#endif
