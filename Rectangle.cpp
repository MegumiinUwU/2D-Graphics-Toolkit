#include <windows.h>
#include <cmath>
#include "LineAlgorithms.h"


void DrawRectangle(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF c) {
    
    int halfWidth = abs(vertexX - centerX);
    int halfHeight = abs(vertexY - centerY);
    
    int left = centerX - halfWidth;
    int right = centerX + halfWidth;
    int top = centerY - halfHeight;
    int bottom = centerY + halfHeight;
    
    DrawLineBresenham(hdc, left, top, right, top, c);
    DrawLineBresenham(hdc, right, top, right, bottom, c);
    DrawLineBresenham(hdc, right, bottom, left, bottom, c);
    DrawLineBresenham(hdc, left, bottom, left, top, c);
}
