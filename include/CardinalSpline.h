#ifndef CARDINALSPLINE_H
#define CARDINALSPLINE_H

#include <windows.h>
#include "Hermite.h"

void DrawCardinalSpline(HDC hdc, HermitePoint* points, int n, double c, int numPointsPerSegment, COLORREF color);

#endif //CARDINALSPLINE_H
