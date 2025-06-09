#include "../../include/PolygonFillAlgorithms.h"

void initNonConvexEdgeTable(NonConvexEdgeTable& tbl) {
    for (int i = 0; i < 800; i++) {
        tbl[i].clear();
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