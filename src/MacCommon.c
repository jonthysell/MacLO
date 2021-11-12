// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "MacCommon.h"

const int16_t MonthOffset[] = {
    0,   // Jan
    31,  // Feb
    60,  // Mar
    91,  // Apr
    121, // May
    152, // Jun
    182, // Jul
    213, // Aug
    244, // Sep
    274, // Oct
    305, // Nov
    335, // Dec
};

void ShowError(Str255 message, bool isFatal)
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

void ConcatenateRect(const Rect *pLeftRect, const Rect *pRightRect, Rect *pDestRect)
{
    Rect newRightRect;
    
    newRightRect.top = pLeftRect->top;
    newRightRect.left = pLeftRect->right;
    newRightRect.bottom = newRightRect.top + (pRightRect->bottom - pRightRect->top);
    newRightRect.right = newRightRect.left + (pRightRect->right - pRightRect->left);
    
    UnionRect(pLeftRect, &newRightRect, pDestRect);
}

void GetBoxRect(const Rect *pOuterRect, const BoxAlignment boxAlignment, Rect *pBoxRect)
{
    int32_t boxWidth, boxHeight;
    Rect resultRect;
    
    boxWidth = (pOuterRect->right - pOuterRect->left) / 3;
    boxHeight = (pOuterRect->bottom - pOuterRect->top) / 3;
    
    switch (boxAlignment)
    {
        case Top:
            resultRect.top = pOuterRect->top;
            resultRect.left = pOuterRect->left + boxWidth;
            resultRect.bottom = pOuterRect->top + boxHeight;
            resultRect.right = pOuterRect->right - boxWidth;
            break;
        case TopLeft:
            resultRect.top = pOuterRect->top;
            resultRect.left = pOuterRect->left;
            resultRect.bottom = pOuterRect->top + boxHeight;
            resultRect.right = pOuterRect->left + boxWidth;
            break;
        case Left:
            resultRect.top = pOuterRect->top + boxHeight;
            resultRect.left = pOuterRect->left;
            resultRect.bottom = pOuterRect->bottom - boxHeight;
            resultRect.right = pOuterRect->left + boxWidth;
            break;
        case BottomLeft:
            resultRect.top = pOuterRect->bottom - boxHeight;
            resultRect.left = pOuterRect->left;
            resultRect.bottom = pOuterRect->bottom;
            resultRect.right = pOuterRect->left + boxWidth;
            break;
        case Bottom:
            resultRect.top = pOuterRect->bottom - boxHeight;
            resultRect.left = pOuterRect->left + boxWidth;
            resultRect.bottom = pOuterRect->bottom;
            resultRect.right = pOuterRect->right - boxWidth;
            break;
        case BottomRight:
            resultRect.top = pOuterRect->bottom - boxHeight;
            resultRect.left = pOuterRect->right - boxWidth;
            resultRect.bottom = pOuterRect->bottom;
            resultRect.right = pOuterRect->right;
            break;
        case Right:
            resultRect.top = pOuterRect->top + boxHeight;
            resultRect.left = pOuterRect->right - boxWidth;
            resultRect.bottom = pOuterRect->bottom - boxHeight;
            resultRect.right = pOuterRect->right;
            break;
        case TopRight:
            resultRect.top = pOuterRect->top;
            resultRect.left = pOuterRect->right - boxWidth;
            resultRect.bottom = pOuterRect->top + boxHeight;
            resultRect.right = pOuterRect->right;
            break;
        case Center:
            resultRect.top = pOuterRect->top + boxHeight;
            resultRect.left = pOuterRect->left + boxWidth;
            resultRect.bottom = pOuterRect->bottom - boxHeight;
            resultRect.right = pOuterRect->right - boxWidth;
            break;
    }
    
    *pBoxRect = resultRect;
}

void GetPictureRect(const PicHandle picHandle, Rect *pDestRect)
{
    *pDestRect = (**(picHandle)).picFrame;
}

void GetScaledPicFrame(const PicHandle picHandle, const uint8_t scale, Rect *pDestRect)
{
    GetPictureRect(picHandle, pDestRect);
    
    pDestRect->right = pDestRect->left + ((pDestRect->right - pDestRect->left) * max(scale, 1));
    pDestRect->bottom = pDestRect->top + ((pDestRect->bottom - pDestRect->top) * max(scale, 1));
}

void DrawScaledPic(const PicHandle pic, const uint8_t scale)
{
    Point penPosition;
    Rect destRect;
    
    GetPen(&penPosition);
    GetScaledPicFrame(pic, scale, &destRect);
    
    OffsetRect(&destRect, penPosition.h, penPosition.v);
    
    DrawPicture(pic, &destRect);
    MoveTo(destRect.right, destRect.top);
}
