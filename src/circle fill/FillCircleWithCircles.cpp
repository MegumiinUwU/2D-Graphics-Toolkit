#include "../../include/CircleFillAlgorithms.h"

// Fill circle with concentric circles (using actual circle algorithms)
void FillCircleWithCircles(HDC hdc, int xc, int yc, int R, COLORREF c) {
    // Draw concentric circles from center outward using existing circle algorithm
    for (int r = 1; r <= R; r+=1) {
        DrawCircleBresenham(hdc, xc, yc, r, c);
    }
}