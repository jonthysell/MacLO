// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"

void InitToolbox()
{
    InitGraf(&thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(0L);
    FlushEvents(everyEvent, 0);
    InitCursor();
}

void InitMainWindow()
{
    MainWindow = GetNewWindow(128, 0L, (WindowPtr)-1L);
    SetPort(MainWindow);
    MoveTo(30, 50);
    DrawString("\pHello MacLO");
}

void EventLoop()
{
    while (!Button()) { }
}

void main(void)
{
    InitToolbox();
    InitMainWindow();
    EventLoop();
}
