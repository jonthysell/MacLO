// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "MacCommon.h"

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
    
    boxWidth = (pOuterRect->right - pOuterRect->left) / 3;
    boxHeight = (pOuterRect->bottom - pOuterRect->top) / 3;
    
    switch (boxAlignment)
    {
        case Top:
            pBoxRect->top = pOuterRect->top;
            pBoxRect->left = pOuterRect->left + boxWidth;
            pBoxRect->bottom = pOuterRect->top + boxHeight;
            pBoxRect->right = pOuterRect->right - boxWidth;
            break;
        case TopLeft:
            pBoxRect->top = pOuterRect->top;
            pBoxRect->left = pOuterRect->left;
            pBoxRect->bottom = pOuterRect->top + boxHeight;
            pBoxRect->right = pOuterRect->left + boxWidth;
            break;
        case Left:
            pBoxRect->top = pOuterRect->top + boxHeight;
            pBoxRect->left = pOuterRect->left;
            pBoxRect->bottom = pOuterRect->bottom - boxHeight;
            pBoxRect->right = pOuterRect->left + boxWidth;
            break;
        case BottomLeft:
            pBoxRect->top = pOuterRect->bottom - boxHeight;
            pBoxRect->left = pOuterRect->left;
            pBoxRect->bottom = pOuterRect->bottom;
            pBoxRect->right = pOuterRect->left + boxWidth;
            break;
        case Bottom:
            pBoxRect->top = pOuterRect->bottom - boxHeight;
            pBoxRect->left = pOuterRect->left + boxWidth;
            pBoxRect->bottom = pOuterRect->bottom;
            pBoxRect->right = pOuterRect->right - boxWidth;
            break;
        case BottomRight:
            pBoxRect->top = pOuterRect->bottom - boxHeight;
            pBoxRect->left = pOuterRect->right - boxWidth;
            pBoxRect->bottom = pOuterRect->bottom;
            pBoxRect->right = pOuterRect->right;
            break;
        case Right:
            pBoxRect->top = pOuterRect->top + boxHeight;
            pBoxRect->left = pOuterRect->right - boxWidth;
            pBoxRect->bottom = pOuterRect->bottom - boxHeight;
            pBoxRect->right = pOuterRect->right;
            break;
        case TopRight:
            pBoxRect->top = pOuterRect->top;
            pBoxRect->left = pOuterRect->right - boxWidth;
            pBoxRect->bottom = pOuterRect->top + boxHeight;
            pBoxRect->right = pOuterRect->right;
            break;
        case Center:
            pBoxRect->top = pOuterRect->top + boxHeight;
            pBoxRect->left = pOuterRect->left + boxWidth;
            pBoxRect->bottom = pOuterRect->bottom - boxHeight;
            pBoxRect->right = pOuterRect->right - boxWidth;
            break;
    }
}

void GetScaledPicFrame(const PicHandle picHandle, const uint8_t scale, Rect *pDestRect)
{
    *pDestRect = (**(picHandle)).picFrame;
    
    pDestRect->right = pDestRect->left + ((pDestRect->right - pDestRect->left) * max(scale, 1));
    pDestRect->bottom = pDestRect->top + ((pDestRect->bottom - pDestRect->top) * max(scale, 1));
}
