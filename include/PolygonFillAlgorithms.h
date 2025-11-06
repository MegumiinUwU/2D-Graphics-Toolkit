#ifndef POLYGON_FILL_ALGORITHMS_H
#define POLYGON_FILL_ALGORITHMS_H

#include <windows.h>
#include <algorithm>
#include <list>
#include <cmath>
#include "LineAlgorithms.h"

struct PolygonPoint {
    double x, y;
    PolygonPoint(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Edge {
    int xleft, xright;
};

struct Node {
    double x, minv;
    int ymax;
    Node(double x = 0, double minv = 0, int ymax = 0) : x(x), minv(minv), ymax(ymax) {}
};

typedef Edge EdgeTable[800];
typedef std::list<Node> LList;
typedef LList NonConvexEdgeTable[800];

void ConvexFill(HDC hdc, PolygonPoint p[], int n, COLORREF c);

void NonConvexFill(HDC hdc, PolygonPoint p[], int n, COLORREF c);

void FillRectangleWithHorizontalBezier(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF color);

void FillSquareWithVerticalHermite(HDC hdc, int centerX, int centerY, int halfSize, COLORREF color);



#endif 