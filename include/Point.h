#ifndef POINT_H
#define POINT_H

// Point structure for coordinates
struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

#endif //POINT_H
