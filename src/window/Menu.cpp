#include "../../include/Window.h"

void GraphicsWindow::InitializeMenus() {
    m_hMenuBar = CreateMenu();

    // File menu
    HMENU hFile = CreatePopupMenu();
    AppendMenu(hFile, MF_STRING, MENU_FILE_NEW, "New\tCtrl+N");
    AppendMenu(hFile, MF_STRING, MENU_FILE_SAVE, "Save\tCtrl+S");
    AppendMenu(hFile, MF_STRING, MENU_FILE_LOAD, "Open\tCtrl+O");
    AppendMenu(hFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFile, MF_STRING, MENU_FILE_EXIT, "Exit\tAlt+F4");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hFile, "File");

    // Shapes menu
    HMENU hShapes = CreatePopupMenu();
    
    HMENU hLine = CreatePopupMenu();
    AppendMenu(hLine, MF_STRING, MENU_LINE_DDA, "DDA");
    AppendMenu(hLine, MF_STRING, MENU_LINE_BRESENHAM, "Bresenham");
    AppendMenu(hLine, MF_STRING, MENU_LINE_PARAMETRIC, "Parametric");
    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hLine, "Line");
    
    HMENU hCircle = CreatePopupMenu();
    AppendMenu(hCircle, MF_STRING, MENU_CIRCLE_DIRECT, "Direct");
    AppendMenu(hCircle, MF_STRING, MENU_CIRCLE_POLAR, "Polar");
    AppendMenu(hCircle, MF_STRING, MENU_CIRCLE_ITERATIVE, "Iterative Polar");
    AppendMenu(hCircle, MF_STRING, MENU_CIRCLE_MIDPOINT, "Midpoint");
    AppendMenu(hCircle, MF_STRING, MENU_CIRCLE_MODIFIED, "Modified Midpoint");
    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hCircle, "Circle");
    
    HMENU hEllipse = CreatePopupMenu();
    AppendMenu(hEllipse, MF_STRING, MENU_ELLIPSE_DIRECT, "Direct");
    AppendMenu(hEllipse, MF_STRING, MENU_ELLIPSE_POLAR, "Polar");
    AppendMenu(hEllipse, MF_STRING, MENU_ELLIPSE_MIDPOINT, "Midpoint");
    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hEllipse, "Ellipse");
    
    HMENU hPolygon = CreatePopupMenu();
    AppendMenu(hPolygon, MF_STRING, MENU_POLYGON, "Polygon");
    AppendMenu(hPolygon, MF_STRING, MENU_SQUARE, "Square");
    AppendMenu(hPolygon, MF_STRING, MENU_RECTANGLE, "Rectangle");
    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hPolygon, "Polygon");
    
    HMENU hCurve = CreatePopupMenu();
    AppendMenu(hCurve, MF_STRING, MENU_CURVE_CARDINAL, "Cardinal Spline");
    AppendMenu(hCurve, MF_STRING, MENU_CURVE_BEZIER, "Bezier");
    AppendMenu(hCurve, MF_STRING, MENU_CURVE_HERMITE, "Hermite");
    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hCurve, "Curve");
    
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hShapes, "Shapes");

    // Colors menu
    HMENU hColors = CreatePopupMenu();
    AppendMenu(hColors, MF_STRING, MENU_COLOR_BLACK, "Black");
    AppendMenu(hColors, MF_STRING, MENU_COLOR_RED, "Red");
    AppendMenu(hColors, MF_STRING, MENU_COLOR_GREEN, "Green");
    AppendMenu(hColors, MF_STRING, MENU_COLOR_BLUE, "Blue");
    AppendMenu(hColors, MF_STRING, MENU_COLOR_WHITE, "White");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hColors, "Colors");

    // Fill menu
    HMENU hFill = CreatePopupMenu();
    AppendMenu(hFill, MF_STRING, MENU_FILL_NONE, "None");
    AppendMenu(hFill, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFill, MF_STRING, MENU_FILL_CIRCLE_LINES, "Circle - Lines");
    AppendMenu(hFill, MF_STRING, MENU_FILL_CIRCLE_QUARTER, "Circle - Quarter");
    AppendMenu(hFill, MF_STRING, MENU_FILL_CIRCLE_CIRCLES, "Circle - Solid");
    AppendMenu(hFill, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFill, MF_STRING, MENU_FILL_SQUARE_HERMITE, "Square - Hermite");
    AppendMenu(hFill, MF_STRING, MENU_FILL_RECTANGLE_BEZIER, "Rectangle - Bezier");
    AppendMenu(hFill, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFill, MF_STRING, MENU_FILL_POLYGON_CONVEX, "Polygon - Convex");
    AppendMenu(hFill, MF_STRING, MENU_FILL_POLYGON_NONCONVEX, "Polygon - Non-Convex");
    AppendMenu(hFill, MF_STRING, MENU_FILL_FLOOD_RECURSIVE, "Flood Fill - Recursive");
    AppendMenu(hFill, MF_STRING, MENU_FILL_FLOOD_NONRECURSIVE, "Flood Fill - Non-Recursive");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hFill, "Fill");

    // Tools menu
    HMENU hTools = CreatePopupMenu();
    AppendMenu(hTools, MF_STRING, MENU_TOOLS_CLEAR, "Clear Canvas\tCtrl+L");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hTools, "Tools");

    // Cursor menu
    HMENU hCursor = CreatePopupMenu();
    AppendMenu(hCursor, MF_STRING, MENU_CURSOR_ARROW, "Arrow");
    AppendMenu(hCursor, MF_STRING, MENU_CURSOR_HAND, "Hand");
    AppendMenu(hCursor, MF_STRING, MENU_CURSOR_CROSSHAIR, "Crosshair");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hCursor, "Cursor");

    SetMenu(m_hwnd, m_hMenuBar);
}

void GraphicsWindow::HandleMenuCommand(WPARAM wParam) {
    switch (LOWORD(wParam)) {
        // File operations
        case MENU_FILE_NEW:     ClearCanvas(); break;
        case MENU_FILE_SAVE:    SaveToFile(); break;
        case MENU_FILE_LOAD:    LoadFromFile(); break;
        case MENU_FILE_EXIT:    PostMessage(m_hwnd, WM_CLOSE, 0, 0); break;

        // Line modes
        case MENU_LINE_DDA:        SetDrawingMode(DrawingMode::LINE_DDA); break;
        case MENU_LINE_BRESENHAM:  SetDrawingMode(DrawingMode::LINE_BRESENHAM); break;
        case MENU_LINE_PARAMETRIC: SetDrawingMode(DrawingMode::LINE_PARAMETRIC); break;

        // Circle modes
        case MENU_CIRCLE_DIRECT:    SetDrawingMode(DrawingMode::CIRCLE_DIRECT); break;
        case MENU_CIRCLE_POLAR:     SetDrawingMode(DrawingMode::CIRCLE_POLAR); break;
        case MENU_CIRCLE_ITERATIVE: SetDrawingMode(DrawingMode::CIRCLE_ITERATIVE_POLAR); break;
        case MENU_CIRCLE_MIDPOINT:  SetDrawingMode(DrawingMode::CIRCLE_MIDPOINT); break;
        case MENU_CIRCLE_MODIFIED:  SetDrawingMode(DrawingMode::CIRCLE_MODIFIED_MIDPOINT); break;

        // Ellipse modes
        case MENU_ELLIPSE_DIRECT:   SetDrawingMode(DrawingMode::ELLIPSE_DIRECT); break;
        case MENU_ELLIPSE_POLAR:    SetDrawingMode(DrawingMode::ELLIPSE_POLAR); break;
        case MENU_ELLIPSE_MIDPOINT: SetDrawingMode(DrawingMode::ELLIPSE_MIDPOINT); break;

        // Polygon modes
        case MENU_POLYGON:   SetDrawingMode(DrawingMode::POLYGON); break;
        case MENU_SQUARE:    SetDrawingMode(DrawingMode::SQUARE); break;
        case MENU_RECTANGLE: SetDrawingMode(DrawingMode::RECTANGLE); break;

        // Curve modes
        case MENU_CURVE_CARDINAL: SetDrawingMode(DrawingMode::CURVE_CARDINAL); break;
        case MENU_CURVE_BEZIER:   SetDrawingMode(DrawingMode::CURVE_BEZIER); break;
        case MENU_CURVE_HERMITE:  SetDrawingMode(DrawingMode::CURVE_HERMITE); break;

        // Colors
        case MENU_COLOR_BLACK: SetDrawingColor(RGB(0, 0, 0)); break;
        case MENU_COLOR_RED:   SetDrawingColor(RGB(255, 0, 0)); break;
        case MENU_COLOR_GREEN: SetDrawingColor(RGB(0, 255, 0)); break;
        case MENU_COLOR_BLUE:  SetDrawingColor(RGB(0, 0, 255)); break;
        case MENU_COLOR_WHITE: SetDrawingColor(RGB(255, 255, 255)); break;

        // Fill modes
        case MENU_FILL_NONE:                SetFillMode(FillMode::NONE); break;
        case MENU_FILL_CIRCLE_LINES:        SetFillMode(FillMode::CIRCLE_FILL_LINES); break;
        case MENU_FILL_CIRCLE_QUARTER:      SetFillMode(FillMode::CIRCLE_FILL_QUARTER); break;
        case MENU_FILL_CIRCLE_CIRCLES:      SetFillMode(FillMode::CIRCLE_FILL_CIRCLES); break;
        case MENU_FILL_POLYGON_CONVEX:      SetFillMode(FillMode::POLYGON_CONVEX_FILL); break;
        case MENU_FILL_POLYGON_NONCONVEX:   SetFillMode(FillMode::POLYGON_NONCONVEX_FILL); break;
        case MENU_FILL_FLOOD_RECURSIVE:     SetFillMode(FillMode::FLOOD_FILL_RECURSIVE_POLYGON); break;
        case MENU_FILL_FLOOD_NONRECURSIVE:  SetFillMode(FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON); break;
        case MENU_FILL_SQUARE_HERMITE:      SetFillMode(FillMode::SQUARE_FILL_HERMITE_VERTICAL); break;
        case MENU_FILL_RECTANGLE_BEZIER:    SetFillMode(FillMode::RECTANGLE_FILL_BEZIER_HORIZONTAL); break;

        // Tools
        case MENU_TOOLS_CLEAR: ClearCanvas(); break;

        // Cursors
        case MENU_CURSOR_ARROW:     SetMouseCursor(LoadCursor(NULL, IDC_ARROW)); break;
        case MENU_CURSOR_HAND:      SetMouseCursor(LoadCursor(NULL, IDC_HAND)); break;
        case MENU_CURSOR_CROSSHAIR: SetMouseCursor(LoadCursor(NULL, IDC_CROSS)); break;
    }
}
