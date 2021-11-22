// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef WINDOWBUFFER_H
#define WINDOWBUFFER_H

typedef struct sWindowBuffer
{
    WindowPtr Window;
    GrafPtr   Buffer;
} WindowBuffer;

void WindowBuffer_Init(WindowBuffer *pWindowBuffer, const WindowPtr window);
void WindowBuffer_StartDraw(const WindowBuffer *pWindowBuffer);
void WindowBuffer_EndDraw(const WindowBuffer *pWindowBuffer);

#endif