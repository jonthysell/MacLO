// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file MacLO.h
 *
 * This file provides the functions necessary to setup the application.
 */

#ifndef MACLO_H
#define MACLO_H

/**
 * Initialize the Macintosh Toolbox managers.
 */
void MacLO_ToolBoxInit();

/**
 * Initialize the application.
 */
void MacLO_AppInit();

/**
 * Run the main loop of the application.
 */
void MacLO_MainLoop();

/**
 * Update menus of the application.
 */
void MacLO_UpdateMenus();

#endif
