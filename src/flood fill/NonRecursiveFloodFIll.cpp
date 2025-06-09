#include "../../include/FloodFill.h"
#include <stack>

void FloodFillNonRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF originalColor) {
    std::stack<FloodPoint> stack;
    stack.push(FloodPoint(x, y));

    while (!stack.empty()) {
        FloodPoint current = stack.top();
        stack.pop();

        int cx = current.x;
        int cy = current.y;

        if (GetPixel(hdc, cx, cy) == originalColor && GetPixel(hdc, cx, cy) != fillColor) {
            SetPixel(hdc, cx, cy, fillColor);

            stack.push(FloodPoint(cx + 1, cy));
            stack.push(FloodPoint(cx - 1, cy));
            stack.push(FloodPoint(cx, cy + 1));
            stack.push(FloodPoint(cx, cy - 1));
        }
    }
}