// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "MacCommon.h"

void CenterWindow(WindowPtr window)
{
    
}

Boolean IsCompactDisplay()
{
    return screenBits.bounds.right == 512
        && screenBits.bounds.bottom == 342;
}

void ShowError(Str255 message, Boolean isFatal)
{
    ParamText(message, kEmptyString, kEmptyString, kEmptyString);
    StopAlert(kErrorAlertID, kNilFilterProc);
    
    if (isFatal)
    {
        ExitToShell();
    }
}
