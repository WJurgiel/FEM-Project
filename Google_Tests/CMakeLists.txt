project(Google_Tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run OutputTest.cpp)

target_include_directories(Google_Tests_run PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(Google_Tests_run gtest gtest_main)