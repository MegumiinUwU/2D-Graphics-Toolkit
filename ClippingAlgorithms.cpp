#include <vector>
#include <algorithm>
#include <cmath>
#include "ClippingAlgorithms.h"

// Rectangle Point Clipping
bool ClipPointRectangle(int x, int y, int xLeft, int xRight, int yTop, int yBottom) {
    return (x >= xLeft && x <= xRight && y >= yTop && y <= yBottom);
}

// OutCode for Cohen-Sutherland
union OutCode {
    struct {
        unsigned left : 1, right : 1, top : 1, bottom : 1;
    };
    unsigned all : 4;
};

static OutCode GetOutCode(int x, int y, int xLeft, int xRight, int yTop, int yBottom) {
    OutCode out;
    out.all = 0;
    if (x < xLeft) out.left = 1;
    else if (x > xRight) out.right = 1;
    if (y < yTop) out.top = 1;
    else if (y > yBottom) out.bottom = 1;
    return out;
}

static void VIntersect(int x1, int y1, int x2, int y2, int xEdge, int& xi, int& yi) {
    yi = y1 + (xEdge - x1) * (y2 - y1) / (x2 - x1);
    xi = xEdge;
}

static void HIntersect(int x1, int y1, int x2, int y2, int yEdge, int& xi, int& yi) {
    xi = x1 + (yEdge - y1) * (x2 - x1) / (y2 - y1);
    yi = yEdge;
}

// Cohen-Sutherland Line Clipping
bool CohenSutherlandLineClip(int& x1, int& y1, int& x2, int& y2, int xLeft, int xRight, int yTop, int yBottom) {
    OutCode out1 = GetOutCode(x1, y1, xLeft, xRight, yTop, yBottom);
    OutCode out2 = GetOutCode(x2, y2, xLeft, xRight, yTop, yBottom);
    int cx1 = x1, cy1 = y1, cx2 = x2, cy2 = y2;
    while (true) {
        if ((out1.all == 0) && (out2.all == 0)) {
            x1 = cx1; y1 = cy1; x2 = cx2; y2 = cy2;
            return true;
        } else if (out1.all & out2.all) {
            return false;
        } else {
            OutCode outP = out1.all ? out1 : out2;
            int tempX, tempY;
            if (outP.left) {
                VIntersect(cx1, cy1, cx2, cy2, xLeft, tempX, tempY);
            } else if (outP.right) {
                VIntersect(cx1, cy1, cx2, cy2, xRight, tempX, tempY);
            } else if (outP.top) {
                HIntersect(cx1, cy1, cx2, cy2, yTop, tempX, tempY);
            } else if (outP.bottom) {
                HIntersect(cx1, cy1, cx2, cy2, yBottom, tempX, tempY);
            }
            if (outP.all == out1.all) {
                cx1 = tempX; cy1 = tempY;
                out1 = GetOutCode(cx1, cy1, xLeft, xRight, yTop, yBottom);
            } else {
                cx2 = tempX; cy2 = tempY;
                out2 = GetOutCode(cx2, cy2, xLeft, xRight, yTop, yBottom);
            }
        }
    }
}

// Sutherland-Hodgman Polygon Clipping
static Point2 VIntersect(const Point2& v1, const Point2& v2, double xEdge) {
    double yi = v1.y + (xEdge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return Point2(xEdge, yi);
}
static Point2 HIntersect(const Point2& v1, const Point2& v2, double yEdge) {
    double xi = v1.x + (yEdge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return Point2(xi, yEdge);
}
static std::vector<Point2> clipLeft(const std::vector<Point2>& p, double xLeft) {
    int n = p.size();
    Point2 v1 = p[n-1];
    bool in1 = v1.x >= xLeft;
    std::vector<Point2> out;
    for (int i = 0; i < n; i++) {
        Point2 v2 = p[i];
        bool in2 = v2.x >= xLeft;
        if (in1 && in2) out.push_back(v2);
        else if (in1 && !in2) out.push_back(VIntersect(v1, v2, xLeft));
        else if (!in1 && in2) { out.push_back(VIntersect(v1, v2, xLeft)); out.push_back(v2); }
        v1 = v2; in1 = in2;
    }
    return out;
}
static std::vector<Point2> clipRight(const std::vector<Point2>& p, double xRight) {
    int n = p.size();
    Point2 v1 = p[n-1];
    bool in1 = v1.x <= xRight;
    std::vector<Point2> out;
    for (int i = 0; i < n; i++) {
        Point2 v2 = p[i];
        bool in2 = v2.x <= xRight;
        if (in1 && in2) out.push_back(v2);
        else if (in1 && !in2) out.push_back(VIntersect(v1, v2, xRight));
        else if (!in1 && in2) { out.push_back(VIntersect(v1, v2, xRight)); out.push_back(v2); }
        v1 = v2; in1 = in2;
    }
    return out;
}
static std::vector<Point2> clipBottom(const std::vector<Point2>& p, double yBottom) {
    int n = p.size();
    Point2 v1 = p[n-1];
    bool in1 = v1.y <= yBottom;
    std::vector<Point2> out;
    for (int i = 0; i < n; i++) {
        Point2 v2 = p[i];
        bool in2 = v2.y <= yBottom;
        if (in1 && in2) out.push_back(v2);
        else if (in1 && !in2) out.push_back(HIntersect(v1, v2, yBottom));
        else if (!in1 && in2) { out.push_back(HIntersect(v1, v2, yBottom)); out.push_back(v2); }
        v1 = v2; in1 = in2;
    }
    return out;
}
static std::vector<Point2> clipTop(const std::vector<Point2>& p, double yTop) {
    int n = p.size();
    Point2 v1 = p[n-1];
    bool in1 = v1.y >= yTop;
    std::vector<Point2> out;
    for (int i = 0; i < n; i++) {
        Point2 v2 = p[i];
        bool in2 = v2.y >= yTop;
        if (in1 && in2) out.push_back(v2);
        else if (in1 && !in2) out.push_back(HIntersect(v1, v2, yTop));
        else if (!in1 && in2) { out.push_back(HIntersect(v1, v2, yTop)); out.push_back(v2); }
        v1 = v2; in1 = in2;
    }
    return out;
}
std::vector<Point2> SutherlandHodgmanPolygonClip(const std::vector<Point2>& polygon, int xLeft, int xRight, int yTop, int yBottom) {
    std::vector<Point2> p1 = clipLeft(polygon, xLeft);
    std::vector<Point2> p2 = clipRight(p1, xRight);
    std::vector<Point2> p3 = clipBottom(p2, yBottom);
    return clipTop(p3, yTop);
}

// Square wrappers
bool ClipPointSquare(int x, int y, int xLeft, int size) {
    return ClipPointRectangle(x, y, xLeft, xLeft + size, xLeft, xLeft + size);
}
bool SquareLineClip(int& x1, int& y1, int& x2, int& y2, int xLeft, int yTop, int size) {
    return CohenSutherlandLineClip(x1, y1, x2, y2, xLeft, xLeft + size, yTop, yTop + size);
}

// Circle stubs
bool ClipPointCircle(int x, int y, int xc, int yc, int r) {
    // To be implemented
    double dx = x - xc, dy = y - yc;
    return (dx * dx + dy * dy) <= r * r;
}
bool CircleLineClip(int& x1, int& y1, int& x2, int& y2, int xc, int yc, int r) {
    // Translate coordinates so circle center is at (0,0)
    double dx1 = x1 - xc, dy1 = y1 - yc;
    double dx2 = x2 - xc, dy2 = y2 - yc;
    double dx = dx2 - dx1, dy = dy2 - dy1;
    double a = dx * dx + dy * dy;
    double b = 2 * (dx1 * dx + dy1 * dy);
    double c = dx1 * dx1 + dy1 * dy1 - r * r;
    double disc = b * b - 4 * a * c;
    if (c <= 0 && ((dx2 * dx2 + dy2 * dy2) <= r * r)) {
        // Both endpoints inside
        return true;
    }
    if (disc < 0) {
        // No intersection
        return false;
    }
    // Find intersection t values
    double sqrt_disc = sqrt(disc);
    double t1 = (-b - sqrt_disc) / (2 * a);
    double t2 = (-b + sqrt_disc) / (2 * a);
    // Clamp t values to [0,1]
    double tmin = std::max(0.0, std::min(t1, t2));
    double tmax = std::min(1.0, std::max(t1, t2));
    if (tmax < 0 || tmin > 1) {
        // Intersections are outside segment
        return false;
    }
    // Compute clipped endpoints
    double nx1 = dx1 + tmin * dx;
    double ny1 = dy1 + tmin * dy;
    double nx2 = dx1 + tmax * dx;
    double ny2 = dy1 + tmax * dy;
    x1 = static_cast<int>(std::round(nx1 + xc));
    y1 = static_cast<int>(std::round(ny1 + yc));
    x2 = static_cast<int>(std::round(nx2 + xc));
    y2 = static_cast<int>(std::round(ny2 + yc));
    return true;
} 