#include <windows.h>
#include <cmath>
#include "../../include/Utils.h"
#include "../../include/LineAlgorithms.h"

void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1, dy = y2 - y1;
    SetPixel(hdc, x1, y1, c);
    
    if (abs(dx) >= abs(dy))
    {
        // Ensure we draw from left to right by swapping if needed
        if (x1 > x2) {
            // Swap points to ensure x1 < x2
            int tempX = x1, tempY = y1;
            x1 = x2; y1 = y2;
            x2 = tempX; y2 = tempY;
            dx = x2 - x1; dy = y2 - y1;
        }
        
        double m = (double)dy / dx;
        int x = x1;
        double y = y1;
        while (x < x2)
        {
            x++;
            y += m;
            SetPixel(hdc, x, Round(y), c);
        }
    }
    else {
        // Ensure we draw from bottom to top by swapping if needed
        if (y1 > y2) {
            // Swap points to ensure y1 < y2
            int tempX = x1, tempY = y1;
            x1 = x2; y1 = y2;
            x2 = tempX; y2 = tempY;
            dx = x2 - x1; dy = y2 - y1;
        }
        
        double mi = (double)dx / dy;
        int y = y1;
        double x = x1;
        while (y < y2)
        {
            y++;
            x += mi;
            SetPixel(hdc, Round(x), y, c);
        }
    }
} 