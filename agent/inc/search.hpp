/*
 * File:   search.hpp
 * Author: Xu Xinyuan
 * Date:   2018-07-05
 */

#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "maze.hpp"
#include "xxylist.hpp"

#include <cmath>
using namespace maze;
namespace solution
{
    typedef enum{
        SOLVED = 0,
        ERROR,
        DEAD
    }result_t;

    class SearchAlgorithm
    {
        Listxxy stack;
        Listxxy open_list;
        Listxxy close_list;
        int home[2];
        int dest[2];
        int rowlimit;
        int collimit;
        int g_min;
        Maze* maze;
        //functions
        void GetCellAvailiable(Node*, bool*,int,int);
        bool GoalTest(Node*);
        dir_t GreedyChoice(Node*,bool*);
        float HeuristicCost(Node*,dir_t);
        float HeuristicCost(Node*);
        float HeuristicCost(int,int);
        dir_t IntToDir(int);
    public:
        // Set method
        SearchAlgorithm();
        void SetHome(int,int);
        void SetDest(int,int);
        void SetMaze(Maze*);
        result_t Search();
        result_t GreedySearch(int);
        result_t AStarSearch();
        void EvaluateNode(Node*,int);
        void Display();
        
    };

    // out-of-class function
};

#endif 
