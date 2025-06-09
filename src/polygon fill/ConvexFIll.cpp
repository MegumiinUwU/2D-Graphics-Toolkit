#include "../../include/PolygonFillAlgorithms.h"


void initEdgeTable(EdgeTable tbl) {
    for (int i = 0; i < 800; i++) {
        tbl[i].xleft = 10000;
        tbl[i].xright = -10000;
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
