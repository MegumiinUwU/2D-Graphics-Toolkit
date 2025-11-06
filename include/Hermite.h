#ifndef HERMITE_ALGORITHMS_H
#define HERMITE_ALGORITHMS_H

#include <windows.h>

struct HermitePoint {
    double x, y;
    HermitePoint(double x = 0, double y = 0) : x(x), y(y) {}
};

void DrawHermiteCurve(HDC hdc, HermitePoint P0, HermitePoint T0, HermitePoint P1, HermitePoint T1, int numpoints, COLORREF color);

void GetHermiteCoeff(double p0, double t0, double p1, double t1, double* coeffs);

double EvaluatePolynomial(double* coeffs, double t);

#endif