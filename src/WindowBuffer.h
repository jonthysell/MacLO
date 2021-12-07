// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file WindowBuffer.h
 *
 * This file provides a WindowBuffer type which manages offscreen buffering
 * of Toolbox drawing commands on behalf of a Window.
 */

#ifndef WINDOWBUFFER_H
#define WINDOWBUFFER_H

/** Struct containing pointers to the Window and its offscreen buffer. */
typedef struct sWindowBuffer
{
    WindowPtr Window;
    GrafPtr   Buffer;
} WindowBuffer;

/**
 * Initializes the WindowBuffer for the given Window.
 * @param pWindowBuffer The WindowBuffer.
 * @param window The Window to buffer.
 */
void WindowBuffer_Init(WindowBuffer *pWindowBuffer, const WindowPtr window);

/**
 * Start redirecting drawing to the offscreen buffer.
 * @param pWindowBuffer The WindowBuffer.
 */
void WindowBuffer_StartDraw(const WindowBuffer *pWindowBuffer);

/**
 * Stop redirecting drawing to the offscreen buffer, and immediately copy
 * everything from the buffer to the Window.
 * @param pWindowBuffer The WindowBuffer.
 */
void WindowBuffer_EndDraw(const WindowBuffer *pWindowBuffer);

#endif