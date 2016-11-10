cmake_minimum_required(VERSION 3.6)
project(A_star_algorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ShortestPath.cpp)
add_executable(A_star_algorithm ${SOURCE_FILES})