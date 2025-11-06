#ifndef ELLIPSE_ALGORITHMS_H
#define ELLIPSE_ALGORITHMS_H

#include <windows.h>

#ifndef PI
#define PI 3.14159265359
#endif

// Helper function to draw ellipse points in all four quadrants
void DrawEllipsePoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

// Ellipse Direct Algorithm
void DrawDirectEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c);

// Ellipse Polar Algorithm
void DrawPolarEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c);

// Ellipse Midpoint Algorithm (Bresenham)
void DrawEllipseBresenham(HDC hdc, int xc, int yc, int a, int b, COLORREF c);

#endif // ELLIPSE_ALGORITHMS_H 