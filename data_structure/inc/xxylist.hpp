/*
 * File:   xxylist.hpp
 * Author: Xu Xinyuan
 * Date:   2018-08-01
 */
 
#include "maze.hpp"
#include <iostream>
using std::cout;
using std::endl;
using namespace maze;
namespace solution
{
    class Node:public Cell
    {
    public:
        Node();
        Node(Cell);
        Node(Cell,Node*);
        Node* parent;
        Node* previous;     //only used in open and close list
        int gx;
        int hx;
        int Fx();
    };

    class Listxxy
    {
        Node* base;
        Node* top;
        int size;
    public:
        Listxxy():base(nullptr),top(nullptr),size(0){}
        ~Listxxy(){}
        bool IsEmpty(void);
        Node GetTop(void);
        Node Pop(void);
        Node GetMinCost(void);
        bool Push(Node);
        bool Delete(Node*);
        bool Contain(Node*);
        void Display();
        Node* GetTopP(void);
    };
};
