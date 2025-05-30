#ifndef POLYGON_FILL_ALGORITHMS_H
#define POLYGON_FILL_ALGORITHMS_H

#include <windows.h>
#include <vector>
#include <algorithm>
#include <list>
#include <stack>
#include <cmath>

struct PolygonPoint {
    double x, y;
    PolygonPoint(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Edge {
    int xleft, xright;
};

struct Node {
    double x, minv;
    int ymax;
    Node(double x = 0, double minv = 0, int ymax = 0) : x(x), minv(minv), ymax(ymax) {}
};

typedef Edge EdgeTable[800];
typedef std::list<Node> LList;
typedef LList NonConvexEdgeTable[800];

void initEdgeTable(EdgeTable tbl) {
    for (int i = 0; i < 800; i++) {
        tbl[i].xleft = 10000;
        tbl[i].xright = -10000;
    }
}

void initNonConvexEdgeTable(NonConvexEdgeTable& tbl) {
    for (int i = 0; i < 800; i++) {
        tbl[i].clear();
    }
}

void Edge2Table(PolygonPoint* v1, PolygonPoint* v2, EdgeTable tbl) {
    if(v1->y == v2->y) return;
    if(v1->y > v2->y) std::swap(v1, v2);

    int y = v1->y;
    double x = v1->x;
    double minv = (v2->x - v1->x) / (v2->y - v1->y);

    while(y < v2->y) {
        if(x < tbl[y].xleft) tbl[y].xleft = (int)ceil(x);
        if(x > tbl[y].xright) tbl[y].xright = (int)floor(x);
        y++;
        x += minv;
    }
}

void Polygon2Table(PolygonPoint p[], int n, EdgeTable tbl) {
    PolygonPoint v1 = p[n-1];
    for(int i = 0; i < n; i++) {
        PolygonPoint v2 = p[i];
        Edge2Table(&v1, &v2, tbl);
        v1 = p[i];
    }
}

void Edge2NonConvexTable(PolygonPoint* v1, PolygonPoint* v2, NonConvexEdgeTable& t) {
    if (v1->y == v2->y) return;
    if (v1->y > v2->y) std::swap(v1, v2);

    double minv = (double)(v2->x - v1->x) / (v2->y - v1->y);
    int y = (int)ceil(v1->y);
    double x = v1->x + (y - v1->y) * minv;

    t[y].push_back(Node(x, minv, (int)v2->y));
}

void Polygon2NonConvexTable(PolygonPoint p[], int n, NonConvexEdgeTable& t) {
    PolygonPoint* v1 = &p[n-1];
    for (int i = 0; i < n; i++) {
        PolygonPoint* v2 = &p[i];
        Edge2NonConvexTable(v1, v2, t);
        v1 = &p[i];
    }
}

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

void Table2Screen(HDC hdc, EdgeTable tbl, COLORREF c) {
    for(int i = 0; i < 800; i++) {
        if(tbl[i].xleft < tbl[i].xright) {
            drawLineBresenhamPolygon(hdc, tbl[i].xleft, i, tbl[i].xright, i, c);
        }
    }
}

void ConvexFill(HDC hdc, PolygonPoint p[], int n, COLORREF c) {
    EdgeTable tbl;
    initEdgeTable(tbl);
    Polygon2Table(p, n, tbl);
    Table2Screen(hdc, tbl, c);
}

void NonConvexFill(HDC hdc, PolygonPoint p[], int n, COLORREF c) {
    if (n < 3) return;

    NonConvexEdgeTable t;
    initNonConvexEdgeTable(t);
    Polygon2NonConvexTable(p, n, t);

    int y = 0;
    while (y < 800) {
        if (t[y].empty()) {
            y++;
            continue;
        }

        LList active = t[y];

        while (!active.empty()) {
            active.sort([](const Node& n1, const Node& n2) {
                return n1.x < n2.x;
            });

            auto it = active.begin();
            while (it != active.end()) {
                int x1 = (int)ceil(it->x);
                it++;
                if (it == active.end()) break;
                int x2 = (int)floor(it->x);
                it++;

                if (x1 <= x2) {
                    drawLineBresenhamPolygon(hdc, x1, y, x2, y, c);
                }
            }

            y++;

            active.remove_if([y](const Node& node) {
                return node.ymax <= y;
            });

            for (auto& node : active) {
                node.x += node.minv;
            }

            if (!t[y].empty()) {
                active.insert(active.end(), t[y].begin(), t[y].end());
            }
        }
    }
}

void FloodFillRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF originalColor) {
    if (GetPixel(hdc, x, y) != originalColor || GetPixel(hdc, x, y) == fillColor) {
        return;
    }
    
    SetPixel(hdc, x, y, fillColor);
    
    FloodFillRecursive(hdc, x + 1, y, fillColor, originalColor);
    FloodFillRecursive(hdc, x - 1, y, fillColor, originalColor);
    FloodFillRecursive(hdc, x, y + 1, fillColor, originalColor);
    FloodFillRecursive(hdc, x, y - 1, fillColor, originalColor);
}

struct FloodPoint {
    int x, y;
    FloodPoint(int x = 0, int y = 0) : x(x), y(y) {}
};

void FloodFillNonRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF originalColor) {
    std::stack<FloodPoint> stack;
    stack.push(FloodPoint(x, y));

    while (!stack.empty()) {
        FloodPoint current = stack.top();
        stack.pop();

        int cx = current.x;
        int cy = current.y;

        if (GetPixel(hdc, cx, cy) == originalColor && GetPixel(hdc, cx, cy) != fillColor) {
            SetPixel(hdc, cx, cy, fillColor);
            
            stack.push(FloodPoint(cx + 1, cy));
            stack.push(FloodPoint(cx - 1, cy));
            stack.push(FloodPoint(cx, cy + 1));
            stack.push(FloodPoint(cx, cy - 1));
        }
    }
}

#endif 