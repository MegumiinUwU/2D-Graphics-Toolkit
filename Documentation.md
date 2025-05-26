# GraphicsWindow Framework Documentation

## Overview

The `GraphicsWindow.h` framework is a complete Windows API-based 2D graphics system designed for implementing custom drawing algorithms. It provides a clean separation between UI management and drawing algorithms, making it easy to focus on implementing mathematical drawing functions without worrying about window management, menus, or mouse handling.

## Architecture Overview

```
┌─────────────────────────────────────┐
│          GraphicsWindow.h           │
├─────────────────────────────────────┤
│  ┌─────────────────────────────────┐ │
│  │     Window Management           │ │
│  │  • Window creation & events     │ │
│  │  • Menu system                  │ │
│  │  • Mouse/keyboard handling      │ │
│  └─────────────────────────────────┘ │
│  ┌─────────────────────────────────┐ │
│  │     Shape Management            │ │
│  │  • Shape storage & persistence  │ │
│  │  • Drawing mode switching       │ │
│  │  • Color & style management     │ │
│  └─────────────────────────────────┘ │
│  ┌─────────────────────────────────┐ │
│  │   Drawing Algorithms (Empty)    │ │
│  │  • Line algorithms              │ │
│  │  • Circle/Ellipse algorithms    │ │
│  │  • Filling algorithms           │ │
│  │  • Clipping algorithms          │ │
│  └─────────────────────────────────┘ │
└─────────────────────────────────────┘
```

## File Structure Breakdown

### 1. Constants and Definitions (Lines 10-42)

```cpp
// Window dimensions
#define DEFAULT_WINDOW_WIDTH  1024
#define DEFAULT_WINDOW_HEIGHT 768

// Menu IDs for various operations
#define MENU_FILE_NEW         1001
// ... more menu constants
```

**Purpose**: Defines window size and menu item identifiers used throughout the framework.

**How to Extend**: Add new menu IDs when implementing additional features:
```cpp
#define MENU_SHAPES_BEZIER    2005  // For Bezier curves
#define MENU_FILL_GRADIENT    4004  // For gradient fills
```

### 2. Enumerations (Lines 44-68)

#### DrawingMode Enum
```cpp
enum class DrawingMode {
    LINE_DDA,                    // ✅ Ready for implementation
    LINE_MIDPOINT,               // 🔄 Ready for implementation  
    LINE_PARAMETRIC,             // 🔄 Ready for implementation
    CIRCLE_DIRECT,               // 🔄 Ready for implementation
    // ... more modes
};
```

**Purpose**: Defines all available drawing algorithms. Each mode corresponds to a specific mathematical implementation.

**How to Add New Modes**:
1. Add enum value: `BEZIER_CUBIC`
2. Add menu item in `InitializeMenus()`
3. Add case in `HandleMenuCommand()`
4. Add case in `HandleMouseClick()`
5. Add case in `RedrawAll()`
6. Implement algorithm in `DrawingAlgorithms` class

#### FillMode Enum
```cpp
enum class FillMode {
    NONE,
    SOLID,
    FLOOD_FILL_RECURSIVE,
    FLOOD_FILL_NON_RECURSIVE,
    SCANLINE_CONVEX,
    SCANLINE_NON_CONVEX
};
```

**Purpose**: Defines filling algorithms for closed shapes.

### 3. Data Structures (Lines 70-85)

#### Point Structure
```cpp
struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};
```

**Purpose**: Represents 2D coordinates. Used throughout the system for storing click points, shape vertices, etc.

#### Shape Structure
```cpp
struct Shape {
    DrawingMode mode;           // Which algorithm was used
    COLORREF color;            // Shape color
    FillMode fillMode;         // How to fill (if applicable)
    std::vector<Point> points; // All points defining the shape
    int thickness;             // Line thickness
};
```

**Purpose**: Stores complete information about a drawn shape for persistence and redrawing.

**How Shapes Are Used**:
- **Line**: 2 points (start, end)
- **Circle**: 2 points (center, radius point)
- **Polygon**: N points (vertices)
- **Ellipse**: 3 points (center, width point, height point)

### 4. GraphicsWindow Class (Lines 87-149)

This is the main class that manages the entire graphics system.

#### Private Members (Lines 88-126)

```cpp
// Window handles and identifiers
HWND m_hwnd;                    // Window handle
HINSTANCE m_hInstance;          // Application instance
HDC m_hdc;                      // Device context

// Drawing state
DrawingMode m_currentDrawingMode;  // Current active algorithm
FillMode m_currentFillMode;        // Current fill method
COLORREF m_currentColor;           // Current drawing color
COLORREF m_backgroundColor;        // Canvas background color
int m_lineThickness;               // Line width

// Mouse interaction state
bool m_isDrawing;                  // Whether user is in middle of drawing
std::vector<Point> m_currentPoints; // Points clicked so far
Point m_lastMousePos;              // Last mouse position (for preview)

// Shape storage
std::vector<Shape> m_shapes;       // All completed shapes

// Drawing tools
HPEN m_currentPen;                 // Current pen for drawing
HBRUSH m_currentBrush;             // Current brush for filling
HBRUSH m_backgroundBrush;          // Background brush

// Menu handle
HMENU m_hMenuBar;                  // Main menu bar
```

#### Key Methods Explained

##### Constructor (Lines 159-175)
Initializes all member variables to safe defaults. Sets up initial drawing state.

##### Initialize() (Lines 184-222)
**Most Important Method** - Sets up the entire Windows application:
1. Registers window class with custom cursor (`IDC_CROSS`)
2. Creates main window (1024x768)
3. Initializes menus
4. Creates drawing tools (pens, brushes)
5. Shows window

##### InitializeMenus() (Lines 225-255)
Creates the complete menu system:
- **File Menu**: New, Save, Load, Exit
- **Shapes Menu**: All drawing algorithms
- **Colors Menu**: Color selection
- **Tools Menu**: Clear, utilities

**How to Add New Menus**:
```cpp
// In InitializeMenus(), add new menu
HMENU hTransformMenu = CreatePopupMenu();
AppendMenu(hTransformMenu, MF_STRING, MENU_TRANSFORM_ROTATE, "Rotate");
AppendMenu(hTransformMenu, MF_STRING, MENU_TRANSFORM_SCALE, "Scale");
AppendMenu(m_hMenuBar, MF_POPUP, (UINT_PTR)hTransformMenu, "Transform");
```

##### HandleMouseClick() (Lines 360-430)
**Core Drawing Logic** - Processes mouse clicks based on current drawing mode:

```cpp
switch (m_currentDrawingMode) {
    case DrawingMode::LINE_DDA:
        // Two-click process: start point, end point
        if (!m_isDrawing) {
            // First click - store start point
            m_currentPoints.push_back(newPoint);
            m_isDrawing = true;
        } else {
            // Second click - complete line and save shape
            m_currentPoints.push_back(newPoint);
            // Create Shape object and add to m_shapes
            m_isDrawing = false;
        }
        break;
    
    case DrawingMode::POLYGON:
        // Multi-click process: keep adding points until right-click
        m_currentPoints.push_back(newPoint);
        break;
}
```

**How Drawing Works**:
1. User selects drawing mode from menu
2. User clicks to add points
3. Framework stores points in `m_currentPoints`
4. When shape is complete, it's saved to `m_shapes` vector
5. Window is refreshed to show the new shape

##### RedrawAll() (Lines 470-550)
**Critical Rendering Method** - Redraws the entire canvas:

```cpp
void GraphicsWindow::RedrawAll() {
    HDC hdc = GetDC(m_hwnd);
    
    // 1. Draw all completed shapes from m_shapes vector
    for (const auto& shape : m_shapes) {
        switch (shape.mode) {
            case DrawingMode::LINE_DDA:
                // Call your DDA implementation
                DrawingAlgorithms::DrawLineDDA(hdc, 
                    shape.points[0].x, shape.points[0].y,
                    shape.points[1].x, shape.points[1].y,
                    shape.color);
                break;
            // ... more cases for each algorithm
        }
    }
    
    // 2. Draw preview of current shape being created
    if (m_isDrawing && !m_currentPoints.empty()) {
        // Show live preview as user draws
    }
    
    ReleaseDC(m_hwnd, hdc);
}
```

**This is where your algorithms get called!** Each saved shape is redrawn using its stored algorithm.

### 5. DrawingAlgorithms Class (Lines 589-630)

This is where you implement all drawing algorithms. Currently contains only declarations:

```cpp
class DrawingAlgorithms {
public:
    // Line drawing algorithms - IMPLEMENT THESE
    static void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);
    static void DrawLineMidpoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color);
    
    // Circle drawing algorithms - IMPLEMENT THESE
    static void DrawCircleMidpoint(HDC hdc, int centerX, int centerY, int radius, COLORREF color);
    
    // Helper functions - IMPLEMENT THESE
    static void SetPixel(HDC hdc, int x, int y, COLORREF color);
};
```

## How to Implement Drawing Algorithms

### Step 1: Implement SetPixel Helper

```cpp
// In DrawingAlgorithms class
static void SetPixel(HDC hdc, int x, int y, COLORREF color) {
    ::SetPixel(hdc, x, y, color);  // Call Windows API SetPixel
}
```

### Step 2: Implement Line Algorithm (Example: DDA)

```cpp
static void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy));
    
    if (steps == 0) {
        SetPixel(hdc, x1, y1, color);
        return;
    }
    
    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;
    
    float x = (float)x1;
    float y = (float)y1;
    
    for (int i = 0; i <= steps; i++) {
        SetPixel(hdc, (int)(x + 0.5f), (int)(y + 0.5f), color);
        x += xIncrement;
        y += yIncrement;
    }
}
```

### Step 3: Implement Circle Algorithm (Example: Midpoint)

```cpp
static void DrawCircleMidpoint(HDC hdc, int centerX, int centerY, int radius, COLORREF color) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;
    
    DrawCirclePoints(hdc, centerX, centerY, x, y, color);
    
    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        DrawCirclePoints(hdc, centerX, centerY, x, y, color);
    }
}

static void DrawCirclePoints(HDC hdc, int centerX, int centerY, int x, int y, COLORREF color) {
    SetPixel(hdc, centerX + x, centerY + y, color);
    SetPixel(hdc, centerX - x, centerY + y, color);
    SetPixel(hdc, centerX + x, centerY - y, color);
    SetPixel(hdc, centerX - x, centerY - y, color);
    SetPixel(hdc, centerX + y, centerY + x, color);
    SetPixel(hdc, centerX - y, centerY + x, color);
    SetPixel(hdc, centerX + y, centerY - x, color);
    SetPixel(hdc, centerX - y, centerY - x, color);
}
```

## How to Add New Drawing Algorithms

### Example: Adding Bresenham Line Algorithm

1. **Add to DrawingMode enum**:
```cpp
enum class DrawingMode {
    LINE_DDA,
    LINE_BRESENHAM,  // ← Add this
    // ... existing modes
};
```

2. **Add menu item**:
```cpp
// In InitializeMenus()
AppendMenu(hShapesMenu, MF_STRING, MENU_SHAPES_LINE_BRESENHAM, "Line (Bresenham)");
```

3. **Add menu constant**:
```cpp
#define MENU_SHAPES_LINE_BRESENHAM 2005
```

4. **Add menu handler**:
```cpp
// In HandleMenuCommand()
case MENU_SHAPES_LINE_BRESENHAM:
    SetDrawingMode(DrawingMode::LINE_BRESENHAM);
    break;
```

5. **Add to RedrawAll()**:
```cpp
// In RedrawAll()
case DrawingMode::LINE_BRESENHAM:
    if (shape.points.size() >= 2) {
        DrawingAlgorithms::DrawLineBresenham(hdc, 
            shape.points[0].x, shape.points[0].y,
            shape.points[1].x, shape.points[1].y,
            shape.color);
    }
    break;
```

6. **Add to HandleMouseClick()** (if needed):
```cpp
// In HandleMouseClick()
case DrawingMode::LINE_BRESENHAM:
    // Same logic as LINE_DDA since both are 2-point lines
    // ... copy LINE_DDA case
    break;
```

7. **Implement the algorithm**:
```cpp
// In DrawingAlgorithms class
static void DrawLineBresenham(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    // Your Bresenham implementation here
}
```

## Data Flow Diagram

```
User Clicks Menu Item
        ↓
HandleMenuCommand()
        ↓
SetDrawingMode()
        ↓
User Clicks on Canvas
        ↓
HandleMouseClick()
        ↓
Points stored in m_currentPoints
        ↓
Shape completed? → Create Shape object → Add to m_shapes vector
        ↓
InvalidateRect() called
        ↓
Windows sends WM_PAINT
        ↓
RedrawAll() called
        ↓
Your algorithm draws the shape
```

## Key Extension Points

### 1. For Drawing Algorithms
- **Location**: `DrawingAlgorithms` class methods
- **What to implement**: Mathematical drawing functions
- **Input**: HDC (device context), coordinates, color
- **Output**: Pixels drawn on screen

### 2. For Filling Algorithms
- **Location**: `DrawingAlgorithms` class filling methods
- **What to implement**: Area filling functions
- **Input**: HDC, seed point or polygon vertices, fill color
- **Output**: Filled regions

### 3. For New Shape Types
- **Locations to modify**:
  - `DrawingMode` enum
  - `InitializeMenus()`
  - `HandleMenuCommand()`
  - `HandleMouseClick()` (mouse interaction logic)
  - `RedrawAll()` (rendering logic)
  - `DrawingAlgorithms` class (implementation)

### 4. For Clipping Algorithms
- **Location**: `GraphicsUtils` namespace
- **What to implement**: Line/polygon clipping functions
- **Integration**: Call before drawing in `RedrawAll()`

## Common Implementation Patterns

### Pattern 1: Two-Point Shapes (Lines, Circles)
```cpp
case DrawingMode::YOUR_ALGORITHM:
{
    if (!m_isDrawing) {
        // First click - start shape
        m_currentPoints.clear();
        m_currentPoints.push_back(newPoint);
        m_isDrawing = true;
    } else {
        // Second click - complete shape
        m_currentPoints.push_back(newPoint);
        
        Shape shape;
        shape.mode = m_currentDrawingMode;
        shape.color = m_currentColor;
        shape.points = m_currentPoints;
        shape.thickness = m_lineThickness;
        m_shapes.push_back(shape);
        
        m_isDrawing = false;
        m_currentPoints.clear();
        InvalidateRect(m_hwnd, NULL, TRUE);
    }
}
```

### Pattern 2: Multi-Point Shapes (Polygons, Splines)
```cpp
case DrawingMode::YOUR_POLYGON:
{
    if (!m_isDrawing) {
        m_currentPoints.clear();
        m_isDrawing = true;
    }
    m_currentPoints.push_back(newPoint);
    // Shape completed by right-click (handled elsewhere)
    InvalidateRect(m_hwnd, NULL, TRUE);
}
```

## Debugging Tips

1. **Add console output**: Use `AllocConsole()` and `printf()` for debugging
2. **Check point storage**: Verify `m_currentPoints` contains expected values
3. **Test algorithms separately**: Implement simple test cases first
4. **Use different colors**: Help distinguish between different algorithm outputs
5. **Add breakpoints**: In `HandleMouseClick()` and `RedrawAll()` to trace execution

## Best Practices

1. **Keep algorithms pure**: Don't modify global state in drawing functions
2. **Handle edge cases**: Zero-length lines, negative radii, etc.
3. **Use consistent naming**: Follow existing naming conventions
4. **Document algorithms**: Add comments explaining the mathematical approach
5. **Test incrementally**: Implement one algorithm at a time
6. **Validate input**: Check for valid coordinates and parameters

This framework provides a complete foundation for implementing any 2D graphics algorithm while handling all the Windows API complexity for you. Focus on the mathematics and let the framework handle the UI!
