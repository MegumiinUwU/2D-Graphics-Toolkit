#include "../../include/Window.h"

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
        , m_currentBrush(nullptr)
        , m_backgroundBrush(nullptr)
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
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(m_backgroundColor);
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
void GraphicsWindow::SetFillMode(FillMode mode) {
    m_currentFillMode = mode;
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

// Set line thickness
void GraphicsWindow::SetLineThickness(int thickness) {
    m_lineThickness = thickness;
    UpdateCurrentPen();
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
