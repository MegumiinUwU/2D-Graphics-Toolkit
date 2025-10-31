#include "../../include/Window.h"

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
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillNonRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillNonRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillNonRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillNonRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
                    } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                        COLORREF bgColor = GetPixel(hdc, shape.points[0].x, shape.points[0].y);
                        FloodFillNonRecursive(hdc, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
                    break;

                case DrawingMode::SQUARE:
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
                break;

            case DrawingMode::SQUARE:
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
                    LineTo(hdc, centerX - halfSize, centerY - halfSize);                    
                    SelectObject(hdc, oldPen);
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

            case DrawingMode::CURVE_CARDINAL:
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
            } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
            } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillNonRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
            } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
            } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillNonRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
            } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
            } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillNonRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
            } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
            } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillNonRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
            } else if (shape.fillMode == FillMode::FLOOD_FILL_RECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
            } else if (shape.fillMode == FillMode::FLOOD_FILL_NONRECURSIVE_POLYGON) {
                COLORREF bgColor = GetPixel(m_offscreenDC, shape.points[0].x, shape.points[0].y);
                FloodFillNonRecursive(m_offscreenDC, shape.points[0].x, shape.points[0].y, shape.color, bgColor);
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
            break;

        case DrawingMode::SQUARE:
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
            break;

        case DrawingMode::CURVE_CARDINAL:
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
