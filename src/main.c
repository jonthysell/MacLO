// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file main.c
 *
 * This file provides the main() entry point.
 */

#include "MacLO.h"

/**
 * Entry point for the application.
 */
void main(void)
{
    MacLO_ToolBoxInit();
    MacLO_AppInit();
    MacLO_MainLoop();
}
