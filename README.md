# 2D Graphics Toolkit

A comprehensive Windows-based 2D graphics application implementing various computer graphics algorithms for drawing lines, circles, ellipses, polygons, curves, and filling shapes. Built using the Windows API (Win32) and C++.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)

## 📋 Table of Contents

- [Features](#features)
- [Implemented Algorithms](#implemented-algorithms)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [Extending the Project](#extending-the-project)
- [License](#license)

<a id="features"></a>
## ✨ Features

- **Interactive Drawing Interface**: Point-and-click interface for drawing various shapes
- **Multiple Algorithm Implementations**: Each shape type has multiple algorithm implementations
- **Real-time Preview**: See shapes as you draw them
- **Color Selection**: Choose from multiple colors for drawing
- **Fill Operations**: Various fill algorithms including flood fill and scanline fill
- **File I/O**: Save and load your drawings
- **Curve Support**: Bezier, Hermite, and Cardinal Spline curves
- **Optimized Rendering**: Double-buffered drawing for smooth performance

<a id="implemented-algorithms"></a>
## 🎨 Implemented Algorithms

### Line Drawing Algorithms
- **DDA (Digital Differential Analyzer)** - Simple incremental line drawing
- **Bresenham's Line Algorithm** - Integer-based efficient line drawing
- **Parametric Line** - Parametric equation-based line drawing
- **Horizontal Line** - Optimized horizontal line drawing

### Circle Drawing Algorithms
- **Direct Circle** - Mathematical circle using direct equation
- **Polar Circle** - Polar coordinate-based circle
- **Iterative Polar Circle** - Optimized polar circle
- **Midpoint Circle (Bresenham)** - Efficient integer-based circle
- **Modified Midpoint Circle** - Enhanced midpoint algorithm

### Ellipse Drawing Algorithms
- **Direct Ellipse** - Direct mathematical ellipse
- **Polar Ellipse** - Polar coordinate ellipse
- **Bresenham's Ellipse (Midpoint)** - Integer-based efficient ellipse

### Polygon Drawing
- **General Polygon** - N-sided polygon with Bresenham lines
- **Rectangle** - Axis-aligned rectangle
- **Square** - Equal-sided rectangle

### Curve Drawing
- **Bezier Curves** - Smooth parametric curves
- **Hermite Curves** - Tangent-based smooth curves
- **Cardinal Splines** - Interpolating spline curves

### Fill Algorithms
- **Circle Fills**:
  - Fill with horizontal lines
  - Quarter circle fill
  - Concentric circles fill
  
- **Polygon Fills**:
  - Convex polygon scanline fill
  - Non-convex polygon scanline fill
  
- **Flood Fill**:
  - Recursive flood fill
  - Non-recursive (iterative) flood fill
  
- **Special Fills**:
  - Fill rectangle with horizontal Bezier curves
  - Fill square with vertical Hermite curves

<a id="project-structure"></a>
## 📁 Project Structure

```
2D-Graphics-Toolkit/
├── include/                      # Header files
│   ├── Bezier.h                 # Bezier curve declarations
│   ├── CardinalSpline.h         # Cardinal spline declarations
│   ├── CircleAlgorithms.h       # Circle drawing algorithms
│   ├── CircleFillAlgorithms.h   # Circle filling algorithms
│   ├── EllipseAlgorithms.h      # Ellipse drawing algorithms
│   ├── FloodFill.h              # Flood fill algorithms
│   ├── GraphicsTypes.h          # Common types and enums
│   ├── Hermite.h                # Hermite curve declarations
│   ├── LineAlgorithms.h         # Line drawing algorithms
│   ├── Point.h                  # Point structure
│   ├── PolygonAlgorithms.h      # Polygon drawing algorithms
│   ├── PolygonFillAlgorithms.h  # Polygon fill algorithms
│   ├── Utils.h                  # Utility functions
│   └── Window.h                 # Main window and graphics framework
│
├── src/                         # Implementation files
│   ├── circle/                  # Circle algorithm implementations
│   │   ├── DirectCircle.cpp
│   │   ├── IterativePolarCircle.cpp
│   │   ├── MidpointCircle.cpp
│   │   ├── ModifiedMidpointCircle.cpp
│   │   └── PolarCircle.cpp
│   │
│   ├── circle fill/             # Circle fill implementations
│   │   ├── FillCircleWithCircles.cpp
│   │   ├── FillCircleWithLines.cpp
│   │   └── FillQuarterCircle.cpp
│   │
│   ├── curve/                   # Curve implementations
│   │   ├── Bezier.cpp
│   │   ├── CardinalSpline.cpp
│   │   └── Hermite.cpp
│   │
│   ├── elipse/                  # Ellipse implementations
│   │   ├── BresenhamElipse.cpp
│   │   ├── DirectElipse.cpp
│   │   └── PolarElipse.cpp
│   │
│   ├── flood fill/              # Flood fill implementations
│   │   ├── NonRecursiveFloodFIll.cpp
│   │   └── RecursiveFloodFill.cpp
│   │
│   ├── line/                    # Line algorithm implementations
│   │   ├── BresenhamLine.cpp
│   │   ├── BresenhamPolygonLine.cpp
│   │   ├── DDALine.cpp
│   │   ├── HorizontalLine.cpp
│   │   └── ParametricLine.cpp
│   │
│   ├── polygon/                 # Polygon implementations
│   │   ├── Polygon.cpp
│   │   ├── Rectangle.cpp
│   │   └── Square.cpp
│   │
│   ├── polygon fill/            # Polygon fill implementations
│   │   ├── ConvexFIll.cpp
│   │   ├── FillRectangleWithHorizontalBezier.cpp
│   │   ├── FillSquareWithVerticalHermite.cpp
│   │   └── NonConvexFill.cpp
│   │
│   └── window/                  # Window management implementations
│       ├── Buffer.cpp           # Offscreen buffer management
│       ├── Draw.cpp             # Drawing coordination
│       ├── File.cpp             # File I/O operations
│       ├── Menu.cpp             # Menu handling
│       ├── Mouse.cpp            # Mouse event handling
│       └── Window.cpp           # Main window implementation
│
├── docs/                        # Documentation
│   └── Documentation.md         # Detailed framework documentation
│
├── cmake-build-debug/           # CMake build files (generated)
├── CMakeLists.txt              # CMake build configuration
├── main.cpp                    # Application entry point
├── LICENSE                     # License file
└── README.md                   # This file
```

<a id="requirements"></a>
## 💻 Requirements

### Software Requirements
- **Operating System**: Windows 7 or later
- **Compiler**: 
  - MSVC (Visual Studio 2017 or later)
  - MinGW-w64 (GCC 7.0 or later)
  - Clang for Windows
- **Build System**: CMake 3.31 or later
- **IDE** (Optional but recommended):
  - CLion
  - Visual Studio
  - VS Code with C++ extensions

### Libraries
- Windows API (Win32) - Pre-installed with Windows SDK
- Standard C++ Library (C++17)

<a id="building-the-project"></a>
## 🔨 Building the Project

### Using CMake (Command Line)

1. **Clone the repository**:
```bash
git clone https://github.com/MegumiinUwU/2D-Graphics-Project.git
cd 2D-Graphics-Toolkit
```

2. **Create build directory**:
```bash
mkdir build
cd build
```

3. **Generate build files**:
```bash
cmake ..
```

4. **Build the project**:
```bash
cmake --build . --config Release
```

5. **Run the executable**:
```bash
# From the build directory
cd Release
./2D-Graphics-Toolkit.exe

# Or from the build directory directly
./Release/2D-Graphics-Toolkit.exe
```

### Using CLion

1. Open CLion
2. Select **File → Open** and choose the project directory
3. CLion will automatically detect CMakeLists.txt
4. Click the **Build** button (hammer icon) or press `Ctrl+F9`
5. Click **Run** (play icon) or press `Shift+F10`

### Using Visual Studio

1. Open Visual Studio
2. Select **File → Open → CMake**
3. Choose the `CMakeLists.txt` file
4. Wait for CMake to configure
5. Select **Build → Build All** or press `Ctrl+Shift+B`
6. Run with **Debug → Start Without Debugging** or press `Ctrl+F5`

<a id="usage"></a>
## 🎮 Usage

### Basic Drawing

1. **Launch the application** - A window will open with a menu bar
2. **Select a drawing algorithm** from the **Shapes** menu:
   - Choose from Lines, Circles, Ellipses, Polygons, or Curves
3. **Click on the canvas** to define points:
   - **Lines/Circles/Ellipses**: Click twice (start and end points)
   - **Polygons**: Click multiple times, right-click to finish
   - **Rectangles**: Click and drag
4. **The shape appears** using the selected algorithm

### Selecting Colors

1. Open the **Colors** menu
2. Select from:
   - Black
   - Red
   - Green
   - Blue
   - White

### Filling Shapes

1. Draw a closed shape (circle, polygon, etc.)
2. Select a fill mode from the **Fill** menu
3. Click inside the shape to fill it

### File Operations

- **New Canvas**: File → New (clears current drawing)
- **Save Drawing**: File → Save (saves to .bin file)
- **Load Drawing**: File → Load (loads from .bin file)

### Shape-Specific Instructions

#### Drawing a Line
1. Shapes → Lines → Choose algorithm (DDA, Bresenham, or Parametric)
2. Click for start point
3. Click for end point

#### Drawing a Circle
1. Shapes → Circles → Choose algorithm
2. Click for center point
3. Click to define radius

#### Drawing an Ellipse
1. Shapes → Ellipses → Choose algorithm
2. Click for center point
3. Click to define semi-major axis length

#### Drawing a Polygon
1. Shapes → Polygon
2. Click to add vertices (as many as needed)
3. Right-click to close polygon

#### Drawing Curves
1. Shapes → Curves → Choose type (Bezier, Hermite, Cardinal)
2. Click to add control points
3. Right-click when done


<a id="extending-the-project"></a>
## 🔧 Extending the Project

### Adding a New Drawing Algorithm

1. **Declare** function in appropriate header file (e.g., `LineAlgorithms.h`)
2. **Implement** algorithm in corresponding source file
3. **Add** menu constant in `GraphicsTypes.h`
4. **Update** `DrawingMode` enum
5. **Add** menu item in `Window.cpp` → `InitializeMenus()`
6. **Handle** menu command in `HandleMenuCommand()`
7. **Add** drawing case in `RedrawAll()` or `DrawShapeToBuffer()`

### Adding a New Shape Type

1. Follow steps for adding algorithm above
2. **Implement** mouse handling logic in `HandleMouseClick()`
3. **Add** preview drawing in `HandleMouseMove()` if needed


<a id="license"></a>
## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

