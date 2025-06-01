#include <windows.h>
#include <cmath>
#include "LineAlgorithms.h"

// Function to draw a rectangle given center point and one vertex
void DrawRectangle(HDC hdc, int centerX, int centerY, int vertexX, int vertexY, COLORREF c) {
    // Calculate the half-width and half-height from center to vertex
    int halfWidth = abs(vertexX - centerX);
    int halfHeight = abs(vertexY - centerY);
    
    // Calculate the four corners of the rectangle
    int left = centerX - halfWidth;
    int right = centerX + halfWidth;
    int top = centerY - halfHeight;
    int bottom = centerY + halfHeight;
    
    // Draw the four sides of the rectangle using Bresenham line algorithm
    DrawLineBresenham(hdc, left, top, right, top, c);       // Top edge
    DrawLineBresenham(hdc, right, top, right, bottom, c);   // Right edge
    DrawLineBresenham(hdc, right, bottom, left, bottom, c); // Bottom edge
    DrawLineBresenham(hdc, left, bottom, left, top, c);     // Left edge
}
