// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file MacCommon.h
 *
 * This file includes some common utility functions for use by Macintosh
 * applications and the Macintosh Toolbox.
 */

#ifndef MACCOMMON_H
#define MACCOMMON_H

#include "Common.h"

/** The first non-reserved resource ID. */
#define BaseResID       128

/** Constant to put a Window to the top of the stack. */
#define MoveToFront     (WindowPtr)-1L

/** An empty Pascal string. */
#define EmptyString     "\p"

/** A nil filter. */
#define NilFilterProc   nil

/** Enum defining nine equal boxes within a rectangle. */
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

/**
 * Toolbox function to set the default Button in a Dialog.
 * @param theDialog The target Dialog.
 * @param itemID The ID of the Button to set as the default.
 * @return An error code.
 */
pascal OSErr SetDialogDefaultItem(DialogPtr theDialog, int16_t itemID) = { 0x303C, 0x0304, 0xAA68 };

/**
 * Displays an error message and optionally terminates the application.
 * @param message The message to display.
 * @param isFatal Whether or not the application should terminate.
 */
void ShowError(Str255 message, bool isFatal);

/**
 * Prompts the user to confirm continuing with a (destructive) action.
 * @param message The message to display.
 * @return The user's choice whether or not to continue.
 */
bool ShowConfirm(Str255 message);

/**
 * Centers an inner Rect within a static outer Rect.
 * @param pOuterRect The static outer Rect.
 * @param pInnerRect The inner Rect to move.
 */
void CenterRect(const Rect *pOuterRect, Rect *pInnerRect);

/**
 * Centers an inner Rect horizontally within a static outer Rect.
 * @param pOuterRect The static outer Rect.
 * @param pInnerRect The inner Rect to move.
 */
void CenterRectH(const Rect *pOuterRect, Rect *pInnerRect);

/**
 * Centers an inner Rect vertically within a static outer Rect.
 * @param pOuterRect The static outer Rect.
 * @param pInnerRect The inner Rect to move.
 */
void CenterRectV(const Rect *pOuterRect, Rect *pInnerRect);

/**
 * Combines two Rects into a new Rect, by moving the right Rect directly
 * to the right of the left Rect (tops aligned), and finding the smallest
 * Rect which contains them both.
 * @param pLeftRect The Rect on the left.
 * @param pRightRect The Rect on the right.
 * @param pDestRect The concatenated Rect.
 */
void ConcatenateRect(const Rect *pLeftRect, const Rect *pRightRect, Rect *pDestRect);

/**
 * Gets the Rect at the given BoxAlignment within the static outer Rect.
 * @param pOuterRect The static outer Rect.
 * @param boxAlignment The target BoxAlignment.
 * @param pBoxRect The Rect within the outer rect at the BoxAlignment.
 */
void GetBoxRect(const Rect *pOuterRect, const BoxAlignment boxAlignment, Rect *pBoxRect);

/**
 * Gets the Rect which bounds the given picture.
 * @param picHandle The target picture.
 * @param pDestRect The Rect bounding the picture.
 */
void GetPictureRect(const PicHandle picHandle, Rect *pDestRect);

/**
 * Gets the Rect which bounds the given picture if it had been scaled.
 * @param picHandle The target picture.
 * @param scale The scale factor.
 * @param pDestRect The Rect bounding the scaled picture.
 */
void GetScaledPicFrame(const PicHandle picHandle, const uint8_t scale, Rect *pDestRect);

/**
 * Draws the given picture scaled at the pen's location.
 * @param picHandle The target picture.
 * @param scale The scale factor.
 */
void DrawScaledPic(const PicHandle pic, const uint8_t scale);

/**
 * Gets the specified resource or creates it if it doesn't exist.
 * @param resType The resource type.
 * @param resID The resource ID.
 * @param byteCount The size of the resource if it needs to be created.
 * @param resName The resource name if it needs to be created.
 * @return Handle to the resource.
 */
Handle GetOrAddResource(ResType resType, uint16_t resID, Size byteCount, Str255 resName);

#endif
