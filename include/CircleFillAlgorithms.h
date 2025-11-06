#ifndef CIRCLE_FILL_ALGORITHMS_H
#define CIRCLE_FILL_ALGORITHMS_H

#include <windows.h>
#include "CircleAlgorithms.h"
#include "LineAlgorithms.h"



// 1. Fill circle with lines (fill one octal with lines, rest with 8-point symmetry)
void FillCircleWithLines(HDC hdc, int xc, int yc, int R, COLORREF c);

// 2. Fill quarter of circle only
void FillQuarterCircle(HDC hdc, int xc, int yc, int R, COLORREF c);

// 3. Fill circle with solid pixels (no gaps)
void FillCircleWithCircles(HDC hdc, int xc, int yc, int R, COLORREF c);

// Helper function to fill one octal with lines
void FillOctalWithLines(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

// Helper function to fill using 8-point symmetry with lines
void FillWithSymmetricLines(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

#endif // CIRCLE_FILL_ALGORITHMS_H 