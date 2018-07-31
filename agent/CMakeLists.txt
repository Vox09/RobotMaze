PROJECT(agent CXX)
cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11)  
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file(GLOB SOURCES "src/*.cpp")
INCLUDE_DIRECTORIES(inc)
TARGET_LINK_LIBRARIES(agent maze)
ADD_LIBRARY(agent ${SOURCES})
