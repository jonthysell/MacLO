// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameWindow.h"
#include "MacLO.h"

#define AppleMenuResID     BaseResID
#define AboutMenuItemID    1

#define GameMenuResID      BaseResID+1
#define NewMenuItemID      1
#define QuitMenuItemID     3

#define AboutDialogResID   BaseResID
#define AboutDialogOKID    1

GameWindow gGameWindow;
Boolean gExitApp;

void MacLO_HandleUpdate(const EventRecord *pEvent);
void MacLO_HandleMouseDown(const EventRecord *pEvent);
void MacLO_HandleMouseUp(const EventRecord *pEvent);

void MacLO_HandleMenuChoice(const int32_t menuChoice);
void MacLO_HandleAppleMenuChoice(const int16_t item);

void MacLO_ShowAboutDialog();
void MacLO_LaunchAppleMenuItem(const int16_t item);

void MacLO_HandleGameMenuChoice(const int16_t item);

void MacLO_ToolBoxInit()
{
    MaxApplZone();
    
    InitGraf(&thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(nil);
    FlushEvents(everyEvent, 0);
    InitCursor();
}

void MacLO_AppInit()
{
    Handle menuBar;
    MenuHandle appleMenu;
    
    // Add the menu bar
    menuBar = GetNewMBar(BaseResID);
    SetMenuBar(menuBar);
    
    // Populate the apple menu
    appleMenu = GetMHandle(AppleMenuResID);
    AddResMenu(appleMenu, 'DRVR');
    
    DrawMenuBar();
    
    // Setup the game window
    GameWindow_Init(&gGameWindow);
    GameWindow_Show(&gGameWindow);
}

void MacLO_MainLoop()
{
    EventRecord event;
    char cmdChar;
    
    while (!gExitApp)
    {
        if (WaitNextEvent(everyEvent, &event, LONG_MAX, nil))
        {
            switch (event.what)
            {
                case updateEvt:
                    MacLO_HandleUpdate(&event);
                    break;
                case mouseDown:
                    MacLO_HandleMouseDown(&event);
                    break;
                case mouseUp:
                    MacLO_HandleMouseUp(&event);
                    break;
                case keyDown:
                case autoKey:
                    // Translate command key combos to menu items
                    cmdChar = event.message & charCodeMask;
                    if ((event.modifiers & cmdKey) != 0)
                    {
                        MacLO_HandleMenuChoice(MenuKey(cmdChar));
                    }
                    break;
            }
        }
    }
}

void MacLO_HandleUpdate(const EventRecord *pEvent)
{
    WindowPtr window;
    
    window = (WindowPtr)pEvent->message;
    
    BeginUpdate(window);
    
    if (window == gGameWindow.Window)
    {
        GameWindow_Draw(&gGameWindow, true);
    }
    
    EndUpdate(window);
}

void MacLO_HandleMouseDown(const EventRecord *pEvent)
{
    WindowPtr window;
    int32_t windowPart;
    int32_t menuChoice;
    Point mousePosition;
    
    windowPart = FindWindow(pEvent->where, &window);
    mousePosition = pEvent->where;
    
    switch (windowPart)
    {
        case inMenuBar:
            menuChoice = MenuSelect(mousePosition);
            MacLO_HandleMenuChoice(menuChoice);
        case inSysWindow:
            SystemClick(pEvent, window);
            break;
        case inDrag:
            DragWindow(window, mousePosition, &((*GetGrayRgn())->rgnBBox));
            break;
    }
}

void MacLO_HandleMouseUp(const EventRecord *pEvent)
{
    WindowPtr window;
    int32_t windowPart;
    Point mousePosition;
    
    windowPart = FindWindow(pEvent->where, &window);
    mousePosition = pEvent->where;
    
    switch (windowPart)
    {
        case inContent:
            GlobalToLocal(&mousePosition);
            GameWindow_Click(&gGameWindow, &mousePosition);
            break;
    }
}

void MacLO_HandleMenuChoice(const int32_t menuChoice)
{
    int16_t menu;
    int16_t item;
    
    if (menuChoice != 0)
    {
        menu = HiWord(menuChoice);
        item = LoWord(menuChoice);
        
        switch (menu)
        {
            case AppleMenuResID:
                MacLO_HandleAppleMenuChoice(item);
                break;
            case GameMenuResID:
                MacLO_HandleGameMenuChoice(item);
                break;
        }
        
        HiliteMenu(0);
    }
}

void MacLO_HandleAppleMenuChoice(const int16_t item)
{
    MenuHandle appleMenu;
    Str255 accName;
    int16_t accNumber;
    
    switch (item)
    {
        case AboutMenuItemID:
            MacLO_ShowAboutDialog();
            break;
        default:
            MacLO_LaunchAppleMenuItem(item);
            break;
    }
}

void MacLO_ShowAboutDialog()
{
    GrafPtr oldPort;
    DialogPtr dialog;
    int32_t itemHit;
    
    GetPort(&oldPort);
    
    dialog = GetNewDialog(AboutDialogResID, nil, MoveToFront);
    
    SetPort(dialog);
    
    SetDialogDefaultItem(dialog, AboutDialogOKID);
    
    ShowWindow(dialog);
    
    ModalDialog(nil, &itemHit);
    
    DisposDialog(dialog);
    
    SetPort(oldPort);
}

void MacLO_LaunchAppleMenuItem(const int16_t item)
{
    MenuHandle appleMenu;
    Str255 accName;
    
    appleMenu = GetMHandle(AppleMenuResID);
    GetItem(appleMenu, item, accName);
    OpenDeskAcc(accName);
}

void MacLO_HandleGameMenuChoice(const int16_t item)
{
    switch (item)
    {
        case NewMenuItemID:
            GameWindow_SetScene(&gGameWindow, Title);
            break;
        case QuitMenuItemID:
            gExitApp = true;
            break;
    }
}
