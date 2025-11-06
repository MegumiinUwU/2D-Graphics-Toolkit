#ifndef WINDOW_H
#define WINDOW_H

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
#include "GraphicsTypes.h"

using namespace std;

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
    HBRUSH m_backgroundBrush;

    // Menu handle
    HMENU m_hMenuBar;

    // Cursor handle
    HCURSOR m_currentCursor;

    // Window class name
    static const char* s_className;

    // Static window procedure
    static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Instance window procedure
    LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Helper methods - Menu
    void InitializeMenus();
    void HandleMenuCommand(WPARAM wParam);

    // Helper methods - Mouse
    void HandleMouseClick(int x, int y, bool isLeftButton);
    void HandleMouseMove(int x, int y);

    // Helper methods - Drawing
    void InitializeDrawingTools();
    void CleanupDrawingTools();
    void UpdateCurrentPen();
    void RedrawAll();
    void DrawShapeToBuffer(const Shape& shape);

    // Helper methods - Buffer
    void CreateOffscreenBuffer(int width, int height);
    void CleanupOffscreenBuffer();
    void ClearOffscreenBuffer();
    void RebuildOffscreenBuffer();

    // Helper methods - File I/O
    void SaveToFile();
    void LoadFromFile();

    // Helper methods - Canvas
    void ClearCanvas();

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
    void SetMouseCursor(HCURSOR cursor);

    // Utility methods
    HWND GetHandle() const { return m_hwnd; }
    DrawingMode GetCurrentDrawingMode() const { return m_currentDrawingMode; }
    COLORREF GetCurrentColor() const { return m_currentColor; }
};

// ========================================
// GLOBAL HELPER FUNCTIONS
// ========================================

// Create graphics window
GraphicsWindow* CreateGraphicsWindow(HINSTANCE hInstance, int nCmdShow, const std::string& title);

// Run graphics program
int RunGraphicsProgram(GraphicsWindow* window);

#endif // WINDOW_H
