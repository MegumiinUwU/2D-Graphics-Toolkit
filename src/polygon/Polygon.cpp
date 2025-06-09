#include <windows.h>
#include "../../include/PolygonAlgorithms.h"

void DrawPolygon(HDC hdc , vector<Point> points , COLORREF c) {

    // Draw polygon outline
    for (size_t i = 0; i < points.size() - 1; i++) {
        DrawLineBresenham(hdc, points[i].x, points[i].y,
                         points[i + 1].x, points[i + 1].y, c);
    }
    // Close the polygon
    DrawLineBresenham(hdc, points.back().x, points.back().y,
                     points[0].x, points[0].y, c);


}