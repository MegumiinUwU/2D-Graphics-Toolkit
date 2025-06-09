#include "../../include/CardinalSpline.h"
#include <cmath>
#include <algorithm>

void DrawCardinalSpline(HDC hdc, HermitePoint* points, int n, double c, int numPointsPerSegment, COLORREF color) {
    if (n < 2) return;

    HermitePoint* tangents = new HermitePoint[n];

    // First tangent
    tangents[0].x = (c / 2.0) * (points[1].x - points[0].x);
    tangents[0].y = (c / 2.0) * (points[1].y - points[0].y);

    // Middle tangents
    for (int i = 1; i < n - 1; ++i) {
        tangents[i].x = (c / 2.0) * (points[i + 1].x - points[i - 1].x);
        tangents[i].y = (c / 2.0) * (points[i + 1].y - points[i - 1].y);
    }

    // Last tangent
    tangents[n - 1].x = (c / 2.0) * (points[n - 1].x - points[n - 2].x);
    tangents[n - 1].y = (c / 2.0) * (points[n - 1].y - points[n - 2].y);

    for (int i = 0; i < n - 1; ++i) {
    
        double dx = points[i + 1].x - points[i].x;
        double dy = points[i + 1].y - points[i].y;
        double distance = sqrt(dx * dx + dy * dy);
        
    
        int adaptivePoints = std::max(numPointsPerSegment, std::min(500, (int)(distance * 1.5) + 20));
        
        DrawHermiteCurve(hdc,
                         points[i], tangents[i],
                         points[i + 1], tangents[i + 1],
                         adaptivePoints,
                         color);
    }

    delete[] tangents;
}