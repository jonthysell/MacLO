// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "WindowBuffer.h"
#include "MacCommon.h"

void WindowBuffer_Init(WindowBuffer *pWindowBuffer, const WindowPtr window)
{
    int16_t width, height;
    BitMap newBits;
    
    pWindowBuffer->Window = window;
    
    // Create a BitMap as the backing for the buffer,
    // since System 6 doesn't have fancy GWorlds
    width = window->portRect.right - window->portRect.left;
    height = window->portRect.bottom - window->portRect.top;
    SetRect(&newBits.bounds, 0, 0, width, height);
    newBits.rowBytes = ((width + 31)/32) * 4;
    newBits.baseAddr = NewPtr(height * newBits.rowBytes);
    
    // Clear the bitmap
    CopyBits(&newBits,
             &newBits,
             &newBits.bounds,
             &newBits.bounds,
             srcXor,
             nil);
    
    // Create the buffer and get it ready
    pWindowBuffer->Buffer = (GrafPtr)NewPtr(sizeof(GrafPort));
    OpenPort(pWindowBuffer->Buffer);
    SetPort(pWindowBuffer->Buffer);
    
    pWindowBuffer->Buffer->portRect = newBits.bounds;
    RectRgn(pWindowBuffer->Buffer->visRgn, &newBits.bounds);
    SetPortBits(&newBits);
}

void WindowBuffer_StartDraw(const WindowBuffer *pWindowBuffer)
{
    // Set the buffer as the port for future QuickDraw commands
    SetPort(pWindowBuffer->Buffer);
}

void WindowBuffer_EndDraw(const WindowBuffer *pWindowBuffer)
{
    SetPort(pWindowBuffer->Window);
    
    // Copy the buffer to the window
    CopyBits(&(pWindowBuffer->Buffer->portBits),
             &(pWindowBuffer->Window->portBits),
             &(pWindowBuffer->Buffer->portRect),
             &(pWindowBuffer->Window->portRect),
             srcCopy, nil);
}
