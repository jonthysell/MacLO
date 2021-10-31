// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef MACCOMMON_H
#define MACCOMMON_H

#define BaseResID       128
#define MoveToFront     (WindowPtr)-1L

#define EmptyString     "\p"
#define NilFilterProc   nil

#define ErrorAlertResID BaseResID

pascal OSErr SetDialogDefaultItem(DialogPtr theDialog, short newItem) = { 0x303C, 0x0304, 0xAA68 };

void ShowError(Str255 message, Boolean isFatal);

void CenterRect(const Rect *pOuterRect, Rect *pInnerRect);
void CenterRectH(const Rect *pOuterRect, Rect *pInnerRect);
void CenterRectV(const Rect *pOuterRect, Rect *pInnerRect);

#endif
