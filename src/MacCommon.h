// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef MACCOMMON_H
#define MACCOMMON_H

#include "Common.h"

#define BaseResID       128
#define MoveToFront     (WindowPtr)-1L

#define EmptyString     "\p"
#define NilFilterProc   nil

#define ErrorAlertResID BaseResID

typedef enum eBoxAlignment
{
    Top,
    TopLeft,
    Left,
    BottomLeft,
    Bottom,
    BottomRight,
    Right,
    TopRight,
    Center
} BoxAlignment;

pascal OSErr SetDialogDefaultItem(DialogPtr theDialog, int16_t newItem) = { 0x303C, 0x0304, 0xAA68 };

int32_t GetThemeID();

void ShowError(Str255 message, bool isFatal);

void CenterRect(const Rect *pOuterRect, Rect *pInnerRect);
void CenterRectH(const Rect *pOuterRect, Rect *pInnerRect);
void CenterRectV(const Rect *pOuterRect, Rect *pInnerRect);

void GetBoxRect(const Rect *pOuterRect, const BoxAlignment boxAlignment, Rect *pBoxRect);

#endif
