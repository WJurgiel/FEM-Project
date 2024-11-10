cmake_minimum_required(VERSION 3.29)

project(file_handler)

set(SOURCE_FILES FileHandler.cpp)
set(HEADER_FILES FileHandler.h)

add_library(file_handler STATIC ${SOURCE_FILES} ${HEADER_FILES})