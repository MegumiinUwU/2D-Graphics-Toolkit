#include <windows.h>
#include "../../include/CircleAlgorithms.h"

// Forward declaration of DrawPoint from DirectCircle.cpp
void DrawPoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

void DrawCircleBresenham(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R, d = 1 - R;
    DrawPoint(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
            x++;
        } else {
            d += 2 * (x - y) + 5;
            x++; y--;
        }
        DrawPoint(hdc, xc, yc, x, y, c);
    }
} 