#include "../../include/CircleFillAlgorithms.h"

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
