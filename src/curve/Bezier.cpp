#include "../../include/Bezier.h"
#include <cmath>
#include <algorithm>

BezierPoint RecBezier(double t, BezierPoint pts[], int si, int ei) {
    if (si == ei) {
        return pts[si];
    }
    
    BezierPoint p1 = RecBezier(t, pts, si, ei - 1);
    BezierPoint p2 = RecBezier(t, pts, si + 1, ei);
    
    BezierPoint result;
    result.x = (1 - t) * p1.x + t * p2.x;
    result.y = (1 - t) * p1.y + t * p2.y;
    
    return result;
}

void DrawBezierCurve(HDC hdc, BezierPoint pts[], int numPoints, int steps, COLORREF color) {
    if (numPoints < 2 || steps < 1) return;
    
    double stepSize = 1.0 / steps;
    for (double t = 0; t <= 1.0; t += stepSize) {
        BezierPoint p = RecBezier(t, pts, 0, numPoints - 1);
        SetPixel(hdc, (int)round(p.x), (int)round(p.y), color);
    }
}