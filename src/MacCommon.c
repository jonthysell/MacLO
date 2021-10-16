// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "MacCommon.h"

void CenterWindow(WindowPtr window)
{
    // TODO
}

void ShowError(Str255 message, Boolean isFatal)
{
    ParamText(message, EmptyString, EmptyString, EmptyString);
    StopAlert(ErrorAlertResID, NilFilterProc);
    
    if (isFatal)
    {
        ExitToShell();
    }
}
