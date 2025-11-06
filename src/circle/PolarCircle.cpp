#include <windows.h>
#include <cmath>
#include "../../include/Utils.h"
#include "../../include/CircleAlgorithms.h"

// Forward declaration of DrawPoint from DirectCircle.cpp
void DrawPoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

void DrawPolarCircle(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = R, y = 0;
    DrawPoint(hdc, xc, yc, x, y, c);
    double theta = 0, dtheta = 1.0/R;
    while (x > y) {
        theta += dtheta;
        x = Round(R * cos(theta));
        y = Round(R * sin(theta));
        DrawPoint(hdc, xc, yc, x, y, c);
    }
} 