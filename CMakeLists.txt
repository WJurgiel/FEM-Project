cmake_minimum_required(VERSION 3.29)
project(FEM)

set(CMAKE_CXX_STANDARD 20)

add_executable(FEM main.cpp
        Source/Node.cpp
        Includes/Node.h
        Includes/Includes.h
        Source/GlobalData.cpp
        Includes/GlobalData.h
        Source/Element.cpp
        Includes/Element.h
        Source/Grid.cpp
        Includes/Grid.h
        Source/ElemUniv.cpp
        Includes/ElemUniv.h)
