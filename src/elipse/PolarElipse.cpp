#include <windows.h>
#include <cmath>
#include "../../include/EllipseAlgorithms.h"
#include "../../include/Utils.h"



void DrawPolarEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
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