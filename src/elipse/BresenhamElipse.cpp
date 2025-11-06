#include <windows.h>
#include "../../include/EllipseAlgorithms.h"


// Ellipse Midpoint Algorithm (Bresenham)
void DrawEllipseBresenham(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    int x = 0, y = b;
    long a2 = a * a, b2 = b * b;
    long d;

    // Region 1: |slope| <= 1 (x-dominant)
    d = b2 - a2 * b + a2 / 4;
    DrawEllipsePoint(hdc, xc, yc, x, y, c);

    while (b2 * x < a2 * y) {
        if (d < 0) {
            d += b2 * (2 * x + 3);
            x++;
        } else {
            d += b2 * (2 * x + 3) + a2 * (-2 * y + 2);
            x++; y--;
        }
        DrawEllipsePoint(hdc, xc, yc, x, y, c);
    }

    // Region 2: |slope| > 1 (y-dominant)
    d = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;

    while (y >= 0) {
        if (d < 0) {
            d += b2 * (2 * x + 2) + a2 * (-2 * y + 3);
            x++; y--;
        } else {
            d += a2 * (-2 * y + 3);
            y--;
        }
        DrawEllipsePoint(hdc, xc, yc, x, y, c);
    }
}