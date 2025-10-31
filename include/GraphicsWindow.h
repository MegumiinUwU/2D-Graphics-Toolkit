#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <fstream>
#include "Point.h"
#include "LineAlgorithms.h"
#include "CircleAlgorithms.h"
#include "EllipseAlgorithms.h"
#include "CircleFillAlgorithms.h"
#include "PolygonFillAlgorithms.h"
#include "PolygonAlgorithms.h"
#include "Hermite.h"
#include "Bezier.h"
#include "CardinalSpline.h"
#include "Utils.h"
#include "FloodFill.h"


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


using namespace std;

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
    ELLIPSE_DIRECT,    ELLIPSE_POLAR,    ELLIPSE_MIDPOINT,
    POLYGON,    SQUARE,
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
    CIRCLE_FILL_CIRCLES,    POLYGON_CONVEX_FILL,
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

// ========================================
// MAIN GRAPHICS WINDOW CLASS
// ========================================

class GraphicsWindow {
private:
    // Window handles and identifiers
    HWND m_hwnd;
    HINSTANCE m_hInstance;
    HDC m_hdc;

    // Offscreen drawing buffer for performance
    HDC m_offscreenDC;
    HBITMAP m_offscreenBitmap;
    HBITMAP m_oldBitmap;
    int m_canvasWidth;
    int m_canvasHeight;

    // Drawing state
    DrawingMode m_currentDrawingMode;
    FillMode m_currentFillMode;
    COLORREF m_currentColor;
    COLORREF m_backgroundColor;
    int m_lineThickness;
    bool m_fillMode; // New flag to indicate we're in fill mode

    // Mouse interaction state
    bool m_isDrawing;
    std::vector<Point> m_currentPoints;
    Point m_lastMousePos;
    
    // Rectangle dragging state
    bool m_isDraggingRectangle;
    
    // Polygon drawing state
    std::vector<PolygonPoint> m_polygonPoints;
    bool m_isDrawingPolygon;

    // Shape storage
    std::vector<Shape> m_shapes;

    // Pens and brushes
    HPEN m_currentPen;
    HBRUSH m_currentBrush;
    HBRUSH m_backgroundBrush;    // Menu handle
    HMENU m_hMenuBar;

    // Cursor handle
    HCURSOR m_currentCursor;

    // Window class name
    static const char* s_className;

    // Static window procedure
    static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Instance window procedure
    LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Helper methods
    void InitializeMenus();
    void InitializeDrawingTools();
    void CleanupDrawingTools();
    void CreateOffscreenBuffer(int width, int height);
    void CleanupOffscreenBuffer();
    void ClearOffscreenBuffer();
    void DrawShapeToBuffer(const Shape& shape);
    void RebuildOffscreenBuffer();
    void UpdateCurrentPen();
    void HandleMouseClick(int x, int y, bool isLeftButton);
    void HandleMouseMove(int x, int y);
    void HandleMenuCommand(WPARAM wParam);
    void RedrawAll();
    void ClearCanvas();
    void SaveToFile();
    void LoadFromFile();

public:
    // Constructor and destructor
    GraphicsWindow();
    ~GraphicsWindow();

    // Window management
    bool Initialize(HINSTANCE hInstance, int nCmdShow);
    void Run();
    void SetTitle(const std::string& title);
    void SetBackgroundColor(COLORREF color);    // Drawing mode setters
    void SetDrawingMode(DrawingMode mode);
    void SetFillMode(FillMode mode);
    void SetDrawingColor(COLORREF color);
    void SetLineThickness(int thickness);
    void SetMouseCursor(HCURSOR cursor);

    // Utility methods
    HWND GetHandle() const { return m_hwnd; }
    DrawingMode GetCurrentDrawingMode() const { return m_currentDrawingMode; }
    COLORREF GetCurrentColor() const { return m_currentColor; }
};

// ========================================
// GRAPHICSWINDOW IMPLEMENTATION
// ========================================

// Static member definition
const char* GraphicsWindow::s_className = "2DGraphicsWindowClass";

// Constructor
GraphicsWindow::GraphicsWindow()
        : m_hwnd(nullptr)
        , m_hInstance(nullptr)
        , m_hdc(nullptr)
        , m_offscreenDC(nullptr)
        , m_offscreenBitmap(nullptr)
        , m_oldBitmap(nullptr)
        , m_canvasWidth(0)
        , m_canvasHeight(0)
        , m_currentDrawingMode(DrawingMode::LINE_DDA)
        , m_currentFillMode(FillMode::NONE)
        , m_currentColor(RGB(0, 0, 0))  // Black
        , m_backgroundColor(RGB(255, 255, 255))  // White
        , m_lineThickness(1)
        , m_isDrawing(false)
        , m_currentPen(nullptr)
        , m_currentBrush(nullptr)        , m_backgroundBrush(nullptr)
        , m_hMenuBar(nullptr)
        , m_currentCursor(LoadCursor(NULL, IDC_CROSS))
        , m_fillMode(false)
        , m_isDrawingPolygon(false)
{
}

// Destructor
GraphicsWindow::~GraphicsWindow() {
    CleanupOffscreenBuffer();
    CleanupDrawingTools();
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
    }
}

// Initialize method
bool GraphicsWindow::Initialize(HINSTANCE hInstance, int nCmdShow) {
    m_hInstance = hInstance;

    // Register window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = StaticWndProc;
    wc.hInstance = hInstance;    wc.hbrBackground = CreateSolidBrush(m_backgroundColor);
    wc.lpszClassName = s_className;
    wc.hCursor = m_currentCursor;  // Use current cursor
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Add CS_OWNDC for better performance

    if (!RegisterClass(&wc)) {
        return false;
    }
    
    // Create window
    m_hwnd = CreateWindow(
            s_className,
            "2D Graphics Drawing Program",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
            NULL, NULL, hInstance, this  // Pass 'this' pointer
    );

    if (!m_hwnd) {
        return false;
    }
    
    // Initialize menus and drawing tools
    InitializeMenus();
    InitializeDrawingTools();

    // Create offscreen buffer for double buffering
    CreateOffscreenBuffer(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

    // Show window with proper visibility and focus
    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);
    
    // Ensure window stays visible and gets focus
    SetWindowPos(m_hwnd, HWND_TOP, 0, 0, 0, 0, 
                SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    SetForegroundWindow(m_hwnd);
    SetActiveWindow(m_hwnd);
    SetFocus(m_hwnd);
    return true;
}

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

// Initialize drawing tools
void GraphicsWindow::InitializeDrawingTools() {
    m_currentPen = CreatePen(PS_SOLID, m_lineThickness, m_currentColor);
    m_currentBrush = CreateSolidBrush(m_currentColor);
    m_backgroundBrush = CreateSolidBrush(m_backgroundColor);
}

// Cleanup drawing tools
void GraphicsWindow::CleanupDrawingTools() {
    if (m_currentPen) DeleteObject(m_currentPen);
    if (m_currentBrush) DeleteObject(m_currentBrush);
    if (m_backgroundBrush) DeleteObject(m_backgroundBrush);
}

// Update current pen
void GraphicsWindow::UpdateCurrentPen() {
    if (m_currentPen) DeleteObject(m_currentPen);
    m_currentPen = CreatePen(PS_SOLID, m_lineThickness, m_currentColor);
}

// Static window procedure
LRESULT CALLBACK GraphicsWindow::StaticWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GraphicsWindow* window = nullptr;

    if (message == WM_CREATE) {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        window = (GraphicsWindow*)cs->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
    } else {
        window = (GraphicsWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (window) {
        return window->WndProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

// Instance window procedure
LRESULT GraphicsWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            HandleMenuCommand(wParam);
            break;

        case WM_LBUTTONDOWN:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            HandleMouseClick(x, y, true);
        }
            break;

        case WM_RBUTTONDOWN:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            HandleMouseClick(x, y, false);
        }
            break;        case WM_MOUSEMOVE:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            HandleMouseMove(x, y);
        }
            break;

        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT) {
                ::SetCursor(m_currentCursor);
                return TRUE;
            }
            return DefWindowProc(hwnd, message, wParam, lParam);

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Copy from offscreen buffer for much better performance
            if (m_offscreenDC) {
                BitBlt(hdc, 0, 0, m_canvasWidth, m_canvasHeight, m_offscreenDC, 0, 0, SRCCOPY);
            }

            // Draw instructions on top
            SetTextColor(hdc, RGB(100, 100, 100));
            SetBkMode(hdc, TRANSPARENT);
            
            if (m_fillMode) {
                if (m_currentFillMode == FillMode::POLYGON_CONVEX_FILL || 
                    m_currentFillMode == FillMode::POLYGON_NONCONVEX_FILL) {
                    TextOut(hdc, 10, 10, "POLYGON FILL: Click near existing polygon to fill it", 53);
                } else if (m_currentFillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON || 
                           m_currentFillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                    TextOut(hdc, 10, 10, "FLOOD FILL MODE: Click inside area to fill", 43);
                } else if (m_currentFillMode == FillMode::SQUARE_FILL_HERMITE_VERTICAL) {
                    TextOut(hdc, 10, 10, "SQUARE HERMITE FILL: Click inside a square to fill it | Right click to cancel", 78);
                } else if (m_currentFillMode == FillMode::RECTANGLE_FILL_BEZIER_HORIZONTAL) {
                    TextOut(hdc, 10, 10, "RECTANGLE BEZIER FILL: Click inside a rectangle to fill it | Right click to cancel", 84);
                } else {
                    TextOut(hdc, 10, 10, "FILL MODE: Click inside a circle to fill it | Right click to cancel", 68);
                }
            } else {
                if (m_currentDrawingMode == DrawingMode::POLYGON) {
                    TextOut(hdc, 10, 10, "POLYGON MODE: Left click to add points | Right click to finish", 63);
                } else {
                    TextOut(hdc, 10, 10, "Left click to draw shapes | Right click to finish/cancel", 57);
                }
            }

            std::string modeText = "Current mode: ";
            switch (m_currentDrawingMode) {
                case DrawingMode::LINE_DDA: modeText += "Line (DDA)"; break;
                case DrawingMode::LINE_BRESENHAM: modeText += "Line (Bresenham)"; break;
                case DrawingMode::LINE_PARAMETRIC: modeText += "Line (Parametric)"; break;
                case DrawingMode::CIRCLE_DIRECT: modeText += "Circle (Direct)"; break;
                case DrawingMode::CIRCLE_POLAR: modeText += "Circle (Polar)"; break;
                case DrawingMode::CIRCLE_ITERATIVE_POLAR: modeText += "Circle (Iterative Polar)"; break;
                case DrawingMode::CIRCLE_MIDPOINT: modeText += "Circle (Midpoint)"; break;
                case DrawingMode::CIRCLE_MODIFIED_MIDPOINT: modeText += "Circle (Modified Midpoint)"; break;
                case DrawingMode::ELLIPSE_DIRECT: modeText += "Ellipse (Direct)"; break;
                case DrawingMode::ELLIPSE_POLAR: modeText += "Ellipse (Polar)"; break;                case DrawingMode::ELLIPSE_MIDPOINT: modeText += "Ellipse (Midpoint)"; break;                case DrawingMode::POLYGON: modeText += "Polygon"; break;
                case DrawingMode::SQUARE: modeText += "Square"; break;
                case DrawingMode::RECTANGLE: modeText += "Rectangle"; break;
                case DrawingMode::CURVE_CARDINAL: modeText += "Cardinal Spline"; break;
                case DrawingMode::CURVE_BEZIER: modeText += "Bezier Curve"; break;
                case DrawingMode::CURVE_HERMITE: modeText += "Hermite Curve"; break;
                default: modeText += "None"; break;
            }
            TextOut(hdc, 10, 30, modeText.c_str(), modeText.length());

            // Display current fill mode
            std::string fillText = "Current fill: ";
            switch (m_currentFillMode) {
                case FillMode::NONE: fillText += "None"; break;
                case FillMode::SOLID: fillText += "Solid"; break;
                case FillMode::CIRCLE_FILL_LINES: fillText += "Circle Lines"; break;
                case FillMode::CIRCLE_FILL_QUARTER: fillText += "Circle Quarter"; break;
                case FillMode::CIRCLE_FILL_CIRCLES: fillText += "Circle Solid"; break;
                case FillMode::POLYGON_CONVEX_FILL: fillText += "Convex Polygon"; break;                case FillMode::POLYGON_NONCONVEX_FILL: fillText += "Non-Convex Polygon"; break;
                case FillMode::FLOOD_FILL_RECURSIVE_POLYGON: fillText += "Flood Fill Recursive"; break;
                case FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON: fillText += "Flood Fill Non-Recursive"; break;                case FillMode::SQUARE_FILL_HERMITE_VERTICAL: fillText += "Square Hermite Curves"; break;
                case FillMode::RECTANGLE_FILL_BEZIER_HORIZONTAL: fillText += "Rectangle Bezier Curves"; break;
                default: fillText += "None"; break;
            }
            TextOut(hdc, 10, 50, fillText.c_str(), fillText.length());

            EndPaint(hwnd, &ps);
        }
            break;

        case WM_SIZE:
        {
            // Handle window resize - recreate offscreen buffer
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            int newWidth = clientRect.right - clientRect.left;
            int newHeight = clientRect.bottom - clientRect.top;
            
            if (newWidth > 0 && newHeight > 0) {
                CreateOffscreenBuffer(newWidth, newHeight);
                RebuildOffscreenBuffer();
            }
            
            InvalidateRect(hwnd, NULL, TRUE);
        }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// Handle mouse click
void GraphicsWindow::HandleMouseClick(int x, int y, bool isLeftButton) {
    if (!isLeftButton) {
        // Right click - finish current drawing or cancel
        if (m_isDrawing && m_currentDrawingMode == DrawingMode::POLYGON && m_currentPoints.size() >= 3) {
            // Finish polygon
            Shape shape;
            shape.mode = m_currentDrawingMode;
            shape.color = m_currentColor;
            shape.fillMode = FillMode::NONE;  // Always create polygons empty
            shape.points = m_currentPoints;
            shape.thickness = m_lineThickness;
            m_shapes.push_back(shape);

            // Draw directly to offscreen buffer for performance
            DrawShapeToBuffer(shape);
        }        else if (m_isDrawing && m_currentDrawingMode == DrawingMode::CURVE_CARDINAL && m_currentPoints.size() >= 2) {
            // Finish Cardinal Spline
            Shape shape;
            shape.mode = m_currentDrawingMode;
            shape.color = m_currentColor;
            shape.fillMode = FillMode::NONE;  // Always create shapes empty
            shape.points = m_currentPoints;
            shape.thickness = m_lineThickness;
            m_shapes.push_back(shape);

            // Draw directly to offscreen buffer for performance
            DrawShapeToBuffer(shape);
        }
        else if (m_isDrawing && m_currentDrawingMode == DrawingMode::CURVE_BEZIER && m_currentPoints.size() >= 2) {
            // Finish Bezier Curve
            Shape shape;
            shape.mode = m_currentDrawingMode;
            shape.color = m_currentColor;
            shape.fillMode = FillMode::NONE;  // Always create shapes empty
            shape.points = m_currentPoints;
            shape.thickness = m_lineThickness;
            m_shapes.push_back(shape);

            // Draw directly to offscreen buffer for performance
            DrawShapeToBuffer(shape);
        }
        else if (m_isDrawing && m_currentDrawingMode == DrawingMode::CURVE_HERMITE && m_currentPoints.size() >= 4) {
            // Finish Hermite Curve (needs at least 4 points: 2 control points + 2 tangent points)
            Shape shape;
            shape.mode = m_currentDrawingMode;
            shape.color = m_currentColor;
            shape.fillMode = FillMode::NONE;  // Always create shapes empty
            shape.points = m_currentPoints;
            shape.thickness = m_lineThickness;
            m_shapes.push_back(shape);

            // Draw directly to offscreen buffer for performance
            DrawShapeToBuffer(shape);
        }

        // Reset drawing state
        m_isDrawing = false;
        m_currentPoints.clear();
        InvalidateRect(m_hwnd, NULL, TRUE);
        return;
    }

    // Left click - check if we're in fill mode first
    Point newPoint(x, y);
    
    // If we're in fill mode, try to fill an existing circle
    if (m_fillMode) {
        if (m_currentFillMode == FillMode::POLYGON_CONVEX_FILL || 
            m_currentFillMode == FillMode::POLYGON_NONCONVEX_FILL) {
            
            // Fill existing polygons by clicking on them
            for (auto& shape : m_shapes) {
                if (shape.mode == DrawingMode::POLYGON && shape.points.size() >= 3) {
                    // Simple point-in-polygon test - check if click is near any vertex
                    bool inside = false;
                    for (size_t i = 0; i < shape.points.size(); i++) {
                        if (abs(shape.points[i].x - x) <= 50 && abs(shape.points[i].y - y) <= 50) {
                            inside = true;
                            break;
                        }
                    }
                    
                    if (inside) {
                        shape.fillMode = m_currentFillMode;
                        shape.color = m_currentColor;  // Use current color for fill
                        RebuildOffscreenBuffer();
                        InvalidateRect(m_hwnd, NULL, TRUE);
                        return;
                    }
                }
            }
            return;
        }
        
        if (m_currentFillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON || 
            m_currentFillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
            COLORREF originalColor = GetPixel(m_offscreenDC, x, y);
            if (originalColor != m_currentColor) {
                if (m_currentFillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                    FloodFillRecursive(m_offscreenDC, x, y, m_currentColor, originalColor);
                } else {
                    FloodFillNonRecursive(m_offscreenDC, x, y, m_currentColor, originalColor);
                }
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
            return;
        }
          for (auto& shape : m_shapes) {
            // Check if it's a circle shape and if click is inside it
            if ((shape.mode == DrawingMode::CIRCLE_DIRECT ||
                 shape.mode == DrawingMode::CIRCLE_POLAR ||
                 shape.mode == DrawingMode::CIRCLE_ITERATIVE_POLAR ||
                 shape.mode == DrawingMode::CIRCLE_MIDPOINT ||
                 shape.mode == DrawingMode::CIRCLE_MODIFIED_MIDPOINT) &&
                shape.points.size() >= 2) {
                
                // Calculate circle radius
                int radius = (int)sqrt(
                    pow(shape.points[1].x - shape.points[0].x, 2) +
                    pow(shape.points[1].y - shape.points[0].y, 2)
                );
                
                // Check if click point is inside this circle
                if (IsPointInCircle(x, y, shape.points[0].x, shape.points[0].y, radius)) {
                    // Update the shape's fill mode and color
                    shape.fillMode = m_currentFillMode;
                    shape.color = m_currentColor;  // Use current color for fill
                    
                    // Rebuild buffer to ensure proper rendering with fills
                    RebuildOffscreenBuffer();
                    
                    InvalidateRect(m_hwnd, NULL, TRUE);
                    return; // Fill the first circle found and exit
                }
            }
              // Check if it's a square shape and if click is inside it
            if (shape.mode == DrawingMode::SQUARE && 
                shape.points.size() >= 2 &&
                m_currentFillMode == FillMode::SQUARE_FILL_HERMITE_VERTICAL) {
                
                // Calculate square boundaries
                int centerX = shape.points[0].x;
                int centerY = shape.points[0].y;
                int halfSize = (int)sqrt(
                    pow(shape.points[1].x - centerX, 2) +
                    pow(shape.points[1].y - centerY, 2)
                );
                
                // Check if click point is inside this square
                if (x >= centerX - halfSize && x <= centerX + halfSize &&
                    y >= centerY - halfSize && y <= centerY + halfSize) {
                    // Update the shape's fill mode and color
                    shape.fillMode = m_currentFillMode;
                    shape.color = m_currentColor;  // Use current color for fill
                    
                    // Rebuild buffer to ensure proper rendering with fills
                    RebuildOffscreenBuffer();
                    
                    InvalidateRect(m_hwnd, NULL, TRUE);
                    return; // Fill the first square found and exit
                }
            }
              // Check if it's a rectangle shape and if click is inside it
            if (shape.mode == DrawingMode::RECTANGLE && 
                shape.points.size() >= 2 &&
                m_currentFillMode == FillMode::RECTANGLE_FILL_BEZIER_HORIZONTAL) {
                
                // Calculate rectangle boundaries using center/vertex coordinate system
                int centerX = shape.points[0].x;
                int centerY = shape.points[0].y;
                int vertexX = shape.points[1].x;
                int vertexY = shape.points[1].y;
                
                int halfWidth = abs(vertexX - centerX);
                int halfHeight = abs(vertexY - centerY);
                
                int left = centerX - halfWidth;
                int right = centerX + halfWidth;
                int top = centerY - halfHeight;
                int bottom = centerY + halfHeight;
                
                // Check if click point is inside this rectangle
                if (x >= left && x <= right && y >= top && y <= bottom) {
                    // Update the shape's fill mode and color
                    shape.fillMode = m_currentFillMode;
                    shape.color = m_currentColor;  // Use current color for fill
                    
                    // Rebuild buffer to ensure proper rendering with fills
                    RebuildOffscreenBuffer();
                    
                    InvalidateRect(m_hwnd, NULL, TRUE);
                    return; // Fill the first rectangle found and exit
                }
            }
        }
        return; // In fill mode but didn't click inside any shape
    }

    // Normal drawing mode - add point or complete shape
    switch (m_currentDrawingMode) {
        case DrawingMode::LINE_DDA:
        case DrawingMode::LINE_BRESENHAM:
        case DrawingMode::LINE_PARAMETRIC:
        {
            if (!m_isDrawing) {
                // Start line
                m_currentPoints.clear();
                m_currentPoints.push_back(newPoint);
                m_isDrawing = true;
            } else {
                // Finish line
                m_currentPoints.push_back(newPoint);

                Shape shape;
                shape.mode = m_currentDrawingMode;
                shape.color = m_currentColor;
                shape.fillMode = FillMode::NONE;  // Always create shapes empty
                shape.points = m_currentPoints;
                shape.thickness = m_lineThickness;
                m_shapes.push_back(shape);

                // Draw directly to offscreen buffer for performance
                DrawShapeToBuffer(shape);

                m_isDrawing = false;
                m_currentPoints.clear();
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
            break;

        case DrawingMode::CIRCLE_DIRECT:
        case DrawingMode::CIRCLE_POLAR:
        case DrawingMode::CIRCLE_ITERATIVE_POLAR:
        case DrawingMode::CIRCLE_MIDPOINT:
        case DrawingMode::CIRCLE_MODIFIED_MIDPOINT:
        {
            if (!m_isDrawing) {
                // Start circle (center point)
                m_currentPoints.clear();
                m_currentPoints.push_back(newPoint);
                m_isDrawing = true;
            } else {
                // Finish circle (radius point)
                m_currentPoints.push_back(newPoint);

                Shape shape;
                shape.mode = m_currentDrawingMode;
                shape.color = m_currentColor;
                shape.fillMode = FillMode::NONE;  // Always create shapes empty
                shape.points = m_currentPoints;
                shape.thickness = m_lineThickness;
                m_shapes.push_back(shape);

                // Draw directly to offscreen buffer for performance
                DrawShapeToBuffer(shape);

                m_isDrawing = false;
                m_currentPoints.clear();
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
            break;

        case DrawingMode::ELLIPSE_DIRECT:
        case DrawingMode::ELLIPSE_POLAR:
        case DrawingMode::ELLIPSE_MIDPOINT:
        {
            if (!m_isDrawing) {
                // Start ellipse (center point)
                m_currentPoints.clear();
                m_currentPoints.push_back(newPoint);
                m_isDrawing = true;
            } else {
                // Finish ellipse (radius point)
                m_currentPoints.push_back(newPoint);

                Shape shape;
                shape.mode = m_currentDrawingMode;
                shape.color = m_currentColor;
                shape.fillMode = FillMode::NONE;  // Always create shapes empty
                shape.points = m_currentPoints;
                shape.thickness = m_lineThickness;
                m_shapes.push_back(shape);

                // Draw directly to offscreen buffer for performance
                DrawShapeToBuffer(shape);

                m_isDrawing = false;
                m_currentPoints.clear();
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
            break;        case DrawingMode::SQUARE:
        {
            if (!m_isDrawing) {
                // Start square (center point)
                m_currentPoints.clear();
                m_currentPoints.push_back(newPoint);
                m_isDrawing = true;            } else {
                // Finish square (edge point to define half-size)
                m_currentPoints.push_back(newPoint);

                Shape shape;
                shape.mode = m_currentDrawingMode;
                shape.color = m_currentColor;
                shape.fillMode = FillMode::NONE;  // Always create squares empty
                shape.points = m_currentPoints;
                shape.thickness = m_lineThickness;
                m_shapes.push_back(shape);

                // Draw directly to offscreen buffer for performance
                DrawShapeToBuffer(shape);

                m_isDrawing = false;
                m_currentPoints.clear();
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
            break;        case DrawingMode::RECTANGLE:
        {
            if (!m_isDrawing) {
                // Start rectangle (center point)
                m_currentPoints.clear();
                m_currentPoints.push_back(newPoint);
                m_isDrawing = true;
            } else {
                // Finish rectangle (corner point to define dimensions)
                m_currentPoints.push_back(newPoint);

                Shape shape;
                shape.mode = m_currentDrawingMode;
                shape.color = m_currentColor;
                shape.fillMode = FillMode::NONE;  // Always create rectangles empty
                shape.points = m_currentPoints;
                shape.thickness = m_lineThickness;
                m_shapes.push_back(shape);

                // Draw directly to offscreen buffer for performance
                DrawShapeToBuffer(shape);

                m_isDrawing = false;
                m_currentPoints.clear();
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
            break;        case DrawingMode::POLYGON:
        {
            if (!m_isDrawing) {
                m_currentPoints.clear();
                m_isDrawing = true;
            }
            m_currentPoints.push_back(newPoint);
            InvalidateRect(m_hwnd, NULL, TRUE);
        }
            break;        case DrawingMode::CURVE_CARDINAL:
        {
            if (!m_isDrawing) {
                m_currentPoints.clear();
                m_isDrawing = true;
            }
            m_currentPoints.push_back(newPoint);
            InvalidateRect(m_hwnd, NULL, TRUE);
        }
            break;

        case DrawingMode::CURVE_BEZIER:
        {
            if (!m_isDrawing) {
                m_currentPoints.clear();
                m_isDrawing = true;
            }
            m_currentPoints.push_back(newPoint);
            InvalidateRect(m_hwnd, NULL, TRUE);
        }
            break;

        case DrawingMode::CURVE_HERMITE:
        {
            if (!m_isDrawing) {
                m_currentPoints.clear();
                m_isDrawing = true;
            }
            m_currentPoints.push_back(newPoint);
            InvalidateRect(m_hwnd, NULL, TRUE);
        }
            break;
    }
}

// Handle mouse move
void GraphicsWindow::HandleMouseMove(int x, int y) {
    Point newPos(x, y);
    
    // Only update if mouse actually moved (reduce unnecessary redraws)
    if (newPos.x != m_lastMousePos.x || newPos.y != m_lastMousePos.y) {
        m_lastMousePos = newPos;

        // For preview drawing while creating shapes
        if (m_isDrawing) {
            // Only invalidate a small region around the preview line instead of the whole window
            RECT invalidRect;
            if (!m_currentPoints.empty()) {
                                 int minX = std::min(m_currentPoints[0].x, m_lastMousePos.x) - 5;
                int maxX = std::max(m_currentPoints[0].x, m_lastMousePos.x) + 5;
                int minY = std::min(m_currentPoints[0].y, m_lastMousePos.y) - 5;
                int maxY = std::max(m_currentPoints[0].y, m_lastMousePos.y) + 5;
                
                SetRect(&invalidRect, minX, minY, maxX, maxY);
                InvalidateRect(m_hwnd, &invalidRect, TRUE);
            }
        }
    }
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

// Redraw all shapes using implemented algorithms
void GraphicsWindow::RedrawAll() {
    // std::cout << m_shapes.size();
    HDC hdc = GetDC(m_hwnd);

    // Draw all saved shapes using their respective algorithms
    for (const auto& shape : m_shapes) {
        if (shape.points.size() >= 2) {
            switch (shape.mode) {
                case DrawingMode::LINE_DDA:
                    DrawLineDDA(hdc, shape.points[0].x, shape.points[0].y,
                               shape.points[1].x, shape.points[1].y, shape.color);
                    break;
                    
                case DrawingMode::LINE_BRESENHAM:
                    DrawLineBresenham(hdc, shape.points[0].x, shape.points[0].y,
                                     shape.points[1].x, shape.points[1].y, shape.color);
                    break;
                    
                case DrawingMode::LINE_PARAMETRIC:
                    DrawLineParametric(hdc, shape.points[0].x, shape.points[0].y,
                                      shape.points[1].x, shape.points[1].y, shape.color);
                    break;
                    
                case DrawingMode::CIRCLE_DIRECT:
                {
                    int radius = (int)sqrt(
                        pow(shape.points[1].x - shape.points[0].x, 2) +
                        pow(shape.points[1].y - shape.points[0].y, 2)
                    );
                    DrawDirectCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    
                    // Apply fill mode if set
                    if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                        FillCircleWithLines(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                        FillQuarterCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                        FillCircleWithCircles(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    }
                }
                    break;
                    
                case DrawingMode::CIRCLE_POLAR:
                {
                    int radius = (int)sqrt(
                        pow(shape.points[1].x - shape.points[0].x, 2) +
                        pow(shape.points[1].y - shape.points[0].y, 2)
                    );
                    DrawPolarCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    
                    // Apply fill mode if set
                    if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                        FillCircleWithLines(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                        FillQuarterCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                        FillCircleWithCircles(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    }
                }
                    break;
                    
                case DrawingMode::CIRCLE_ITERATIVE_POLAR:
                {
                    int radius = (int)sqrt(
                        pow(shape.points[1].x - shape.points[0].x, 2) +
                        pow(shape.points[1].y - shape.points[0].y, 2)
                    );
                    DrawIterativePolarCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    
                    // Apply fill mode if set
                    if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                        FillCircleWithLines(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                        FillQuarterCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                        FillCircleWithCircles(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    }
                }
                    break;
                    
                case DrawingMode::CIRCLE_MIDPOINT:
                {
                    int radius = (int)sqrt(
                        pow(shape.points[1].x - shape.points[0].x, 2) +
                        pow(shape.points[1].y - shape.points[0].y, 2)
                    );
                    std::cout << radius << '\n';
                    DrawCircleBresenham(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    
                    // Apply fill mode if set
                    if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                        FillCircleWithLines(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                        FillQuarterCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                        FillCircleWithCircles(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    }
                }
                    break;
                    
                case DrawingMode::CIRCLE_MODIFIED_MIDPOINT:
                {
                    int radius = (int)sqrt(
                        pow(shape.points[1].x - shape.points[0].x, 2) +
                        pow(shape.points[1].y - shape.points[0].y, 2)
                    );
                    DrawCircleDDA1(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    
                    // Apply fill mode if set
                    if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                        FillCircleWithLines(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                        FillQuarterCircle(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                        FillCircleWithCircles(hdc, shape.points[0].x, shape.points[0].y, radius, shape.color);
                    }
                }
                    break;
                    
                case DrawingMode::ELLIPSE_DIRECT:
                {
                    int radiusX = abs(shape.points[1].x - shape.points[0].x);
                    int radiusY = abs(shape.points[1].y - shape.points[0].y);
                    DrawDirectEllipse(hdc, shape.points[0].x, shape.points[0].y, radiusX, radiusY, shape.color);
                }
                    break;
                    
                case DrawingMode::ELLIPSE_POLAR:
                {
                    int radiusX = abs(shape.points[1].x - shape.points[0].x);
                    int radiusY = abs(shape.points[1].y - shape.points[0].y);
                    DrawPolarEllipse(hdc, shape.points[0].x, shape.points[0].y, radiusX, radiusY, shape.color);
                }
                    break;
                    
                case DrawingMode::ELLIPSE_MIDPOINT:
                {
                    int radiusX = abs(shape.points[1].x - shape.points[0].x);
                    int radiusY = abs(shape.points[1].y - shape.points[0].y);
                    DrawEllipseBresenham(hdc, shape.points[0].x, shape.points[0].y, radiusX, radiusY, shape.color);
                }
                    break;                case DrawingMode::SQUARE:
                {
                    if (shape.points.size() >= 2) {
                        // Calculate half-size (distance from center to edge)
                        int centerX = shape.points[0].x;
                        int centerY = shape.points[0].y;
                        int halfSize = (int)sqrt(
                            pow(shape.points[1].x - centerX, 2) +
                            pow(shape.points[1].y - centerY, 2)
                        );
                        
                        // Draw square using our DrawSquare function
                        DrawSquare(hdc, centerX, centerY, halfSize, shape.color);
                          // Apply Hermite fill if set
                        if (shape.fillMode == FillMode::SQUARE_FILL_HERMITE_VERTICAL) {
                            FillSquareWithVerticalHermite(hdc, centerX, centerY, halfSize, shape.color);
                        }
                    }
                }
                    break;
                
                case DrawingMode::RECTANGLE:
                {
                    if (shape.points.size() >= 2) {
                        // Draw rectangle using our DrawRectangle function
                        DrawRectangle(hdc, shape.points[0].x, shape.points[0].y,
                                    shape.points[1].x, shape.points[1].y, shape.color);
                    }
                }
                    break;
                
                case DrawingMode::POLYGON:
                {
                    if (shape.points.size() >= 3) {
                        // Draw polygon outline
                        for (size_t i = 0; i < shape.points.size() - 1; i++) {
                            DrawLineBresenham(hdc, shape.points[i].x, shape.points[i].y,
                                             shape.points[i + 1].x, shape.points[i + 1].y, shape.color);
                        }
                        // Close the polygon
                        DrawLineBresenham(hdc, shape.points.back().x, shape.points.back().y,
                                         shape.points[0].x, shape.points[0].y, shape.color);
                        
                        // Apply polygon fill if set
                        if (shape.fillMode == FillMode::POLYGON_CONVEX_FILL || 
                            shape.fillMode == FillMode::POLYGON_NONCONVEX_FILL) {
                            
                            PolygonPoint* pointsArray = new PolygonPoint[shape.points.size()];
                            for (size_t i = 0; i < shape.points.size(); i++) {
                                pointsArray[i] = PolygonPoint(shape.points[i].x, shape.points[i].y);
                            }
                            
                            if (shape.fillMode == FillMode::POLYGON_CONVEX_FILL) {
                                ConvexFill(hdc, pointsArray, shape.points.size(), shape.color);
                            } else {
                                NonConvexFill(hdc, pointsArray, shape.points.size(), shape.color);
                            }
                            
                            delete[] pointsArray;
                        }
                    }
                }
                    break;
                
                default:
                    // TODO: Implement other shape algorithms
                    break;
            }
        }
    }

    // Draw current shape being created (basic preview for now)
    if (m_isDrawing && !m_currentPoints.empty()) {
        switch (m_currentDrawingMode) {
            case DrawingMode::LINE_DDA:
            case DrawingMode::LINE_BRESENHAM:
            case DrawingMode::LINE_PARAMETRIC:
                if (m_currentPoints.size() == 1) {
                    // Draw preview line to mouse cursor
                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    MoveToEx(hdc, m_currentPoints[0].x, m_currentPoints[0].y, NULL);
                    LineTo(hdc, m_lastMousePos.x, m_lastMousePos.y);

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }
                break;

            case DrawingMode::CIRCLE_DIRECT:
            case DrawingMode::CIRCLE_POLAR:
            case DrawingMode::CIRCLE_ITERATIVE_POLAR:
            case DrawingMode::CIRCLE_MIDPOINT:
            case DrawingMode::CIRCLE_MODIFIED_MIDPOINT:
                if (m_currentPoints.size() == 1) {
                    // Draw preview circle using Windows API for now
                    int radius = (int)sqrt(
                            pow(m_lastMousePos.x - m_currentPoints[0].x, 2) +
                            pow(m_lastMousePos.y - m_currentPoints[0].y, 2)
                    );

                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);
                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

                    Ellipse(hdc,
                            m_currentPoints[0].x - radius, m_currentPoints[0].y - radius,
                            m_currentPoints[0].x + radius, m_currentPoints[0].y + radius);

                    SelectObject(hdc, oldPen);
                    SelectObject(hdc, oldBrush);
                    DeleteObject(tempPen);
                }
                break;

            case DrawingMode::ELLIPSE_DIRECT:
            case DrawingMode::ELLIPSE_POLAR:
            case DrawingMode::ELLIPSE_MIDPOINT:
                if (m_currentPoints.size() == 1) {
                    // Draw preview ellipse using Windows API for now
                    int radiusX = abs(m_lastMousePos.x - m_currentPoints[0].x);
                    int radiusY = abs(m_lastMousePos.y - m_currentPoints[0].y);

                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);
                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

                    Ellipse(hdc,
                            m_currentPoints[0].x - radiusX, m_currentPoints[0].y - radiusY,
                            m_currentPoints[0].x + radiusX, m_currentPoints[0].y + radiusY);

                    SelectObject(hdc, oldPen);
                    SelectObject(hdc, oldBrush);
                    DeleteObject(tempPen);
                }
                break;            case DrawingMode::SQUARE:
                // Draw current square preview
                if (m_currentPoints.size() == 1) {
                    // Calculate half-size (distance from center to mouse position)
                    int centerX = m_currentPoints[0].x;
                    int centerY = m_currentPoints[0].y;
                    int halfSize = (int)sqrt(
                        pow(m_lastMousePos.x - centerX, 2) +
                        pow(m_lastMousePos.y - centerY, 2)
                    );
                    
                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    // Draw square preview using lines
                    MoveToEx(hdc, centerX - halfSize, centerY - halfSize, NULL);
                    LineTo(hdc, centerX + halfSize, centerY - halfSize);
                    MoveToEx(hdc, centerX + halfSize, centerY - halfSize, NULL);
                    LineTo(hdc, centerX + halfSize, centerY + halfSize);
                    MoveToEx(hdc, centerX + halfSize, centerY + halfSize, NULL);
                    LineTo(hdc, centerX - halfSize, centerY + halfSize);
                    MoveToEx(hdc, centerX - halfSize, centerY + halfSize, NULL);
                    LineTo(hdc, centerX - halfSize, centerY - halfSize);                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }
                break;

            case DrawingMode::RECTANGLE:
                // Draw current rectangle preview
                if (m_currentPoints.size() == 1) {
                    // Draw preview rectangle using Windows API for now
                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);
                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

                    // Draw rectangle using center and corner point
                    int centerX = m_currentPoints[0].x;
                    int centerY = m_currentPoints[0].y;
                    int cornerX = m_lastMousePos.x;
                    int cornerY = m_lastMousePos.y;
                    
                    // Calculate rectangle corners based on center and corner point
                    int width = abs(cornerX - centerX) * 2;
                    int height = abs(cornerY - centerY) * 2;
                    
                    Rectangle(hdc, 
                        centerX - width/2, centerY - height/2,
                        centerX + width/2, centerY + height/2);

                    SelectObject(hdc, oldPen);
                    SelectObject(hdc, oldBrush);
                    DeleteObject(tempPen);
                }
                break;            case DrawingMode::POLYGON:
                // Draw current polygon lines using Windows API for now
                if (m_currentPoints.size() >= 2) {
                    HPEN tempPen = CreatePen(PS_SOLID, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    for (size_t i = 0; i < m_currentPoints.size() - 1; i++) {
                        MoveToEx(hdc, m_currentPoints[i].x, m_currentPoints[i].y, NULL);
                        LineTo(hdc, m_currentPoints[i + 1].x, m_currentPoints[i + 1].y);
                    }

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }

                // Draw preview line to mouse cursor
                if (!m_currentPoints.empty()) {
                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    MoveToEx(hdc, m_currentPoints.back().x, m_currentPoints.back().y, NULL);
                    LineTo(hdc, m_lastMousePos.x, m_lastMousePos.y);

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }
                break;            case DrawingMode::CURVE_CARDINAL:
                // Draw current Cardinal Spline preview
                if (m_currentPoints.size() >= 2) {
                    // Convert Point to HermitePoint for preview
                    HermitePoint* hermitePoints = new HermitePoint[m_currentPoints.size()];
                    for (size_t i = 0; i < m_currentPoints.size(); i++) {
                        hermitePoints[i] = HermitePoint(m_currentPoints[i].x, m_currentPoints[i].y);
                    }
                    
                    // Draw Cardinal Spline preview with default tension (0.5) and 50 points per segment
                    DrawCardinalSpline(hdc, hermitePoints, m_currentPoints.size(), 0.5, 50, m_currentColor);
                    
                    delete[] hermitePoints;
                }

                // Draw points as visual indicators
                if (!m_currentPoints.empty()) {
                    HPEN tempPen = CreatePen(PS_SOLID, 2, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    for (const auto& point : m_currentPoints) {
                        // Draw small circle at each control point
                        MoveToEx(hdc, point.x - 3, point.y, NULL);
                        LineTo(hdc, point.x + 3, point.y);
                        MoveToEx(hdc, point.x, point.y - 3, NULL);
                        LineTo(hdc, point.x, point.y + 3);
                    }

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }

                // Draw preview line to mouse cursor
                if (!m_currentPoints.empty()) {
                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    MoveToEx(hdc, m_currentPoints.back().x, m_currentPoints.back().y, NULL);
                    LineTo(hdc, m_lastMousePos.x, m_lastMousePos.y);

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }
                break;

            case DrawingMode::CURVE_BEZIER:
                // Draw current Bezier Curve preview
                if (m_currentPoints.size() >= 2) {
                    // Convert Point to BezierPoint for preview
                    BezierPoint* bezierPoints = new BezierPoint[m_currentPoints.size()];
                    for (size_t i = 0; i < m_currentPoints.size(); i++) {
                        bezierPoints[i] = BezierPoint(m_currentPoints[i].x, m_currentPoints[i].y);
                    }
                    
                    // Calculate adaptive step count based on curve length
                    double totalDistance = 0;
                    for (size_t i = 0; i < m_currentPoints.size() - 1; i++) {
                        double dx = m_currentPoints[i + 1].x - m_currentPoints[i].x;
                        double dy = m_currentPoints[i + 1].y - m_currentPoints[i].y;
                        totalDistance += sqrt(dx * dx + dy * dy);
                    }
                    int steps = std::max(50, std::min(1000, (int)(totalDistance * 1.5) + 20));
                    
                    // Draw Bezier Curve preview
                    DrawBezierCurve(hdc, bezierPoints, m_currentPoints.size(), steps, m_currentColor);
                    
                    delete[] bezierPoints;
                }

                // Draw points as visual indicators
                if (!m_currentPoints.empty()) {
                    HPEN tempPen = CreatePen(PS_SOLID, 2, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    for (const auto& point : m_currentPoints) {
                        // Draw small circle at each control point
                        MoveToEx(hdc, point.x - 3, point.y, NULL);
                        LineTo(hdc, point.x + 3, point.y);
                        MoveToEx(hdc, point.x, point.y - 3, NULL);
                        LineTo(hdc, point.x, point.y + 3);
                    }

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }

                // Draw preview line to mouse cursor
                if (!m_currentPoints.empty()) {
                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    MoveToEx(hdc, m_currentPoints.back().x, m_currentPoints.back().y, NULL);
                    LineTo(hdc, m_lastMousePos.x, m_lastMousePos.y);

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }
                break;

            case DrawingMode::CURVE_HERMITE:
                // Draw current Hermite Curve preview
                if (m_currentPoints.size() >= 4) {
                    // For Hermite curves, we need pairs of points: (P0, T0, P1, T1)
                    // Draw curves for complete point pairs
                    for (size_t i = 0; i + 3 < m_currentPoints.size(); i += 4) {
                        HermitePoint P0(m_currentPoints[i].x, m_currentPoints[i].y);
                        HermitePoint T0(m_currentPoints[i + 1].x - m_currentPoints[i].x, 
                                      m_currentPoints[i + 1].y - m_currentPoints[i].y);
                        HermitePoint P1(m_currentPoints[i + 2].x, m_currentPoints[i + 2].y);
                        HermitePoint T1(m_currentPoints[i + 3].x - m_currentPoints[i + 2].x, 
                                      m_currentPoints[i + 3].y - m_currentPoints[i + 2].y);
                        
                        // Calculate adaptive point count
                        double dx = P1.x - P0.x;
                        double dy = P1.y - P0.y;
                        double distance = sqrt(dx * dx + dy * dy);
                        int points = std::max(50, std::min(1000, (int)(distance * 2) + 10));
                        
                        DrawHermiteCurve(hdc, P0, T0, P1, T1, points, m_currentColor);
                    }
                }

                // Draw points as visual indicators
                if (!m_currentPoints.empty()) {
                    HPEN tempPen = CreatePen(PS_SOLID, 2, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    for (size_t i = 0; i < m_currentPoints.size(); i++) {
                        const auto& point = m_currentPoints[i];
                        // Draw different markers for control points vs tangent points
                        if (i % 4 == 0 || i % 4 == 2) {
                            // Control points - draw circles
                            MoveToEx(hdc, point.x - 3, point.y, NULL);
                            LineTo(hdc, point.x + 3, point.y);
                            MoveToEx(hdc, point.x, point.y - 3, NULL);
                            LineTo(hdc, point.x, point.y + 3);
                        } else {
                            // Tangent points - draw squares
                            MoveToEx(hdc, point.x - 2, point.y - 2, NULL);
                            LineTo(hdc, point.x + 2, point.y - 2);
                            LineTo(hdc, point.x + 2, point.y + 2);
                            LineTo(hdc, point.x - 2, point.y + 2);
                            LineTo(hdc, point.x - 2, point.y - 2);
                        }
                    }

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }

                // Draw preview line to mouse cursor
                if (!m_currentPoints.empty()) {
                    HPEN tempPen = CreatePen(PS_DOT, 1, m_currentColor);
                    HPEN oldPen = (HPEN)SelectObject(hdc, tempPen);

                    MoveToEx(hdc, m_currentPoints.back().x, m_currentPoints.back().y, NULL);
                    LineTo(hdc, m_lastMousePos.x, m_lastMousePos.y);

                    SelectObject(hdc, oldPen);
                    DeleteObject(tempPen);
                }
                break;
        }
    }

    ReleaseDC(m_hwnd, hdc);
}

// Clear canvas
void GraphicsWindow::ClearCanvas() {
    m_shapes.clear();
    m_isDrawing = false;
    m_currentPoints.clear();
    
    // Clear offscreen buffer
    ClearOffscreenBuffer();
    
    InvalidateRect(m_hwnd, NULL, TRUE);
}

// Run message loop
void GraphicsWindow::Run() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Set drawing mode
void GraphicsWindow::SetDrawingMode(DrawingMode mode) {
    m_currentDrawingMode = mode;
    m_isDrawing = false;
    m_currentPoints.clear();
    
    // Reset fill mode when switching to drawing mode
    m_fillMode = false;
    
    InvalidateRect(m_hwnd, NULL, TRUE);
}

// Set drawing color
void GraphicsWindow::SetDrawingColor(COLORREF color) {
    m_currentColor = color;
    UpdateCurrentPen();
    InvalidateRect(m_hwnd, NULL, TRUE);
}

// Set background color
void GraphicsWindow::SetBackgroundColor(COLORREF color) {
    m_backgroundColor = color;
    if (m_backgroundBrush) DeleteObject(m_backgroundBrush);
    m_backgroundBrush = CreateSolidBrush(m_backgroundColor);
    InvalidateRect(m_hwnd, NULL, TRUE);
}

// Set title
void GraphicsWindow::SetTitle(const std::string& title) {
    if (m_hwnd) {
        SetWindowText(m_hwnd, title.c_str());
    }
}

// Set mouse cursor
void GraphicsWindow::SetMouseCursor(HCURSOR cursor) {
    m_currentCursor = cursor;
    if (m_hwnd) {
        SetClassLongPtr(m_hwnd, GCLP_HCURSOR, (LONG_PTR)cursor);
        ::SetCursor(cursor);
    }
}

// Set fill mode
void GraphicsWindow::SetFillMode(FillMode mode) {    m_currentFillMode = mode;
      // Enable fill mode for circle fill modes and polygon operations
    m_fillMode = (mode == FillMode::CIRCLE_FILL_LINES || 
                  mode == FillMode::CIRCLE_FILL_QUARTER || 
                  mode == FillMode::CIRCLE_FILL_CIRCLES ||
                  mode == FillMode::POLYGON_CONVEX_FILL ||
                  mode == FillMode::POLYGON_NONCONVEX_FILL ||
                  mode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON ||
                  mode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON ||
                  mode == FillMode::SQUARE_FILL_HERMITE_VERTICAL ||
                  mode == FillMode::RECTANGLE_FILL_BEZIER_HORIZONTAL);
    
    // Reset drawing state when entering fill mode
    if (m_fillMode) {
        m_isDrawing = false;
        m_currentPoints.clear();
        m_isDrawingPolygon = false;
        m_polygonPoints.clear();
    }
    
    InvalidateRect(m_hwnd, NULL, TRUE);
}

// Set line thickness (placeholder)
void GraphicsWindow::SetLineThickness(int thickness) {
    m_lineThickness = thickness;
    UpdateCurrentPen();
}

// Save to file (placeholder)
void GraphicsWindow::SaveToFile() {
    OPENFILENAME ofn;              
    char szFile[MAX_PATH] = "";   

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hwnd;  
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);


    ofn.lpstrFilter = "binary Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = "bin";
    ofn.lpstrTitle = "Save Drawing As";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn)) {
        std::ofstream outFile(szFile, std::ios::binary);
        if (!outFile) {
            MessageBox(m_hwnd, "Failed to open file for writing.", "Error", MB_OK | MB_ICONERROR);
            return;
        }

        int shapeCnt = m_shapes.size();
        outFile.write(reinterpret_cast<const char*>(&shapeCnt), sizeof(shapeCnt));

        for(auto& shape:m_shapes) {
            outFile.write(reinterpret_cast<const char*>(&shape.mode), sizeof(shape.mode));
            outFile.write(reinterpret_cast<const char*>(&shape.color), sizeof(shape.color));
            outFile.write(reinterpret_cast<const char*>(&shape.fillMode), sizeof(shape.fillMode));
            outFile.write(reinterpret_cast<const char*>(&shape.thickness), sizeof(shape.thickness));

            int pointCnt = shape.points.size();
            outFile.write(reinterpret_cast<const char*>(&pointCnt), sizeof(pointCnt));

            if (pointCnt > 0) {
                outFile.write(reinterpret_cast<const char*>(shape.points.data()), pointCnt * sizeof(Point));
            }
        }
        
        outFile.close();
    }
}


void GraphicsWindow::LoadFromFile() {
    OPENFILENAME ofn;
    char szFile[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);

    ofn.lpstrFilter = "Binary Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = "bin";
    ofn.lpstrTitle = "Open Drawing";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        std::ifstream inFile(szFile, std::ios::binary);
        if (!inFile) {
            MessageBox(m_hwnd, "Failed to open file for reading.", "Error", MB_OK | MB_ICONERROR);
            return;
        }

        ClearCanvas();

        int shapeCnt = 0;
        inFile.read(reinterpret_cast<char*>(&shapeCnt), sizeof(shapeCnt));
        for (int i = 0; i < shapeCnt; ++i) {
            Shape shape;

            inFile.read(reinterpret_cast<char*>(&shape.mode), sizeof(shape.mode));
            inFile.read(reinterpret_cast<char*>(&shape.color), sizeof(shape.color));
            inFile.read(reinterpret_cast<char*>(&shape.fillMode), sizeof(shape.fillMode));
            inFile.read(reinterpret_cast<char*>(&shape.thickness), sizeof(shape.thickness));

            int pointCnt = 0;
            inFile.read(reinterpret_cast<char*>(&pointCnt), sizeof(pointCnt));

            shape.points.resize(pointCnt);
            if (pointCnt > 0) {
                inFile.read(reinterpret_cast<char*>(shape.points.data()), pointCnt * sizeof(Point));
            }
            m_shapes.push_back(shape);
        }
        inFile.close();
        InvalidateRect(m_hwnd, nullptr, TRUE);
        RedrawAll();
        RebuildOffscreenBuffer();
        InvalidateRect(m_hwnd, NULL, TRUE);
    }
}

// Create offscreen buffer for double buffering
void GraphicsWindow::CreateOffscreenBuffer(int width, int height) {
    CleanupOffscreenBuffer();
    
    m_canvasWidth = width;
    m_canvasHeight = height;
    
    HDC hdc = GetDC(m_hwnd);
    m_offscreenDC = CreateCompatibleDC(hdc);
    m_offscreenBitmap = CreateCompatibleBitmap(hdc, width, height);
    m_oldBitmap = (HBITMAP)SelectObject(m_offscreenDC, m_offscreenBitmap);
    ReleaseDC(m_hwnd, hdc);
    
    ClearOffscreenBuffer();
}

// Cleanup offscreen buffer
void GraphicsWindow::CleanupOffscreenBuffer() {
    if (m_offscreenDC) {
        if (m_oldBitmap) {
            SelectObject(m_offscreenDC, m_oldBitmap);
            m_oldBitmap = nullptr;
        }
        DeleteDC(m_offscreenDC);
        m_offscreenDC = nullptr;
    }
    if (m_offscreenBitmap) {
        DeleteObject(m_offscreenBitmap);
        m_offscreenBitmap = nullptr;
    }
}

// Clear offscreen buffer with background color
void GraphicsWindow::ClearOffscreenBuffer() {
    if (m_offscreenDC) {
        RECT rect = {0, 0, m_canvasWidth, m_canvasHeight};
        FillRect(m_offscreenDC, &rect, m_backgroundBrush);
    }
}

// Draw shape to buffer
void GraphicsWindow::DrawShapeToBuffer(const Shape& shape) {
    if (!m_offscreenDC || shape.points.size() < 2) return;

    // Draw shape using its respective algorithm to offscreen buffer
    switch (shape.mode) {
        case DrawingMode::LINE_DDA:
            DrawLineDDA(m_offscreenDC, shape.points[0].x, shape.points[0].y,
                       shape.points[1].x, shape.points[1].y, shape.color);
            break;
            
        case DrawingMode::LINE_BRESENHAM:
            DrawLineBresenham(m_offscreenDC, shape.points[0].x, shape.points[0].y,
                             shape.points[1].x, shape.points[1].y, shape.color);
            break;
            
        case DrawingMode::LINE_PARAMETRIC:
            DrawLineParametric(m_offscreenDC, shape.points[0].x, shape.points[0].y,
                              shape.points[1].x, shape.points[1].y, shape.color);
            break;
            
        case DrawingMode::CIRCLE_DIRECT:
        {
            int radius = (int)sqrt(
                pow(shape.points[1].x - shape.points[0].x, 2) +
                pow(shape.points[1].y - shape.points[0].y, 2)
            );
            DrawDirectCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            
            // Apply fill mode if set
            if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                FillCircleWithLines(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                FillQuarterCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                FillCircleWithCircles(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            }
        }
            break;
            
        case DrawingMode::CIRCLE_POLAR:
        {
            int radius = (int)sqrt(
                pow(shape.points[1].x - shape.points[0].x, 2) +
                pow(shape.points[1].y - shape.points[0].y, 2)
            );
            DrawPolarCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            
            // Apply fill mode if set
            if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                FillCircleWithLines(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                FillQuarterCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                FillCircleWithCircles(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            }
        }
            break;
            
        case DrawingMode::CIRCLE_ITERATIVE_POLAR:
        {
            int radius = (int)sqrt(
                pow(shape.points[1].x - shape.points[0].x, 2) +
                pow(shape.points[1].y - shape.points[0].y, 2)
            );
            DrawIterativePolarCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            
            // Apply fill mode if set
            if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                FillCircleWithLines(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                FillQuarterCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                FillCircleWithCircles(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            }
        }
            break;
            
        case DrawingMode::CIRCLE_MIDPOINT:
        {
            int radius = (int)sqrt(
                pow(shape.points[1].x - shape.points[0].x, 2) +
                pow(shape.points[1].y - shape.points[0].y, 2)
            );
            DrawCircleBresenham(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            
            // Apply fill mode if set
            if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                FillCircleWithLines(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                FillQuarterCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                FillCircleWithCircles(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            }
        }
            break;
            
        case DrawingMode::CIRCLE_MODIFIED_MIDPOINT:
        {
            int radius = (int)sqrt(
                pow(shape.points[1].x - shape.points[0].x, 2) +
                pow(shape.points[1].y - shape.points[0].y, 2)
            );
            DrawCircleDDA1(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            
            // Apply fill mode if set
            if (shape.fillMode == FillMode::CIRCLE_FILL_LINES) {
                FillCircleWithLines(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_QUARTER) {
                FillQuarterCircle(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            } else if (shape.fillMode == FillMode::CIRCLE_FILL_CIRCLES) {
                FillCircleWithCircles(m_offscreenDC, shape.points[0].x, shape.points[0].y, radius, shape.color);
            }
        }
            break;
            
        case DrawingMode::ELLIPSE_DIRECT:
        {
            int radiusX = abs(shape.points[1].x - shape.points[0].x);
            int radiusY = abs(shape.points[1].y - shape.points[0].y);
            DrawDirectEllipse(m_offscreenDC, shape.points[0].x, shape.points[0].y, radiusX, radiusY, shape.color);
        }
            break;
            
        case DrawingMode::ELLIPSE_POLAR:
        {
            int radiusX = abs(shape.points[1].x - shape.points[0].x);
            int radiusY = abs(shape.points[1].y - shape.points[0].y);
            DrawPolarEllipse(m_offscreenDC, shape.points[0].x, shape.points[0].y, radiusX, radiusY, shape.color);
        }
            break;
            
        case DrawingMode::ELLIPSE_MIDPOINT:
        {
            int radiusX = abs(shape.points[1].x - shape.points[0].x);
            int radiusY = abs(shape.points[1].y - shape.points[0].y);
            DrawEllipseBresenham(m_offscreenDC, shape.points[0].x, shape.points[0].y, radiusX, radiusY, shape.color);
        }
            break;        case DrawingMode::SQUARE:
        {
            if (shape.points.size() >= 2) {
                // Calculate half-size (distance from center to edge)
                int centerX = shape.points[0].x;
                int centerY = shape.points[0].y;
                int halfSize = (int)sqrt(
                    pow(shape.points[1].x - centerX, 2) +
                    pow(shape.points[1].y - centerY, 2)
                );
                
                // Draw square using our DrawSquare function
                DrawSquare(m_offscreenDC, centerX, centerY, halfSize, shape.color);
                  // Apply Hermite fill if set
                if (shape.fillMode == FillMode::SQUARE_FILL_HERMITE_VERTICAL) {
                    FillSquareWithVerticalHermite(m_offscreenDC, centerX, centerY, halfSize, shape.color);
                }
            }
        }
            break;
              case DrawingMode::RECTANGLE:
        {
            if (shape.points.size() >= 2) {
                // Draw rectangle using our DrawRectangle function
                DrawRectangle(m_offscreenDC, shape.points[0].x, shape.points[0].y,
                            shape.points[1].x, shape.points[1].y, shape.color);
                  // Apply Bezier fill if set
                if (shape.fillMode == FillMode::RECTANGLE_FILL_BEZIER_HORIZONTAL) {
                    FillRectangleWithHorizontalBezier(m_offscreenDC, shape.points[0].x, shape.points[0].y,
                                                    shape.points[1].x, shape.points[1].y, shape.color);
                }
            }
        }
            break;
              case DrawingMode::POLYGON:
        {
            if (shape.points.size() >= 3) {

                // draw the polygon
                DrawPolygon(m_offscreenDC, shape.points ,shape.color);


                // Apply polygon fill if set
                if (shape.fillMode == FillMode::POLYGON_CONVEX_FILL || 
                    shape.fillMode == FillMode::POLYGON_NONCONVEX_FILL) {
                    
                    PolygonPoint* pointsArray = new PolygonPoint[shape.points.size()];
                    for (size_t i = 0; i < shape.points.size(); i++) {
                        pointsArray[i] = PolygonPoint(shape.points[i].x, shape.points[i].y);
                    }
                    
                    if (shape.fillMode == FillMode::POLYGON_CONVEX_FILL) {
                        ConvexFill(m_offscreenDC, pointsArray, shape.points.size(), shape.color);
                    } else {
                        NonConvexFill(m_offscreenDC, pointsArray, shape.points.size(), shape.color);
                    }
                    
                    delete[] pointsArray;
                }
            }
        }
            break;        case DrawingMode::CURVE_CARDINAL:
        {
            if (shape.points.size() >= 2) {
                // Convert Point to HermitePoint
                HermitePoint* hermitePoints = new HermitePoint[shape.points.size()];
                for (size_t i = 0; i < shape.points.size(); i++) {
                    hermitePoints[i] = HermitePoint(shape.points[i].x, shape.points[i].y);
                }
                
                // Draw Cardinal Spline with default tension (0.5) and 50 points per segment
                DrawCardinalSpline(m_offscreenDC, hermitePoints, shape.points.size(), 0.5, 50, shape.color);
                
                delete[] hermitePoints;
            }
        }
            break;

        case DrawingMode::CURVE_BEZIER:
        {
            if (shape.points.size() >= 2) {
                // Convert Point to BezierPoint
                BezierPoint* bezierPoints = new BezierPoint[shape.points.size()];
                for (size_t i = 0; i < shape.points.size(); i++) {
                    bezierPoints[i] = BezierPoint(shape.points[i].x, shape.points[i].y);
                }
                
                // Calculate adaptive step count based on curve length
                double totalDistance = 0;
                for (size_t i = 0; i < shape.points.size() - 1; i++) {
                    double dx = shape.points[i + 1].x - shape.points[i].x;
                    double dy = shape.points[i + 1].y - shape.points[i].y;
                    totalDistance += sqrt(dx * dx + dy * dy);
                }
                int steps = std::max(50, std::min(1000, (int)(totalDistance * 1.5) + 20));
                
                // Draw Bezier Curve
                DrawBezierCurve(m_offscreenDC, bezierPoints, shape.points.size(), steps, shape.color);
                
                delete[] bezierPoints;
            }
        }
            break;

        case DrawingMode::CURVE_HERMITE:
        {
            if (shape.points.size() >= 4) {
                // For Hermite curves, draw curves for complete point quadruples: (P0, T0, P1, T1)
                for (size_t i = 0; i + 3 < shape.points.size(); i += 4) {
                    HermitePoint P0(shape.points[i].x, shape.points[i].y);
                    HermitePoint T0(shape.points[i + 1].x - shape.points[i].x, 
                                  shape.points[i + 1].y - shape.points[i].y);
                    HermitePoint P1(shape.points[i + 2].x, shape.points[i + 2].y);
                    HermitePoint T1(shape.points[i + 3].x - shape.points[i + 2].x, 
                                  shape.points[i + 3].y - shape.points[i + 2].y);
                    
                    // Calculate adaptive point count
                    double dx = P1.x - P0.x;
                    double dy = P1.y - P0.y;
                    double distance = sqrt(dx * dx + dy * dy);
                    int points = std::max(50, std::min(1000, (int)(distance * 2) + 10));
                    
                    DrawHermiteCurve(m_offscreenDC, P0, T0, P1, T1, points, shape.color);
                }
            }
        }
            break;
            
        default:
            // TODO: Implement other shape algorithms
            break;
    }
}

// Rebuild offscreen buffer
void GraphicsWindow::RebuildOffscreenBuffer() {
    if (!m_offscreenDC) return;
    
    // Clear buffer
    ClearOffscreenBuffer();
    
    // Redraw all shapes
    for (const auto& shape : m_shapes) {
        DrawShapeToBuffer(shape);
    }
}

// ========================================
// GLOBAL HELPER FUNCTIONS IMPLEMENTATION
// ========================================

// Create graphics window
GraphicsWindow* CreateGraphicsWindow(HINSTANCE hInstance, int nCmdShow, const std::string& title) {
    GraphicsWindow* window = new GraphicsWindow();
    if (window->Initialize(hInstance, nCmdShow)) {
        window->SetTitle(title);
        return window;
    }
    delete window;
    return nullptr;
}

// Run graphics program
int RunGraphicsProgram(GraphicsWindow* window) {
    if (!window) return 1;

    window->Run();
    delete window;
    return 0;
}

#endif // GRAPHICS_WINDOW_H