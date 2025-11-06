#ifndef POLYGONALGORITHMS_H
#define POLYGONALGORITHMS_H

#include "LineAlgorithms.h"
#include "Point.h"
#include <vector>

using namespace std;

void DrawPolygon(HDC hdc , vector<Point> points , COLORREF c);

void DrawSquare(HDC hdc, int centerX, int centerY, int halfSize, COLORREF c);

void DrawRectangle(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF c);


#endif //POLYGONALGORITHMS_H
