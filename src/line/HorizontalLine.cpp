#include <windows.h>
#include "../../include/LineAlgorithms.h"

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