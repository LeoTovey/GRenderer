cmake_minimum_required(VERSION 3.22)
project(GRenderer)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 CONFIG REQUIRED)
add_executable(GRenderer main.cpp)
target_link_libraries(GRenderer PRIVATE Eigen3::Eigen)