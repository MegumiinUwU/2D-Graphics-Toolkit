#include "HermiteAlgorithms.h"
#include <cmath>
#include <algorithm>


void GetHermiteCoeff(double p0, double t0, double p1, double t1, double* coeffs) {
    coeffs[0] = 2*p0 - 2*p1 + t0 + t1;  
    coeffs[1] = -3*p0 + 3*p1 - 2*t0 - t1;  
    coeffs[2] = t0;                     
    coeffs[3] = p0;
}


double EvaluatePolynomial(double* coeffs, double t) {
    return coeffs[0]*t*t*t + coeffs[1]*t*t + coeffs[2]*t + coeffs[3];
}

void DrawHermiteCurve(
    HDC hdc,
    HermitePoint P0, HermitePoint T0,
    HermitePoint P1, HermitePoint T1,
    int numpoints,
    COLORREF color)
{
    if (numpoints < 2) return;

    double xcoeff[4], ycoeff[4];
    GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x, xcoeff);
    GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y, ycoeff);

    double dx = P1.x - P0.x;
    double dy = P1.y - P0.y;
    double distance = sqrt(dx * dx + dy * dy);
    
    int adaptivePoints = std::max(numpoints, std::min(1000, (int)(distance * 2) + 10));
    
    double dt = 1.0 / (adaptivePoints - 1);

    for (int i = 0; i < adaptivePoints; ++i) {
        double t = i * dt;
        int x = (int)round(EvaluatePolynomial(xcoeff, t));
        int y = (int)round(EvaluatePolynomial(ycoeff, t));
        SetPixel(hdc, x, y, color);
    }
}

void FillSquareWithVerticalHermite(
    HDC hdc,
    int centerX,
    int centerY,
    int halfSize,
    COLORREF color)
{
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

void DrawCardinalSpline(HDC hdc, HermitePoint* points, int n, double c, int numPointsPerSegment, COLORREF color) {
    if (n < 2) return;

    HermitePoint* tangents = new HermitePoint[n];

    // First tangent
    tangents[0].x = (c / 2.0) * (points[1].x - points[0].x);
    tangents[0].y = (c / 2.0) * (points[1].y - points[0].y);

    // Middle tangents
    for (int i = 1; i < n - 1; ++i) {
        tangents[i].x = (c / 2.0) * (points[i + 1].x - points[i - 1].x);
        tangents[i].y = (c / 2.0) * (points[i + 1].y - points[i - 1].y);
    }

    // Last tangent
    tangents[n - 1].x = (c / 2.0) * (points[n - 1].x - points[n - 2].x);
    tangents[n - 1].y = (c / 2.0) * (points[n - 1].y - points[n - 2].y);

    for (int i = 0; i < n - 1; ++i) {
    
        double dx = points[i + 1].x - points[i].x;
        double dy = points[i + 1].y - points[i].y;
        double distance = sqrt(dx * dx + dy * dy);
        
    
        int adaptivePoints = std::max(numPointsPerSegment, std::min(500, (int)(distance * 1.5) + 20));
        
        DrawHermiteCurve(hdc,
                         points[i], tangents[i],
                         points[i + 1], tangents[i + 1],
                         adaptivePoints,
                         color);
    }

    delete[] tangents;
}
