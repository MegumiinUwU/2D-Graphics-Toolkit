#include "../../include/CircleFillAlgorithms.h"

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