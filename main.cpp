/*
* File:   main.cpp
* Author: Xu Xinyuan
* Date:   2018-05-25
*/


#include <cstdlib>
#include "maze.hpp"
#include "search.hpp"


int main(int argc, char** argv){
	int num_rows; 
	int num_cols;
    solution::SearchAlgorithm dfs;
	if (argc != 3){
		num_rows = 8; //default size
		num_cols = 8; //default size
   	}
	else{
		num_rows = atoi(argv[1]);
		num_cols = atoi(argv[2]);
	}
	maze::Maze map(num_rows,num_cols);
	map.Hi();
	map.ShowStatus();
    map.SetWallProp(0.25);
    map.Generate();
    map.SetEntry(0,0);
    map.SetExit(num_rows-1,num_cols-1);
    map.Display();
    map.WriteToFile("map/maze.maze");
    dfs.SetMaze(&map);
    dfs.Search();
	dfs.Display();
	return 0;
}
