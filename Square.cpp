#include <windows.h>
#include <cmath>
#include "LineAlgorithms.h"


void DrawSquare(HDC hdc, int centerX, int centerY, int halfSize, COLORREF c) {
   
    int left = centerX - halfSize;
    int right = centerX + halfSize;
    int top = centerY - halfSize;
    int bottom = centerY + halfSize;
    
    DrawLineBresenham(hdc, left, top, right, top, c);      
    DrawLineBresenham(hdc, right, top, right, bottom, c);  
    DrawLineBresenham(hdc, right, bottom, left, bottom, c); 
    DrawLineBresenham(hdc, left, bottom, left, top, c);   
}
