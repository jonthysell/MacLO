// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file MacLO.c
 *
 * This file provides implementations for MacLO.h.
 */

#include "MacLO.h"
#include "GameWindow.h"

/** Resource ID for the apple menu. */
#define AppleMenuResID      BaseResID

/** ID for the about menu item. */
#define AboutMenuItemID     1

/** Resource ID for the game menu. */
#define GameMenuResID       BaseResID+1

/** ID for the title menu item. */
#define GoToTitleMenuItemID 1

/** ID for the sound item. */
#define SoundMenuItemID     2

/** ID for the clear menu item. */
#define ClearMenuItemID     4

/** ID for the quit menu item. */
#define QuitMenuItemID      6

/** Resource ID for the about dialog. */
#define AboutDialogResID    BaseResID

/** Resource ID for the about dialog's ok button. */
#define AboutDialogOKID     1

/** GameWindow global instance. */
GameWindow gGameWindow;

/** Bool to signal that the app should exit. */
bool gExitApp;

/**
 * Processes the update event with the given EventRecord.
 * @param pEvent The EventRecord. 
 */
void MacLO_HandleUpdate(const EventRecord *pEvent);

/**
 * Processes the mouse down event with the given EventRecord.
 * @param pEvent The EventRecord. 
 */
void MacLO_HandleMouseDown(const EventRecord *pEvent);

/**
 * Processes the mouse up event with the given EventRecord.
 * @param pEvent The EventRecord. 
 */
void MacLO_HandleMouseUp(const EventRecord *pEvent);

/**
 * Processes when a menu has been selected.
 * @param menuChoice The menu selected.
 */
void MacLO_HandleMenuChoice(const int32_t menuChoice);

/**
 * Processes when an item was selected in the apple menu.
 * @param item The item in the menu selected.
 */
void MacLO_HandleAppleMenuChoice(const int16_t item);

/**
 * Shows the about dialog.
 */
void MacLO_ShowAboutDialog();

/**
 * Launches the item selected in the apple menu.
 * @param item The item in the menu selected.
 */
void MacLO_LaunchAppleMenuItem(const int16_t item);

/**
 * Processes when an item was selected in the game menu.
 * @param item The item in the menu selected.
 */
void MacLO_HandleGameMenuChoice(const int16_t item);

/**
 * Quits the application.
 */
void MacLO_Quit();

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
    MenuHandle appleMenu, gameMenu;
    
    // Add the menu bar
    menuBar = GetNewMBar(BaseResID);
    if (menuBar == nil)
    {
        ShowError("\pMacLO MBAR resource missing!", true);
    }
    
    SetMenuBar(menuBar);
    
    // Populate the apple menu
    appleMenu = GetMHandle(AppleMenuResID);
    if (appleMenu == nil)
    {
        ShowError("\pApple MENU resource missing!", true);
    }
    
    AddResMenu(appleMenu, 'DRVR');
    
    gameMenu = GetMHandle(GameMenuResID);
    if (gameMenu == nil)
    {
        ShowError("\pGame MENU resource missing!", true);
    }
    
    // Setup the game window
    GameWindow_Init(&gGameWindow);
    MacLO_UpdateMenus();
    GameWindow_Show(&gGameWindow);
    
    // Update menus now that the game window is ready
    MacLO_UpdateMenus();
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
                        if (cmdChar == 'Q' || cmdChar == 'q')
                        {
                            // Always handle quit properly, don't rely
                            // on the quit menu existing or working properly
                            MacLO_Quit();
                        }
                        else
                        {
                            // Try to invoke menu
                            MacLO_HandleMenuChoice(MenuKey(cmdChar));
                        }
                    }
                    break;
            }
        }
    }
}

void MacLO_UpdateMenus()
{
    MenuHandle gameMenu = GetMHandle(GameMenuResID);
    
    CheckItem(gameMenu, SoundMenuItemID, gGameWindow.Sounds.Enabled);
    
    DrawMenuBar();
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
        case GoToTitleMenuItemID:
            GameWindow_SetScene(&gGameWindow, Title);
            break;
        case SoundMenuItemID:
            GameWindow_ToggleSound(&gGameWindow);
            break;
        case ClearMenuItemID:
            GameWindow_ClearScores(&gGameWindow);
            break;
        case QuitMenuItemID:
            MacLO_Quit();
            break;
    }
}

void MacLO_Quit()
{
    if (ShowConfirm("\pAre you sure you want to quit MacLO?"))
    {
        gExitApp = true;
        GameSave_SaveData(&(gGameWindow.GameSave), &(gGameWindow.Engine));
    }
}
