// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "MacCommon.h"
#include "MacLO.h"

void InitToolBox()
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

void InitMainWindow()
{
    WindowPtr window;
    
    window = GetNewWindow(kBaseResID, nil, kMoveToFront);
    
    if (window == nil)
    {
        SysBeep(0);
        ExitToShell();
    }
    
    ShowWindow(window);
    SetPort(window);
    
    MoveTo(30, 50);
    DrawString("\pHello MacLO");
}

void ProcessEvents()
{
    while (!Button()) { }
}

