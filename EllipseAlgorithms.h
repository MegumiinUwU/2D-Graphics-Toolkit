#ifndef ELLIPSE_ALGORITHMS_H
#define ELLIPSE_ALGORITHMS_H

#include <windows.h>
#include <cmath>
#include <algorithm>
#include "Utils.h"

#ifndef PI
#define PI 3.14159265359
#endif

// Helper function to draw ellipse points in all four quadrants
void DrawEllipsePoint(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, xc+x, yc+y, c);
    SetPixel(hdc, xc-x, yc+y, c);
    SetPixel(hdc, xc-x, yc-y, c);
    SetPixel(hdc, xc+x, yc-y, c);
}

// Ellipse Direct Algorithm
void DrawEllipse1(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
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

// Ellipse Polar Algorithm
void DrawEllipse2(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    double theta = 0;
    double dtheta = 1.0 / std::max(a, b);  // Adaptive step size
    int x, y;

    // Region 1: |slope| <= 1
    while (theta <= PI/2) {
        x = Round(a * cos(theta));
        y = Round(b * sin(theta));
        DrawEllipsePoint(hdc, xc, yc, x, y, c);

        // Check slope condition: dy/dx = -(b²x)/(a²y)
        // |slope| > 1 when b²x > a²y
        if (b*b*x > a*a*y && y > 0) break;

        theta += dtheta;
    }

    // Continue from current point, adjusting step for y-dominant region
    dtheta = 1.0 / std::max((a*b/(double)a), (double)b);  // Finer steps for y-dominant
    while (theta <= PI/2) {
        x = Round(a * cos(theta));
        y = Round(b * sin(theta));
        DrawEllipsePoint(hdc, xc, yc, x, y, c);
        theta += dtheta;
    }
}

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

#endif // ELLIPSE_ALGORITHMS_H 