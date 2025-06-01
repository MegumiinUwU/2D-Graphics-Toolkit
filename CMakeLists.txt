cmake_minimum_required(VERSION 3.31)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

add_executable(2D-Graphics-Project
        demo.cpp
        BresenhamLine.cpp
        DDALine.cpp
        DirectCircle.cpp
        IterativePolarCircle.cpp
        MidpointCircle.cpp
        ModifiedMidpointCircle.cpp
        ParametricLine.cpp
        PolarCircle.cpp
        Square.cpp
        Rectangle.cpp
        HermiteAlgorithms.cpp
)
