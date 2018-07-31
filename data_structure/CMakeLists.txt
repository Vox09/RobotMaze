PROJECT(Maze CXX)
cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11)  
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file(GLOB SOURCES "src/*.cpp")
INCLUDE_DIRECTORIES(inc)
ADD_LIBRARY(maze ${SOURCES})
