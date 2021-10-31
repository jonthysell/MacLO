// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "MacCommon.h"

void ShowError(Str255 message, Boolean isFatal)
{
    ParamText(message, EmptyString, EmptyString, EmptyString);
    StopAlert(ErrorAlertResID, NilFilterProc);
    
    if (isFatal)
    {
        ExitToShell();
    }
}

void CenterRect(const Rect *pOuterRect, Rect *pInnerRect)
{
    CenterRectH(pOuterRect, pInnerRect);
    CenterRectV(pOuterRect, pInnerRect);
}

void CenterRectH(const Rect *pOuterRect, Rect *pInnerRect)
{
    OffsetRect(pInnerRect, pOuterRect->left - pInnerRect->left, 0);
    OffsetRect(pInnerRect, (pOuterRect->right - pInnerRect->right) / 2, 0);
}

void CenterRectV(const Rect *pOuterRect, Rect *pInnerRect)
{
    OffsetRect(pInnerRect, 0, pOuterRect->top - pInnerRect->top);
    OffsetRect(pInnerRect, 0, (pOuterRect->bottom - pInnerRect->bottom) / 2);
}