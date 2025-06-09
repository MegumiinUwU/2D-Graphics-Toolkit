#include "../../include/FloodFill.h"

void FloodFillRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF originalColor) {
    if (GetPixel(hdc, x, y) != originalColor || GetPixel(hdc, x, y) == fillColor) {
        return;
    }

    SetPixel(hdc, x, y, fillColor);

    FloodFillRecursive(hdc, x + 1, y, fillColor, originalColor);
    FloodFillRecursive(hdc, x - 1, y, fillColor, originalColor);
    FloodFillRecursive(hdc, x, y + 1, fillColor, originalColor);
    FloodFillRecursive(hdc, x, y - 1, fillColor, originalColor);
}