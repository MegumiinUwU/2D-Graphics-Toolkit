#include "../../include/Window.h"

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
                case DrawingMode::ELLIPSE_POLAR: modeText += "Ellipse (Polar)"; break;
                case DrawingMode::ELLIPSE_MIDPOINT: modeText += "Ellipse (Midpoint)"; break;
                case DrawingMode::POLYGON: modeText += "Polygon"; break;
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
                case FillMode::POLYGON_CONVEX_FILL: fillText += "Convex Polygon"; break;
                case FillMode::POLYGON_NONCONVEX_FILL: fillText += "Non-Convex Polygon"; break;
                case FillMode::FLOOD_FILL_RECURSIVE_POLYGON: fillText += "Flood Fill Recursive"; break;
                case FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON: fillText += "Flood Fill Non-Recursive"; break;
                case FillMode::SQUARE_FILL_HERMITE_VERTICAL: fillText += "Square Hermite Curves"; break;
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
        }
        else if (m_isDrawing && m_currentDrawingMode == DrawingMode::CURVE_CARDINAL && m_currentPoints.size() >= 2) {
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
            break;

        case DrawingMode::SQUARE:
        {
            if (!m_isDrawing) {
                // Start square (center point)
                m_currentPoints.clear();
                m_currentPoints.push_back(newPoint);
                m_isDrawing = true;
            } else {
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
            break;

        case DrawingMode::RECTANGLE:
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

        case DrawingMode::CURVE_CARDINAL:
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
