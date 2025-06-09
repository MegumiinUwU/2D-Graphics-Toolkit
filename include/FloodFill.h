#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <windows.h>

void FloodFillRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF originalColor);

void FloodFillNonRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF originalColor);

struct FloodPoint {
    int x, y;
    FloodPoint(int x = 0, int y = 0) : x(x), y(y) {}
};

#endif //FLOODFILL_H
