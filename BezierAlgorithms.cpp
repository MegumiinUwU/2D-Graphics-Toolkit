#include "BezierAlgorithms.h"
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

void FillRectangleWithHorizontalBezier(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF color) {
    // Calculate rectangle boundaries the same way as DrawRectangle
    int halfWidth = abs(vertexX - centerX);
    int halfHeight = abs(vertexY - centerY);
    
    int left = centerX - halfWidth;
    int right = centerX + halfWidth;
    int top = centerY - halfHeight;
    int bottom = centerY + halfHeight;
    
    int width = right - left;
    int numpoints = std::max(2, width + 1);
    
    int spacing = 1; // Vertical spacing between horizontal Bezier curves
    
    // Draw horizontal Bezier curves from top to bottom
    for (int y = top; y <= bottom; y += spacing) {
        // Create 4 control points for a cubic Bezier curve
        BezierPoint controlPoints[4];
        
        // Start point (left side)
        controlPoints[0] = BezierPoint(left, y);
        
        // Control point 1 (1/3 of the way across)
        controlPoints[1] = BezierPoint(left + width / 3.0, y);
        
        // Control point 2 (2/3 of the way across)
        controlPoints[2] = BezierPoint(left + 2 * width / 3.0, y);
        
        // End point (right side)
        controlPoints[3] = BezierPoint(right, y);
        
        // Draw the horizontal Bezier curve
        DrawBezierCurve(hdc, controlPoints, 4, numpoints, color);
    }
}