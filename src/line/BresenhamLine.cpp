#include <windows.h>
#include <cmath>
#include "../../include/LineAlgorithms.h"

void DrawLineBresenham(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    // Handle negative slopes and ensure we're drawing in positive direction
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;  // Step direction for x
    int sy = (y1 < y2) ? 1 : -1;  // Step direction for y

    int x = x1;
    int y = y1;

    // Set starting pixel
    SetPixel(hdc, x, y, c);

    // Case 1: dx >= dy (slope <= 1)
    if (dx >= dy) {
        int d = dx - 2 * dy;
        int d1 = -2 * dy;
        int d2 = 2 * (dx - dy);

        while (x != x2) {
            if (d > 0) {
                d += d1;
                x += sx;
            }
            else {
                d += d2;
                x += sx;
                y += sy;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    // Case 2: dy > dx (slope > 1)
    else {
        int d = dy - 2 * dx;
        int d1 = -2 * dx;
        int d2 = 2 * (dy - dx);

        while (y != y2) {
            if (d > 0) {
                d += d1;
                y += sy;
            }
            else {
                d += d2;
                y += sy;
                x += sx;
            }
            SetPixel(hdc, x, y, c);
        }
    }
} 