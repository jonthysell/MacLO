// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

/**
 * @file LevelSelectScene.c
 *
 * This file provides implementations for LevelSelectScene.h.
 */

#include "LevelSelectScene.h"

/** Scale factor for the A/B set text. */
#define SetTextScale   3

/** Scale factor for the score text. */
#define ScoreTextScale 1

/** Margin for each level selection. */
#define LevelMargin         10

/** Width for each level selection. */
#define LevelWidth          80

/** Height for each level selection. */
#define LevelHeight         60

/** The number of rows of levels to show. */
#define LevelRowCount       2

/** The number of columns of levels to show. */
#define LevelColumnCount    5

/** The total number of levels to show per page.  */
#define LevelsPerPage       (LevelRowCount * LevelColumnCount)

/** Scale factor for the level text. */
#define LevelTextScale      1

/**
 * Gets the Rect of the level selection at the given index.
 * @param pGameWindow The GameWindow.
 * @param pRect. The Rect of the level selection.
 * @param i The index of the level onscreen.
 */
void LevelSelectScene_SetLevelRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t i);

void LevelSelectScene_Init(GameWindow *pGameWindow)
{
    Rect r;
    
    const Rect *pContentRect = &(pGameWindow->Window->portRect);
    
    pGameWindow->LevelSelectScene.PageNumber = pGameWindow->Engine.Level / LevelsPerPage;
        
    // Setup set
    GetScaledPicFrame(pGameWindow->Engine.SetB ? pGameWindow->Bitmaps.BCharPict : pGameWindow->Bitmaps.ACharPict, SetTextScale, &(pGameWindow->LevelSelectScene.SetRect));
    
    GetBoxRect(pContentRect, Top, &r);
    CenterRect(&r, &(pGameWindow->LevelSelectScene.SetRect));
    
    // Setup score
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale, &(pGameWindow->LevelSelectScene.ScoreRect));
    GetScaledPicFrame(pGameWindow->Bitmaps.SlashCharPict, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->LevelSelectScene.ScoreRect), &r, &(pGameWindow->LevelSelectScene.ScoreRect));
    Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale, &r);
    ConcatenateRect(&(pGameWindow->LevelSelectScene.ScoreRect), &r, &(pGameWindow->LevelSelectScene.ScoreRect));
    
    GetBoxRect(pContentRect, Bottom, &r);
    CenterRect(&r, &(pGameWindow->LevelSelectScene.ScoreRect));
    
    // Setup previous button
    GetPictureRect(pGameWindow->Bitmaps.NextButtonPict, &(pGameWindow->LevelSelectScene.PrevButtonRect));
    
    GetBoxRect(pContentRect, BottomLeft, &r);
    CenterRect(&r, &(pGameWindow->LevelSelectScene.PrevButtonRect));
    
    // Setup next button
    GetPictureRect(pGameWindow->Bitmaps.NextButtonPict, &(pGameWindow->LevelSelectScene.NextButtonRect));
    
    GetBoxRect(pContentRect, BottomRight, &r);
    CenterRect(&r, &(pGameWindow->LevelSelectScene.NextButtonRect));
    
    // Setup LevelGrid
    pGameWindow->LevelSelectScene.LevelGridRect.top = 0;
    pGameWindow->LevelSelectScene.LevelGridRect.bottom = (LevelRowCount * (LevelHeight + LevelMargin)) - LevelMargin;
    pGameWindow->LevelSelectScene.LevelGridRect.left = 0;
    pGameWindow->LevelSelectScene.LevelGridRect.right = (LevelColumnCount * (LevelWidth + LevelMargin)) - LevelMargin;
    CenterRect(pContentRect, &(pGameWindow->LevelSelectScene.LevelGridRect));
}

void LevelSelectScene_SetLevelRect(const GameWindow *pGameWindow, Rect *pRect, const int8_t i)
{
    int8_t c, r;
    c = i % LevelColumnCount;
    r = i / LevelColumnCount;
        
    pRect->top = pGameWindow->LevelSelectScene.LevelGridRect.top + (r * (LevelHeight + LevelMargin));
    pRect->bottom = pRect->top + LevelHeight;
    pRect->left = pGameWindow->LevelSelectScene.LevelGridRect.left + (c * (LevelWidth + LevelMargin));
    pRect->right = pRect->left + LevelWidth;
}

void LevelSelectScene_Draw(const GameWindow *pGameWindow, bool fullRefresh)
{
    int8_t i, level;
    Rect levelRect, levelTextRect, levelHalfStarsRect, r;
    
    // Draw set
    if (fullRefresh)
    {
        MoveTo(pGameWindow->LevelSelectScene.SetRect.left, pGameWindow->LevelSelectScene.SetRect.top);
        if (pGameWindow->Engine.SetB)
        {
            Bitmaps_DrawBChar(&(pGameWindow->Bitmaps), SetTextScale);
        }
        else
        {
            Bitmaps_DrawAChar(&(pGameWindow->Bitmaps), SetTextScale);
        }
    }
    
    // Draw score
    if (fullRefresh)
    {
        MoveTo(pGameWindow->LevelSelectScene.ScoreRect.left, pGameWindow->LevelSelectScene.ScoreRect.top);
        Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), GameEngine_GetTotalScore(&(pGameWindow->Engine)), ScoreTextScale);
        Bitmaps_DrawSlashChar(&(pGameWindow->Bitmaps), ScoreTextScale);
        Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), PerfectScore, ScoreTextScale);
    }
    
    // Draw prev button
    if (fullRefresh)
    {
        DrawPicture(pGameWindow->Bitmaps.PrevButtonPict, &(pGameWindow->LevelSelectScene.PrevButtonRect));
    }
    
    // Draw next button
    if ((pGameWindow->LevelSelectScene.PageNumber + 1) * LevelsPerPage < LevelCount)
    {
        DrawPicture(pGameWindow->Bitmaps.NextButtonPict, &(pGameWindow->LevelSelectScene.NextButtonRect));
    }
    else
    {
        FillRect(&(pGameWindow->LevelSelectScene.NextButtonRect), WindowPattern);
    }
        
    // Draw levels
    for (i = 0; i < LevelsPerPage; i++)
    {
        level = i + (LevelsPerPage * pGameWindow->LevelSelectScene.PageNumber);
        
        LevelSelectScene_SetLevelRect(pGameWindow, &levelRect, i);
        
        if (!fullRefresh)
        {
            FillRect(&levelRect, WindowPattern);
        }
        
        if (level < LevelCount)
        {
            // Draw level number
            Bitmaps_GetNumberRect(&(pGameWindow->Bitmaps), 1 + level, LevelTextScale, &levelTextRect);
            
            GetBoxRect(&levelRect, Top, &r);
            GetBoxRect(&r, Bottom, &r);
            CenterRect(&r, &levelTextRect);
            
            MoveTo(levelTextRect.left, levelTextRect.top);
            Bitmaps_DrawNumber(&(pGameWindow->Bitmaps), 1 + level, LevelTextScale);
            
            if (GameEngine_IsEnabled(&(pGameWindow->Engine), level))
            {
                // Draw half-stars
                Bitmaps_GetHalfStarsRect(&(pGameWindow->Bitmaps), MaxStars, LevelTextScale, &levelHalfStarsRect);
        
                GetBoxRect(&levelRect, Bottom, &r);
                GetBoxRect(&r, Top, &r);
                CenterRect(&r, &levelHalfStarsRect);
            
                MoveTo(levelHalfStarsRect.left, levelHalfStarsRect.top);
                Bitmaps_DrawHalfStars(&(pGameWindow->Bitmaps), GameEngine_GetScore(&(pGameWindow->Engine), level), MaxStars, LevelTextScale);
            }
        }
    }
}

void LevelSelectScene_Click(GameWindow *pGameWindow, const Point *pPosition)
{
    int8_t i, level;
    Rect levelRect;
    
    if (PtInRect(*pPosition, &(pGameWindow->LevelSelectScene.LevelGridRect)))
    {
        // Click within LevelGrid
        for (i = 0; i < LevelsPerPage; i++)
        {
            level = i + (LevelsPerPage * pGameWindow->LevelSelectScene.PageNumber);
        
            if (GameEngine_IsEnabled(&(pGameWindow->Engine), level))
            {
                LevelSelectScene_SetLevelRect(pGameWindow, &levelRect, i);
                
                if (PtInRect(*pPosition, &levelRect))
                {
                    // Clicked on level button
                    GameEngine_StartLevel(&(pGameWindow->Engine), level);
                    GameWindow_SetScene(pGameWindow, Play);
                    Sounds_PlayRetrySnd(&(pGameWindow->Sounds));
                    break;
                }
            }
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->LevelSelectScene.PrevButtonRect)))
    {
        // Clicked on previous button, go to previous page or title scene
        if (pGameWindow->LevelSelectScene.PageNumber > 0)
        {
            pGameWindow->LevelSelectScene.PageNumber--;
            GameWindow_Draw(pGameWindow, false);
        }
        else
        {
            GameWindow_SetScene(pGameWindow, Title);
        }
    }
    else if (PtInRect(*pPosition, &(pGameWindow->LevelSelectScene.NextButtonRect)))
    {
        // Clicked on next button, go to next page if possible
        if ((pGameWindow->LevelSelectScene.PageNumber + 1) * LevelsPerPage < LevelCount)
        {
            pGameWindow->LevelSelectScene.PageNumber++;
            GameWindow_Draw(pGameWindow, false);
        }
    }
}
