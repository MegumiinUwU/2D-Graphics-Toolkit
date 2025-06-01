#ifndef RECTANGLE_ALGORITHMS_H
#define RECTANGLE_ALGORITHMS_H

#include <windows.h>

void DrawRectangle(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF c);

void FillRectangleWithHorizontalBezier(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF color);

#endif
