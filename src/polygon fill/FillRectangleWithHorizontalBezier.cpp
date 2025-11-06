#include "../../include/PolygonFillAlgorithms.h"
#include "../../include/Bezier.h"


void FillRectangleWithHorizontalBezier(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF color) {

    int halfWidth = abs(vertexX - centerX);
    int halfHeight = abs(vertexY - centerY);
    
    int left = centerX - halfWidth;
    int right = centerX + halfWidth;
    int top = centerY - halfHeight;
    int bottom = centerY + halfHeight;
    
    int width = right - left;
    int numpoints = std::max(2, width + 1);
    
    int spacing = 1;
    

    for (int y = top; y <= bottom; y += spacing) {
       
        BezierPoint controlPoints[4];
        
        
        controlPoints[0] = BezierPoint(left, y);
        
        controlPoints[1] = BezierPoint(left + width / 3.0, y);
    
        controlPoints[2] = BezierPoint(left + 2 * width / 3.0, y);
        
        controlPoints[3] = BezierPoint(right, y);
        
        DrawBezierCurve(hdc, controlPoints, 4, numpoints, color);
    }
}