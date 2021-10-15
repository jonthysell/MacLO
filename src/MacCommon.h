// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef MACCOMMON_H
#define MACCOMMON_H

#define kBaseResID       128
#define kMoveToFront     (WindowPtr)-1L

#define kEmptyString     "\p"
#define kNilFilterProc   nil

#define kErrorAlertID    kBaseResID

void CenterWindow(WindowPtr window);
Boolean IsCompactDisplay();
void ShowError(Str255 message, Boolean isFatal);

#endif
