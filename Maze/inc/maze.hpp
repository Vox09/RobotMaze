/*
* File:   maze.hpp
* Author: Xu Xinyuan
* Date:   2018-05-25
*/
#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <cstdlib>

//#define DISPLAY
#define ADISPLAY
//#define SDISPLAY
//#define BDISPLAY

namespace maze
{
    enum{OUT=-1,UNVISITED, VISITED,DEAD, EXPLORED,SOLVED};
    typedef char dir_t;
	
	class Cell
    {
		int V;
        int place[2];
		bool wall[4];
	public:
        Cell();
        Cell(int);
        // Get method
		int GetV();
        int GetRow();
        int GetCol();
        bool* GetWallState();
        // Set method
		void SetV(int);
        void SetPlace(int,int);
        // Other method
        void Close(dir_t);
        void Open(dir_t);
        bool CellOut(dir_t,int,int);
        bool CellOut(int,int,int);
        bool operator==(Cell*);
	};

	class Maze{
	private:
		int row;
		int col;
		Cell** pc;
        int home[2];
        int dest[2];
        float wallProp;
        std::random_device rd;
        // functions
        int CalWallSum();
        int GetNextCellState(Cell*,dir_t);
        void GetCellUnvisited(Cell*,bool*);
        int RandomChoice(bool*);
		void GenDepth(Cell*);
        void OpenWalls(int);
        Cell GetCell(int,int);
	public:
        //XXYStack<Cell> gStack;
		Maze(int ,int );
		~Maze();
		void Hi();
        // Get method
		int GetRow();
		int GetCol();
        Cell GetEntry();
        Cell GetExit();
        Cell GetNextCell(Cell*,dir_t);
		Cell GetNextCell(Cell*,int);
        // Set method
        void SetEntry(int, int);
        void SetExit(int, int);
        void SetCellExplored(int, int);
		void SetCellSolution(int, int);
        void SetCellDEAD(int, int);
        void SetWallProp(float);
        // Other method
		void ShowStatus();
		void Display();
        void WriteToFile(std::string);
        void LoadFromFile(std::string);
        void Generate();
        dir_t IntToDir(int);
	};
}
#endif
