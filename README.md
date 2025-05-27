# 2D-Graphics-Project

# 2D Drawing Program Project

This document outlines the tasks required to implement a 2D drawing program in C++. Use the checkboxes below to track your progress through the development phases.

---

## Phase 1: Core Functionality & Window Setup 🖱️

This phase focuses on setting up the basic window and user interaction.

- [x] **Task 1: Create Window & Set Background**
    - Create a window for your drawing program.
    - Implement a function to set the background color to white.
    - *Integration:* This forms the canvas for all subsequent drawing operations.

- [x] **Task 2: Customize Mouse Cursor**
    - Research and implement a method to change the default mouse cursor shape.

- [ ] **Task 3: Implement Mouse-Only Interaction**
    - Set up event handling for mouse clicks and movement.
    - Ensure all primary user actions rely on mouse inputs.

- [ ] **Task 4: Console & Window Integration (Optional)**
    - Investigate having both a graphical window and a console running.
    - Use the console for debugging, status updates, etc.

---

## Phase 2: Menus & Basic Drawing Management 🎨

This phase focuses on creating the user interface for selecting options.

- [ ] **Task 5: Implement Drop-Down Menus**
    - Design and implement a menu bar with drop-down lists.
    - Populate menus with placeholders (File, Shapes, Colors, etc.).
    - *Integration:* This will be the primary way users access features.

- [ ] **Task 6: Color Selection Menu**
    - Add a "Colors" menu item.
    - Implement a sub-menu/dialog for choosing drawing colors.
    - Store the selected color.
    - *Integration:* The chosen color will be used by all drawing functions.

- [ ] **Task 7: Implement Clear Screen Functionality**
    - Add a "Clear" or "New" option.
    - Implement a function to erase all shapes and reset the window.
    - *Integration:* Provides a way to start a new drawing.

- [ ] **Task 8: Implement Save Functionality**
    - Add a "Save" option.
    - Design a file format to store shape data.
    - Implement code to write data to a file.
    - *Integration:* Allows users to preserve their work.

- [ ] **Task 9: Implement Load Functionality**
    - Add a "Load" option.
    - Implement code to read the save file format.
    - Re-draw shapes based on loaded data.
    - *Integration:* Enables users to continue working on previous drawings.

---

## Phase 3: Line & Circle Drawing Algorithms ✍️

This phase focuses on implementing the fundamental shape drawing algorithms.

- [x] **Task 10: Implement DDA Line Algorithm**
    - Create a function to draw a line using the DDA algorithm.

- [x] **Task 11: Implement Midpoint Line Algorithm**
    - Create a function to draw a line using the Midpoint line algorithm.

- [x] **Task 12: Implement Parametric Line Algorithm**
    - Create a function to draw a line using a parametric equation.

- [x] **Task 13: Implement Direct Circle Algorithm**
    - Create a function to draw a circle using the direct method.

- [x] **Task 14: Implement Polar Circle Algorithm**
    - Create a function to draw a circle using polar coordinates.

- [x] **Task 15: Implement Iterative Polar Circle Algorithm**
    - Create a function to draw a circle using an iterative polar approach.

- [x] **Task 16: Implement Midpoint Circle Algorithm**
    - Create a function to draw a circle using the Midpoint circle algorithm.

- [x] **Task 17: Implement Modified Midpoint Circle Algorithm**
    - Create a function to draw a circle using a modified Midpoint circle algorithm.

- [ ] **Task 18: Implement Ellipse Direct Algorithm**
    - Create a function to draw an ellipse using the direct method.

- [ ] **Task 19: Implement Ellipse Polar Algorithm**
    - Create a function to draw an ellipse using polar coordinates.

- [ ] **Task 20: Implement Ellipse Midpoint Algorithm**
    - Create a function to draw an ellipse using the Midpoint ellipse algorithm.

---

## Phase 4: Filling Algorithms ⬛

This phase focuses on implementing various shape-filling techniques.

- [ ] **Task 21: Implement Circle Filling with Lines**
    - Allow user to select a quarter of a circle.

- [ ] **Task 22: Implement Circle Filling with Circles**
    - Allow user to select a quarter of a circle.

- [ ] **Task 23: Implement Square Filling with Hermite Curve (Vertical)**
    - Allow user to draw a square.
    - Fill the square with vertical Hermite curves.

- [ ] **Task 24: Implement Rectangle Filling with Bezier Curve (Horizontal)**
    - Allow user to draw a rectangle.
    - Fill the rectangle with horizontal Bezier curves.

- [ ] **Task 25: Implement Convex Filling Algorithm**
    - Implement a scan-line filling algorithm for convex polygons.

- [ ] **Task 26: Implement Non-Convex Filling Algorithm**
    - Implement a scan-line filling algorithm for non-convex polygons.

- [ ] **Task 27: Implement Recursive Flood Fill**
    - Implement a recursive flood fill algorithm.

- [ ] **Task 28: Implement Non-Recursive Flood Fill**
    - Implement a non-recursive flood fill algorithm (stack/queue).

---

## Phase 5: Curves & Clipping ✂️

This phase focuses on more advanced drawing and manipulation techniques.

- [ ] **Task 29: Implement Cardinal Spline Curve**
    - Allow user to input control points.
    - Draw a Cardinal spline curve through these points.
    - *Integration:* Adds smooth curve drawing capability.

- [ ] **Task 30: Implement Point Clipping (Rectangle Window)**
    - Allow user to define a rectangular clipping window.
    - Determine if a point is inside or outside the window.
    - *Integration:* The basic building block for line and polygon clipping.

- [ ] **Task 31: Implement Line Clipping (Rectangle Window)**
    - Implement a line clipping algorithm against a rectangle.

- [ ] **Task 32: Implement Polygon Clipping (Rectangle Window)**
    - Implement a polygon clipping algorithm against a rectangle.

- [ ] **Task 33: Implement Point Clipping (Square Window)**
    - Adapt point clipping for a square window.

- [ ] **Task 34: Implement Line Clipping (Square Window)**
    - Adapt line clipping for a square window.

- [ ] **Task 35: Implement Point Clipping (Circle Window)**
    - Implement point clipping against a circular window.

- [ ] **Task 36: Implement Line Clipping (Circle Window)**
    - Implement line clipping against a circular window (involves intersections).

---

