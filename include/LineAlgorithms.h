#ifndef LINE_ALGORITHMS_H
#define LINE_ALGORITHMS_H

#include <windows.h>

// Line drawing algorithm declarations
void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
void DrawLineBresenham(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
void DrawLineParametric(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
void DrawHorizontalLine(HDC hdc, int x1, int x2, int y, COLORREF c);
void drawLineBresenhamPolygon(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

#endif // LINE_ALGORITHMS_H 