cmake_minimum_required(VERSION 3.6)
project(Maze_and_Algorithm_Work)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    "Algorithm Work/.cproject"
    "Algorithm Work/.project")

add_executable(Maze_and_Algorithm_Work ${SOURCE_FILES})