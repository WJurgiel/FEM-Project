cmake_minimum_required(VERSION 3.29)

project(time-measurement)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES timer.h)
set(SOURCE_FILES timer.cpp)

add_library(timer_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})