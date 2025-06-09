#ifndef UTILS_H
#define UTILS_H

// Utility function for rounding
inline int Round(double x) {
    return (int)(x + 0.5);
}


// Helper function to check if a point is inside a circle
inline bool IsPointInCircle(int px, int py, int cx, int cy, int radius) {
    int dx = px - cx;
    int dy = py - cy;
    return (dx * dx + dy * dy) <= (radius * radius);
}

#endif // UTILS_H 