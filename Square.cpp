#include <windows.h>
#include <cmath>
#include "LineAlgorithms.h"

// Function to draw a square given center point and distance to edge
void DrawSquare(HDC hdc, int centerX, int centerY, int halfSize, COLORREF c) {
    // Calculate the four corners of the square
    // halfSize is the distance from center to any edge
    int left = centerX - halfSize;
    int right = centerX + halfSize;
    int top = centerY - halfSize;
    int bottom = centerY + halfSize;
    
    // Draw the four sides of the square using Bresenham line algorithm
    DrawLineBresenham(hdc, left, top, right, top, c);       // Top edge
    DrawLineBresenham(hdc, right, top, right, bottom, c);   // Right edge
    DrawLineBresenham(hdc, right, bottom, left, bottom, c); // Bottom edge
    DrawLineBresenham(hdc, left, bottom, left, top, c);     // Left edge
}
