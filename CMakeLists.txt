PROJECT(RoboMaze CXX)
cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11)  
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file(GLOB_RECURSE MAZE_SRC "Maze/src/*.cpp")
file(GLOB_RECURSE AGENT_SRC "agent/src/*.cpp")
file(GLOB_RECURSE DATA_STRUCTURE_SRC 
    "data_structure/src/*.cpp")
INCLUDE_DIRECTORIES(Maze/inc)
INCLUDE_DIRECTORIES(agent/inc)
INCLUDE_DIRECTORIES(datastructure/inc)
ADD_EXECUTABLE(main ${MAZE_SRC} ${AGENT_SRC} 
    ${DATA_STRUCTURE_SRC})
