cmake_minimum_required(VERSION 3.31)
project(2D-Graphics-Toolkit)

set(CMAKE_CXX_STANDARD 17)

add_executable(2D-Graphics-Toolkit
        main.cpp
        src/line/BresenhamLine.cpp
        src/line/DDALine.cpp
        src/circle/DirectCircle.cpp
        src/circle/IterativePolarCircle.cpp
        src/circle/MidpointCircle.cpp
        src/circle/ModifiedMidpointCircle.cpp
        src/line/ParametricLine.cpp
        src/circle/PolarCircle.cpp
        src/polygon/Square.cpp
        src/polygon/Rectangle.cpp
        src/curve/Hermite.cpp
        src/curve/Bezier.cpp
        src/elipse/DirectElipse.cpp
        src/elipse/PolarElipse.cpp
        src/elipse/BresenhamElipse.cpp
        src/curve/CardinalSpline.cpp
        include/CardinalSpline.h
        src/line/HorizontalLine.cpp
        "src/circle fill/FillCircleWithLines.cpp"
        "src/circle fill/FillQuarterCircle.cpp"
        "src/circle fill/FillCircleWithCircles.cpp"
        include/FloodFill.h
        "src/flood fill/RecursiveFloodFill.cpp"
        "src/flood fill/NonRecursiveFloodFIll.cpp"
        include/PolygonAlgorithms.h
        src/polygon/Polygon.cpp
        include/Point.h
        src/line/BresenhamPolygonLine.cpp
        "src/polygon fill/ConvexFIll.cpp"
        "src/polygon fill/NonConvexFill.cpp"
        "src/polygon fill/FillRectangleWithHorizontalBezier.cpp"
        "src/polygon fill/FillSquareWithVerticalHermite.cpp"
        src/window/Window.cpp
        src/window/Menu.cpp
        src/window/Mouse.cpp
        src/window/Draw.cpp
        src/window/Buffer.cpp
        src/window/File.cpp
)