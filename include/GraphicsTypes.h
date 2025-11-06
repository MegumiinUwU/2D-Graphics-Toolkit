#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include <vector>
#include <windows.h>
#include "Point.h"

// ========================================
// CONSTANTS AND DEFINITIONS
// ========================================

// Window dimensions
#define DEFAULT_WINDOW_WIDTH  1024
#define DEFAULT_WINDOW_HEIGHT 768

// Menu IDs
enum MenuID {
    // File operations
    MENU_FILE_NEW = 1001,
    MENU_FILE_SAVE,
    MENU_FILE_LOAD,
    MENU_FILE_EXIT,
    
    // Line algorithms
    MENU_LINE_DDA = 2001,
    MENU_LINE_BRESENHAM,
    MENU_LINE_PARAMETRIC,
    
    // Circle algorithms
    MENU_CIRCLE_DIRECT = 2010,
    MENU_CIRCLE_POLAR,
    MENU_CIRCLE_ITERATIVE,
    MENU_CIRCLE_MIDPOINT,
    MENU_CIRCLE_MODIFIED,
    
    // Ellipse algorithms
    MENU_ELLIPSE_DIRECT = 2020,
    MENU_ELLIPSE_POLAR,
    MENU_ELLIPSE_MIDPOINT,
    
    // Polygon shapes
    MENU_POLYGON = 2030,
    MENU_SQUARE,
    MENU_RECTANGLE,
    
    // Curve types
    MENU_CURVE_CARDINAL = 2040,
    MENU_CURVE_BEZIER,
    MENU_CURVE_HERMITE,
    
    // Colors
    MENU_COLOR_BLACK = 3001,
    MENU_COLOR_RED,
    MENU_COLOR_GREEN,
    MENU_COLOR_BLUE,
    MENU_COLOR_WHITE,
    
    // Fill modes
    MENU_FILL_NONE = 4001,
    MENU_FILL_CIRCLE_LINES,
    MENU_FILL_CIRCLE_QUARTER,
    MENU_FILL_CIRCLE_CIRCLES,
    MENU_FILL_POLYGON_CONVEX,
    MENU_FILL_POLYGON_NONCONVEX,
    MENU_FILL_FLOOD_RECURSIVE,
    MENU_FILL_FLOOD_NONRECURSIVE,
    MENU_FILL_SQUARE_HERMITE,
    MENU_FILL_RECTANGLE_BEZIER,
    
    // Tools
    MENU_TOOLS_CLEAR = 5001,
    
    // Cursors
    MENU_CURSOR_ARROW = 6001,
    MENU_CURSOR_HAND,
    MENU_CURSOR_CROSSHAIR
};

// Drawing modes
enum class DrawingMode {
    LINE_DDA,
    LINE_BRESENHAM,
    LINE_PARAMETRIC,
    CIRCLE_DIRECT,
    CIRCLE_POLAR,
    CIRCLE_ITERATIVE_POLAR,
    CIRCLE_MIDPOINT,
    CIRCLE_MODIFIED_MIDPOINT,
    ELLIPSE_DIRECT,
    ELLIPSE_POLAR,
    ELLIPSE_MIDPOINT,
    POLYGON,
    SQUARE,
    RECTANGLE,
    CURVE_CARDINAL,
    CURVE_BEZIER,
    CURVE_HERMITE,
    NONE
};

// Fill modes
enum class FillMode {
    NONE,
    SOLID,
    FLOOD_FILL_RECURSIVE,
    FLOOD_FILL_NON_RECURSIVE,
    SCANLINE_CONVEX,
    SCANLINE_NON_CONVEX,
    CIRCLE_FILL_LINES,
    CIRCLE_FILL_QUARTER,
    CIRCLE_FILL_CIRCLES,
    POLYGON_CONVEX_FILL,
    POLYGON_NONCONVEX_FILL,
    FLOOD_FILL_RECURSIVE_POLYGON,
    FLOOD_FILL_NONRECURSIVE_POLYGON,
    SQUARE_FILL_HERMITE_VERTICAL,
    RECTANGLE_FILL_BEZIER_HORIZONTAL
};

// Shape data structure for saving/loading
struct Shape {
    DrawingMode mode;
    COLORREF color;
    FillMode fillMode;
    std::vector<Point> points;
    int thickness;
};

#endif // GRAPHICS_TYPES_H
