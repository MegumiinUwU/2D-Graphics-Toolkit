#include <windows.h>
#include <cmath>
#include "../../include/Utils.h"
#include "../../include/CircleAlgorithms.h"

void DrawPoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, xc+x, yc+y, c);
    SetPixel(hdc, xc-x, yc+y, c);
    SetPixel(hdc, xc-x, yc-y, c);
    SetPixel(hdc, xc+x, yc-y, c);
    SetPixel(hdc, xc+y, yc+x, c);
    SetPixel(hdc, xc-y, yc+x, c);
    SetPixel(hdc, xc-y, yc-x, c);
    SetPixel(hdc, xc+y, yc-x, c);
}

void DrawDirectCircle(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R;
    DrawPoint(hdc, xc, yc, x, y, c);
    while (x < y) {
        x++;
        y = Round(sqrt(R*R - x*x));
        DrawPoint(hdc, xc, yc, x, y, c);
    }
} 