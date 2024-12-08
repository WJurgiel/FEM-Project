cmake_minimum_required(VERSION 3.29)
project(FEM)

set(CMAKE_CXX_STANDARD 20)

include_directories(Includes)
add_subdirectory(Source)

add_executable(FEM main.cpp
        Source/Node.cpp
        Source/GlobalData.cpp
        Source/Element.cpp
        Source/Grid.cpp
        Source/ElemUniv.cpp
        Source/Jacobian.cpp
        Source/IntegrationPoints.cpp
        Source/GlobalSystemEquation.cpp
)

add_subdirectory(Google_Tests)

include_directories(lib/time-measurement lib/file-handler)
add_subdirectory(lib/time-measurement)
add_subdirectory(lib/file-handler)

target_link_libraries(FEM timer_lib file_handler)