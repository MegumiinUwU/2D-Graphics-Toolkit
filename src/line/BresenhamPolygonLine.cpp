#include "../../include/LineAlgorithms.h"


void drawLineBresenhamPolygon(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int x = x1, y = y1;

    SetPixel(hdc, x, y, c);

    if(abs(dx) > abs(dy)) {
        int d = sy * dx - 2 * sx * dy;
        int d1 = 2 * (sy * dx - sx * dy);
        int d2 = -2 * sx * dy;

        while(x != x2) {
            if(dx * dy * d < 0) {
                d += d1;
                y += sy;
            } else {
                d += d2;
            }
            x += sx;
            SetPixel(hdc, x, y, c);
        }
    } else {
        int d = 2 * sy * dx - sx * dy;
        int d1 = 2 * (sy * dx - sx * dy);
        int d2 = 2 * sy * dx;

        while(y != y2) {
            if(dx * dy * d > 0) {
                d += d1;
                x += sx;
            } else {
                d += d2;
            }
            y += sy;
            SetPixel(hdc, x, y, c);
        }
    }
}