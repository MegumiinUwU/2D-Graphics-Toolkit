#include <windows.h>
#include <cmath>
#include "../../include/EllipseAlgorithms.h"
#include "../../include/Utils.h"

void DrawEllipsePoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, xc+x, yc+y, c);
    SetPixel(hdc, xc-x, yc+y, c);
    SetPixel(hdc, xc-x, yc-y, c);
    SetPixel(hdc, xc+x, yc-y, c);
}

void DrawDirectEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    int x, y;

    // Region 1: |slope| <= 1, loop on x
    for (x = 0; x <= a; x++) {
        y = Round(b * sqrt(1.0 - (x*x)/(double)(a*a)));
        DrawEllipsePoint(hdc, xc, yc, x, y, c);

        // Check if slope > 1, then break
        if (a*a * (y-0.5) < b*b * (x+1)) break;
    }

    // Region 2: |slope| > 1, loop on y
    for (y = Round(b * sqrt(1.0 - (x*x)/(double)(a*a))); y >= 0; y--) {
        x = Round(a * sqrt(1.0 - (y*y)/(double)(b*b)));
        DrawEllipsePoint(hdc, xc, yc, x, y, c);
    }
}