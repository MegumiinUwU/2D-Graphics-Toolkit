#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include <windows.h>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include "LineAlgorithms.h"

// ========================================
// CONSTANTS AND DEFINITIONS
// ========================================

// Window dimensions
#define DEFAULT_WINDOW_WIDTH  1024
#define DEFAULT_WINDOW_HEIGHT 768

// Menu IDs for various operations
#define MENU_FILE_NEW         1001
#define MENU_FILE_SAVE        1002
#define MENU_FILE_LOAD        1003
#define MENU_FILE_EXIT        1004

#define MENU_SHAPES_LINE      2001
#define MENU_SHAPES_LINE_DDA      2011
#define MENU_SHAPES_LINE_BRESENHAM 2012
#define MENU_SHAPES_LINE_PARAMETRIC 2013
#define MENU_SHAPES_CIRCLE    2002
#define MENU_SHAPES_ELLIPSE   2003
#define MENU_SHAPES_POLYGON   2004

#define MENU_COLORS_RED       3001
#define MENU_COLORS_GREEN     3002
#define MENU_COLORS_BLUE      3003
#define MENU_COLORS_BLACK     3004
#define MENU_COLORS_WHITE     3005
#define MENU_COLORS_CUSTOM    3006

#define MENU_FILL_NONE        4001
#define MENU_FILL_SOLID       4002
#define MENU_FILL_PATTERN     4003

#define MENU_TOOLS_CLEAR      5001
#define MENU_TOOLS_ZOOM_IN    5002
#define MENU_TOOLS_ZOOM_OUT   5003

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
    CURVE_CARDINAL,
    NONE
};

// Fill modes
enum class FillMode {
    NONE,
    SOLID,
    FLOOD_FILL_RECURSIVE,
    FLOOD_FILL_NON_RECURSIVE,
    SCANLINE_CONVEX,
    SCANLINE_NON_CONVEX
};

// Point structure for coordinates
struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
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

    // Drawing state
    DrawingMode m_currentDrawingMode;
    FillMode m_currentFillMode;
    COLORREF m_currentColor;
    COLORREF m_backgroundColor;
    int m_lineThickness;

    // Mouse interaction state
    bool m_isDrawing;
    std::vector<Point> m_currentPoints;
    Point m_lastMousePos;

    // Shape storage
    std::vector<Shape> m_shapes;

    // Pens and brushes
    HPEN m_currentPen;
    HBRUSH m_currentBrush;
    HBRUSH m_backgroundBrush;

    // Menu handle
    HMENU m_hMenuBar;

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
    void UpdateCurrentPen();
    void HandleMouseClick(int x, int y, bool isLeftButton);
    void HandleMouseMove(int x, int y);
    void HandleMenuCommand(WPARAM wParam);
    void RedrawAll();
    void ClearCanvas();
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

public:
    // Constructor and destructor
    GraphicsWindow();
    ~GraphicsWindow();

    // Window management
    bool Initialize(HINSTANCE hInstance, int nCmdShow);
    void Run();
    void SetTitle(const std::string& title);
    void SetBackgroundColor(COLORREF color);

    // Drawing mode setters
    void SetDrawingMode(DrawingMode mode);
    void SetFillMode(FillMode mode);
    void SetDrawingColor(COLORREF color);
    void SetLineThickness(int thickness);

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
        , m_currentDrawingMode(DrawingMode::LINE_DDA)
        , m_currentFillMode(FillMode::NONE)
        , m_currentColor(RGB(0, 0, 0))  // Black
        , m_backgroundColor(RGB(255, 255, 255))  // White
        , m_lineThickness(1)
        , m_isDrawing(false)
        , m_currentPen(nullptr)
        , m_currentBrush(nullptr)
        , m_backgroundBrush(nullptr)
        , m_hMenuBar(nullptr)
{
}

// Destructor
GraphicsWindow::~GraphicsWindow() {
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
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(m_backgroundColor);
    wc.lpszClassName = s_className;
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);  // Custom cursor for drawing
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

    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);

    return true;
}

// Initialize menus
void GraphicsWindow::InitializeMenus() {
    m_hMenuBar = CreateMenu();

    // File menu
    HMENU hFileMenu = CreatePopupMenu();
    AppendMenu(hFileMenu, MF_STRING, MENU_FILE_NEW, "New\tCtrl+N");
    AppendMenu(hFileMenu, MF_STRING, MENU_FILE_SAVE, "Save\tCtrl+S");
    AppendMenu(hFileMenu, MF_STRING, MENU_FILE_LOAD, "Open\tCtrl+O");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, MENU_FILE_EXIT, "Exit\tAlt+F4");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, "File");

    // Shapes menu
    HMENU hShapesMenu = CreatePopupMenu();
    
    // Line submenu
    HMENU hLineMenu = CreatePopupMenu();
    AppendMenu(hLineMenu, MF_STRING, MENU_SHAPES_LINE_DDA, "DDA Algorithm");
    AppendMenu(hLineMenu, MF_STRING, MENU_SHAPES_LINE_BRESENHAM, "Bresenham (Midpoint)");
    AppendMenu(hLineMenu, MF_STRING, MENU_SHAPES_LINE_PARAMETRIC, "Parametric");
    AppendMenu(hShapesMenu, MF_POPUP, (UINT_PTR)hLineMenu, "Line");
    
    AppendMenu(hShapesMenu, MF_STRING, MENU_SHAPES_CIRCLE, "Circle (Midpoint)");
    AppendMenu(hShapesMenu, MF_STRING, MENU_SHAPES_ELLIPSE, "Ellipse");
    AppendMenu(hShapesMenu, MF_STRING, MENU_SHAPES_POLYGON, "Polygon");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hShapesMenu, "Shapes");

    // Colors menu
    HMENU hColorsMenu = CreatePopupMenu();
    AppendMenu(hColorsMenu, MF_STRING, MENU_COLORS_BLACK, "Black");
    AppendMenu(hColorsMenu, MF_STRING, MENU_COLORS_RED, "Red");
    AppendMenu(hColorsMenu, MF_STRING, MENU_COLORS_GREEN, "Green");
    AppendMenu(hColorsMenu, MF_STRING, MENU_COLORS_BLUE, "Blue");
    AppendMenu(hColorsMenu, MF_STRING, MENU_COLORS_WHITE, "White");
    AppendMenu(hColorsMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hColorsMenu, MF_STRING, MENU_COLORS_CUSTOM, "Custom Color...");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hColorsMenu, "Colors");

    // Tools menu
    HMENU hToolsMenu = CreatePopupMenu();
    AppendMenu(hToolsMenu, MF_STRING, MENU_TOOLS_CLEAR, "Clear Canvas\tCtrl+L");
    AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hToolsMenu, "Tools");

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
            break;

        case WM_MOUSEMOVE:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            HandleMouseMove(x, y);
        }
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Draw all saved shapes
            RedrawAll();

            // Draw instructions
            SetTextColor(hdc, RGB(100, 100, 100));
            SetBkMode(hdc, TRANSPARENT);
            TextOut(hdc, 10, 10, "Left click to draw shapes | Right click to finish/cancel", 55);

            std::string modeText = "Current mode: ";
            switch (m_currentDrawingMode) {
                case DrawingMode::LINE_DDA: modeText += "Line (DDA)"; break;
                case DrawingMode::LINE_BRESENHAM: modeText += "Line (Bresenham)"; break;
                case DrawingMode::LINE_PARAMETRIC: modeText += "Line (Parametric)"; break;
                case DrawingMode::CIRCLE_MIDPOINT: modeText += "Circle (Midpoint)"; break;
                case DrawingMode::ELLIPSE_MIDPOINT: modeText += "Ellipse"; break;
                case DrawingMode::POLYGON: modeText += "Polygon"; break;
                default: modeText += "None"; break;
            }
            TextOut(hdc, 10, 30, modeText.c_str(), modeText.length());

            EndPaint(hwnd, &ps);
        }
            break;

        case WM_SIZE:
            // Handle window resize if needed
            InvalidateRect(hwnd, NULL, TRUE);
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
            shape.fillMode = m_currentFillMode;
            shape.points = m_currentPoints;
            shape.thickness = m_lineThickness;
            m_shapes.push_back(shape);
        }

        // Reset drawing state
        m_isDrawing = false;
        m_currentPoints.clear();
        InvalidateRect(m_hwnd, NULL, TRUE);
        return;
    }

    // Left click - add point or complete shape
    Point newPoint(x, y);

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
                shape.fillMode = m_currentFillMode;
                shape.points = m_currentPoints;
                shape.thickness = m_lineThickness;
                m_shapes.push_back(shape);

                m_isDrawing = false;
                m_currentPoints.clear();
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
            break;

        case DrawingMode::CIRCLE_MIDPOINT:
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
                shape.fillMode = m_currentFillMode;
                shape.points = m_currentPoints;
                shape.thickness = m_lineThickness;
                m_shapes.push_back(shape);

                m_isDrawing = false;
                m_currentPoints.clear();
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
            break;

        case DrawingMode::POLYGON:
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

// Handle menu command
void GraphicsWindow::HandleMenuCommand(WPARAM wParam) {
    switch (LOWORD(wParam)) {
        case MENU_FILE_NEW:
            ClearCanvas();
            break;

        case MENU_FILE_EXIT:
            PostMessage(m_hwnd, WM_CLOSE, 0, 0);
            break;

        case MENU_SHAPES_LINE_DDA:
            SetDrawingMode(DrawingMode::LINE_DDA);
            break;

        case MENU_SHAPES_LINE_BRESENHAM:
            SetDrawingMode(DrawingMode::LINE_BRESENHAM);
            break;

        case MENU_SHAPES_LINE_PARAMETRIC:
            SetDrawingMode(DrawingMode::LINE_PARAMETRIC);
            break;

        case MENU_SHAPES_CIRCLE:
            SetDrawingMode(DrawingMode::CIRCLE_MIDPOINT);
            break;

        case MENU_SHAPES_ELLIPSE:
            SetDrawingMode(DrawingMode::ELLIPSE_MIDPOINT);
            break;

        case MENU_SHAPES_POLYGON:
            SetDrawingMode(DrawingMode::POLYGON);
            break;

        case MENU_COLORS_BLACK:
            SetDrawingColor(RGB(0, 0, 0));
            break;

        case MENU_COLORS_RED:
            SetDrawingColor(RGB(255, 0, 0));
            break;

        case MENU_COLORS_GREEN:
            SetDrawingColor(RGB(0, 255, 0));
            break;

        case MENU_COLORS_BLUE:
            SetDrawingColor(RGB(0, 0, 255));
            break;

        case MENU_COLORS_WHITE:
            SetDrawingColor(RGB(255, 255, 255));
            break;

        case MENU_TOOLS_CLEAR:
            ClearCanvas();
            break;
    }
}

// Redraw all shapes using implemented algorithms
void GraphicsWindow::RedrawAll() {
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

            case DrawingMode::CIRCLE_MIDPOINT:
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

            case DrawingMode::POLYGON:
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

// Set fill mode (placeholder)
void GraphicsWindow::SetFillMode(FillMode mode) {
    m_currentFillMode = mode;
}

// Set line thickness (placeholder)
void GraphicsWindow::SetLineThickness(int thickness) {
    m_lineThickness = thickness;
    UpdateCurrentPen();
}

// Save to file (placeholder)
void GraphicsWindow::SaveToFile(const std::string& filename) {
    // TODO: Implement file saving
}

// Load from file (placeholder)
void GraphicsWindow::LoadFromFile(const std::string& filename) {
    // TODO: Implement file loading
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

// ========================================
// DRAWING ALGORITHMS IMPLEMENTATION
// ========================================

class DrawingAlgorithms {
public:
    // Line drawing algorithms
    static void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);
    static void DrawLineMidpoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);
    static void DrawLineParametric(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);

    // Circle drawing algorithms
    static void DrawCircleDirect(HDC hdc, int centerX, int centerY, int radius, COLORREF color);
    static void DrawCirclePolar(HDC hdc, int centerX, int centerY, int radius, COLORREF color);
    static void DrawCircleIterativePolar(HDC hdc, int centerX, int centerY, int radius, COLORREF color);
    static void DrawCircleMidpoint(HDC hdc, int centerX, int centerY, int radius, COLORREF color);
    static void DrawCircleModifiedMidpoint(HDC hdc, int centerX, int centerY, int radius, COLORREF color);

    // Ellipse drawing algorithms
    static void DrawEllipseDirect(HDC hdc, int centerX, int centerY, int radiusX, int radiusY, COLORREF color);
    static void DrawEllipsePolar(HDC hdc, int centerX, int centerY, int radiusX, int radiusY, COLORREF color);
    static void DrawEllipseMidpoint(HDC hdc, int centerX, int centerY, int radiusX, int radiusY, COLORREF color);

    // Curve algorithms
    static void DrawCardinalSpline(HDC hdc, const std::vector<Point>& controlPoints, COLORREF color, float tension = 0.5f);

    // Filling algorithms
    static void FloodFillRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF boundaryColor);
    static void FloodFillNonRecursive(HDC hdc, int x, int y, COLORREF fillColor, COLORREF boundaryColor);
    static void ScanLineFillConvex(HDC hdc, const std::vector<Point>& vertices, COLORREF fillColor);
    static void ScanLineFillNonConvex(HDC hdc, const std::vector<Point>& vertices, COLORREF fillColor);

    // Helper functions
    static void SetPixel(HDC hdc, int x, int y, COLORREF color);
    static COLORREF GetPixel(HDC hdc, int x, int y);
    static void DrawCirclePoints(HDC hdc, int centerX, int centerY, int x, int y, COLORREF color);
    static void DrawEllipsePoints(HDC hdc, int centerX, int centerY, int x, int y, COLORREF color);
};

// ========================================
// UTILITY FUNCTIONS
// ========================================

namespace GraphicsUtils {
    // Color utilities
    COLORREF RGBToColorRef(int r, int g, int b);
    void ColorRefToRGB(COLORREF color, int& r, int& g, int& b);

    // File dialog helpers
    std::string OpenFileDialog(HWND hwnd);
    std::string SaveFileDialog(HWND hwnd);

    // Math utilities
    double Distance(const Point& p1, const Point& p2);
    Point MidPoint(const Point& p1, const Point& p2);

    // Clipping algorithms
    bool ClipPointToRectangle(const Point& point, const RECT& clipRect);
    bool ClipLineToRectangle(Point& p1, Point& p2, const RECT& clipRect);
    std::vector<Point> ClipPolygonToRectangle(const std::vector<Point>& polygon, const RECT& clipRect);

    // Circle clipping
    bool ClipPointToCircle(const Point& point, const Point& center, int radius);
    bool ClipLineToCircle(Point& p1, Point& p2, const Point& center, int radius);
}

#endif // GRAPHICS_WINDOW_H 