#pragma once
#include <vector>

// Simple Point struct (adapt as needed)
struct Point2 {
    double x, y;
    Point2(double x = 0, double y = 0) : x(x), y(y) {}
    int getIntX() const { return static_cast<int>(x + 0.5); }
    int getIntY() const { return static_cast<int>(y + 0.5); }
};

// Rectangle Point Clipping
bool ClipPointRectangle(int x, int y, int xLeft, int xRight, int yTop, int yBottom);

// Rectangle Line Clipping (Cohen-Sutherland)
bool CohenSutherlandLineClip(int& x1, int& y1, int& x2, int& y2, int xLeft, int xRight, int yTop, int yBottom);

// Rectangle Polygon Clipping (Sutherland-Hodgman)
std::vector<Point2> SutherlandHodgmanPolygonClip(const std::vector<Point2>& polygon, int xLeft, int xRight, int yTop, int yBottom);

// Square Point Clipping (wrapper)
bool ClipPointSquare(int x, int y, int xLeft, int size);

// Square Line Clipping (wrapper)
bool SquareLineClip(int& x1, int& y1, int& x2, int& y2, int xLeft, int yTop, int size);

// Circle Point Clipping
bool ClipPointCircle(int x, int y, int xc, int yc, int r);

// Circle Line Clipping
bool CircleLineClip(int& x1, int& y1, int& x2, int& y2, int xc, int yc, int r); 