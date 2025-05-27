#include <windows.h>
#include <cmath>
#include <algorithm>

void DrawLineParametric(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    double alpha_x = x2 - x1, alpha_y = y2 - y1;
    double steps = 1.0 / (std::max(abs(alpha_x), abs(alpha_y)));

    for (double i = 0.0; i <= 1.0; i += steps) {
        int x = x1 + (int)(alpha_x * i);
        int y = y1 + (int)(alpha_y * i);
        SetPixel(hdc, x, y, c);
    }
} 