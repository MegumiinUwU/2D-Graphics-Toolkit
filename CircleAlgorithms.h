#ifndef CIRCLE_ALGORITHMS_H
#define CIRCLE_ALGORITHMS_H

#include <windows.h>

// Circle drawing algorithm declarations
void DrawCircle1(HDC hdc, int xc, int yc, int R, COLORREF c);        // Direct Circle
void DrawCircle2(HDC hdc, int xc, int yc, int R, COLORREF c);        // Polar Circle
void DrawCircle3(HDC hdc, int xc, int yc, int R, COLORREF c);        // Iterative Polar Circle
void DrawCircleBresenham(HDC hdc, int xc, int yc, int R, COLORREF c); // Midpoint Circle
void DrawCircleDDA1(HDC hdc, int xc, int yc, int R, COLORREF c);     // Modified Midpoint Circle

// Helper function
void DrawPoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

#endif // CIRCLE_ALGORITHMS_H 