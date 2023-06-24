cmake_minimum_required(VERSION 3.22)
project(GRenderer)

set(CMAKE_CXX_STANDARD 17)

# 'lib' is the folder with Google Test sources
add_subdirectory(deps/google_test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(./)
include_directories(deps/spdlog/include)
add_subdirectory(test/)

add_executable(GRenderer main.cpp Tuple3.h Tuple2.h Vector2.h Vector3.h)
target_compile_definitions(GRenderer PRIVATE GRENDER_DEBUG_BUILD)