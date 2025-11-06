#ifndef BEZIER_ALGORITHMS_H
#define BEZIER_ALGORITHMS_H

#include <windows.h>

struct BezierPoint {
    double x, y;
    BezierPoint(double x = 0, double y = 0) : x(x), y(y) {}
};

BezierPoint RecBezier(double t, BezierPoint pts[], int si, int ei);

void DrawBezierCurve(HDC hdc, BezierPoint pts[], int numPoints, int steps, COLORREF color);

#endif