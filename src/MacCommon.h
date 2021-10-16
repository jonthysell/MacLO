// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef MACCOMMON_H
#define MACCOMMON_H

#define BaseResID       128
#define MoveToFront     (WindowPtr)-1L

#define EmptyString     "\p"
#define NilFilterProc   nil

#define ErrorAlertResID BaseResID

void CenterWindow(WindowPtr window);
Boolean IsCompactDisplay();
void ShowError(Str255 message, Boolean isFatal);

#endif
