#include "../../include/PolygonFillAlgorithms.h"
#include "../../include/Hermite.h"


void FillSquareWithVerticalHermite(HDC hdc, int centerX, int centerY, int halfSize, COLORREF color) {
    int left   = centerX - halfSize;
    int right  = centerX + halfSize;
    int top    = centerY - halfSize;
    int bottom = centerY + halfSize;

    int height = bottom - top;
    int numpoints = std::max(2, height + 1);

    int spacing = 1;

    for (int x = left; x <= right; x += spacing) {
        HermitePoint P0(x, top);
        HermitePoint P1(x, bottom);


        HermitePoint T0(0, height);
        HermitePoint T1(0, height);

        DrawHermiteCurve(hdc, P0, T0, P1, T1, numpoints, color);
    }
}