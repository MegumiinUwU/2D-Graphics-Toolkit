#include <windows.h>
#include <cmath>
#include "../../include/Utils.h"
#include "../../include/CircleAlgorithms.h"

// Forward declaration of DrawPoint from DirectCircle.cpp
void DrawPoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c);

void DrawIterativePolarCircle(HDC hdc, int xc, int yc, int R, COLORREF c) {
    double x = R, y = 0;
    double dtheta = 1.0/R;
    double ct = cos(dtheta), st = sin(dtheta);
    DrawPoint(hdc, xc, yc, R, 0, c);
    while (x > y) {
        double x1 = x * ct - y * st;
        y = x * st + y * ct;
        x = x1;
        DrawPoint(hdc, xc, yc, Round(x), Round(y), c);
    }
} 