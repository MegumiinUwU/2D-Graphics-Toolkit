#include <windows.h>

// Forward declaration of DrawPoint from DirectCircle.cpp
void DrawPoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

void DrawCircleDDA1(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R, d = 1 - R;
    int d1 = 3, d2 = 5 - 2 * R;
    DrawPoint(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += d1; d1 += 2; d2 += 2; x++;
        } else {
            d += d2; d1 += 2; d2 += 4; x++; y--;
        }
        DrawPoint(hdc, xc, yc, x, y, c);
    }
} 