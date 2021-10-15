// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"
#include "MacLO.h"

GameWindow gGameWindow;

void MacLO_InitToolBox()
{
    InitGraf(&thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(nil);
    FlushEvents(everyEvent, 0);
    InitCursor();
}

void MacLO_InitWindows()
{
    GameWindow_Init(&gGameWindow);
}

void MacLO_MainLoop()
{
    while (!Button()) { }
}

