#ifndef CIRCLE_FILL_ALGORITHMS_H
#define CIRCLE_FILL_ALGORITHMS_H

#include <windows.h>
#include <cmath>
#include "Utils.h"
#include "CircleAlgorithms.h"



// 1. Fill circle with lines (fill one octal with lines, rest with 8-point symmetry)
void FillCircleWithLines(HDC hdc, int xc, int yc, int R, COLORREF c);

// 2. Fill quarter of circle only
void FillQuarterCircle(HDC hdc, int xc, int yc, int R, COLORREF c);

// 3. Fill circle with solid pixels (no gaps)
void FillCircleWithCircles(HDC hdc, int xc, int yc, int R, COLORREF c);

// Helper function to draw horizontal line
void DrawHorizontalLine(HDC hdc, int x1, int x2, int y, COLORREF c) {
    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    for (int x = x1; x <= x2; x++) {
        SetPixel(hdc, x, y, c);
    }
}

// Helper function to fill one octal with lines
void FillOctalWithLines(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    // Fill the first octal (0 to 45 degrees) with horizontal lines
    if (x <= y) {
        // Draw horizontal line from center to the circle point in first octal
        DrawHorizontalLine(hdc, xc, xc + x, yc + y, c);
    }
}

// Helper function to fill using 8-point symmetry with lines
void FillWithSymmetricLines(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    DrawHorizontalLine(hdc, xc - x, xc + x, yc + y, c);  
    DrawHorizontalLine(hdc, xc - x, xc + x, yc - y, c);  
    DrawHorizontalLine(hdc, xc - y, xc + y, yc + x, c);  
    DrawHorizontalLine(hdc, xc - y, xc + y, yc - x, c);  
}

// Main algorithm: Fill circle with lines
void FillCircleWithLines(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R;
    int d = 1 - R;
    
    FillOctalWithLines(hdc, xc, yc, x, y, c);
    FillWithSymmetricLines(hdc, xc, yc, x, y, c);
    
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
            x++;
        } else {
            d += 2 * (x - y) + 5;
            x++;
            y--;
        }
        
        FillOctalWithLines(hdc, xc, yc, x, y, c);
        FillWithSymmetricLines(hdc, xc, yc, x, y, c);
    }
}

// Fill quarter of circle only (first quadrant)
void FillQuarterCircle(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R;
    int d = 1 - R;
    
    // Fill first quarter only with horizontal lines
    DrawHorizontalLine(hdc, xc, xc + x, yc - y, c);
    
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
            x++;
        } else {
            d += 2 * (x - y) + 5;
            x++;
            y--;
        }
        
        // Fill only the first quarter (top-right quadrant)
        // Draw horizontal lines from center to circle boundary
        if (y >= 0) {
            DrawHorizontalLine(hdc, xc, xc + x, yc - y, c);
        }
        if (x <= y && x >= 0) {
            DrawHorizontalLine(hdc, xc, xc + y, yc - x, c);
        }
    }
}

// Fill circle with concentric circles (using actual circle algorithms)
void FillCircleWithCircles(HDC hdc, int xc, int yc, int R, COLORREF c) {
    // Draw concentric circles from center outward using existing circle algorithm
    for (int r = 1; r <= R; r++) {
        DrawCircleBresenham(hdc, xc, yc, r, c);
    }
}

// Helper function to check if a point is inside a circle
bool IsPointInCircle(int px, int py, int cx, int cy, int radius) {
    int dx = px - cx;
    int dy = py - cy;
    return (dx * dx + dy * dy) <= (radius * radius);
}

#endif // CIRCLE_FILL_ALGORITHMS_H 