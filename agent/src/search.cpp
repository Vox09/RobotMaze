/*
 * File:   df-search.cpp
 * Author: Xu Xinyuan
 * Date:   2018-07-05
 */
 
#include "search.hpp"

using namespace solution;
//====================node staff=========================
Node::Node():Cell(),parent(nullptr),previous(nullptr),cost(0){};
Node::Node(Cell c):Cell(c),parent(nullptr), cost(0){};
Node::Node(Cell c,Node* p):Cell(c),parent(p),cost(0){};

//====================list staff=========================
bool Listxxy::IsEmpty() {return (size == 0);}
bool Listxxy::Push(Node e)
{
    Node* tmp;  
    tmp = top;  
    top = new Node;  
    if(!top) return false;  
    *top = e;  
    top->previous = tmp;
    size++;
    return true;
}
  
Node Listxxy::Pop()  
{
    if(size<=0) return Node();  
    Node tmp;  
    tmp = *top;
    delete top;  
    top = tmp.previous;  
    size--;
    return tmp;
}
  
Node Listxxy::GetTop() 
{
    return *top;
}
  
Node Listxxy::GetMinCost()  
{    
    if(IsEmpty())return Node();
    Node* tmp = top;  
    int minCost = tmp->cost;
    for(tmp;tmp!=nullptr;tmp = tmp->previous)
        minCost = tmp->cost<minCost?tmp->cost:minCost;
    tmp = top;    
    for(tmp;tmp->cost > minCost;tmp = tmp->previous);
    return *tmp;
}
  
//=================search staff======================
SearchAlgorithm::SearchAlgorithm()
{home[0] = -1; home[1] = -1;dest[0] = -1; dest[1] = -1;}

void SearchAlgorithm::SetHome(int _r, int _c)
{home[0] = _r; home[1] = _c;}

void SearchAlgorithm::SetDest(int _r, int _c)
{dest[0] = _r; dest[1] = _c;}

void SearchAlgorithm::SetMaze(Maze* _m)
{
    maze = _m;
    Cell entry = maze->GetEntry();
    Cell exit  = maze->GetExit();
    home[0] = entry.GetRow();
    home[1] = entry.GetCol();
    dest[0] = exit.GetRow();
    dest[1] = exit.GetCol();
    rowlimit = maze->GetRow();
    collimit = maze->GetCol();
    g_min = rowlimit*collimit;
//    entry.SetV(EXPLORED);
    stack.Push(Node(entry));
    open_list.Push(Node(entry));
}


result_t  SearchAlgorithm::Search()  
{  
    return GreedySearch(0);  
}
  

bool SearchAlgorithm::GoalTest(Node* cur)
{return(cur->GetRow() == dest[0] && cur->GetCol() == dest[1]);}

void SearchAlgorithm::GetCellAvailiable(Node* n,bool* r,int row, int col)
{
    bool* w = n->GetWallState();
    for(int i= 0;i<4;i++)
    {
        bool a = !n->CellOut(i,row,col);
        bool b = w[i];
        Cell tmp = maze->GetNextCell(n,i);
        bool c = !(tmp == n->parent );
        bool d = tmp.GetV() != DEAD ;
        r[i] = a && b && c && d;
    }
}

void SearchAlgorithm::Display()
{
    maze->Display();
//    std::cout<<stack.GetTop().cost<<std::endl;
}

dir_t SearchAlgorithm::IntToDir(int i)
{
    switch(i)
    {
        case 0: return 'N';
        case 1: return 'E';
        case 2: return 'S';
        case 3: return 'W';
        default: return 'N';
    }
}

float SearchAlgorithm::HeuristicCost(Node* n, dir_t dir)
{
    int r = n->GetRow();
    int c = n->GetCol();
    //int g = n->cost;
    switch(dir)
    {
        case 'N': r--;break;
        case 'S': r++;break;
        case 'E': c++;break;
        case 'W': c--;break; 
    }
    int fr = dest[0];
    int fc = dest[1];
    return sqrt((r-fr)*(r-fr)+(c-fc)*(c-fc));

}

dir_t SearchAlgorithm::GreedyChoice(Node* n, bool* dir)
{
    dir_t result;
    float mincost=rowlimit*collimit;
    for(int i = 0;i<4;i++)
    {
        if(dir[i])
        {
            float curcost = HeuristicCost(n,IntToDir(i)); 
            if(curcost < mincost)
            {
                result = IntToDir(i);
                mincost = curcost;
            }
        }
    }  
    g_min = g_min<mincost?g_min:mincost;
    // g_limit function to turn back to alternative ways.
    if(mincost>1.5*g_min+3) result = '\0';
    return result;
}

result_t  SearchAlgorithm::GreedySearch(int _cost)
{
    _cost++;
    Node n= stack.GetTop();
    maze->SetCellExplored(n.GetRow(),n.GetCol());
#ifdef ADISPLAY
    if(_cost%1==0)  
    {
        Display();
//        std::cout<<stack.GetMinCost().cost<<std::endl;
        system("sleep 0.1");
        system("clear");
    }
#endif
    if(GoalTest(&n) && _cost >1) return SOLVED;
    bool dir[4];
    GetCellAvailiable(&n, dir,rowlimit, collimit);
    while(dir[0] || dir[1] || dir[2] || dir[3])
    {
        dir_t nd = GreedyChoice(&n,dir);
        if(nd=='\0') break;
        Cell nc =  maze->GetNextCell(&n,nd);
        Node nn(nc,&n);
        if(nn.GetV() == EXPLORED ||  nn.GetV() == DEAD)  
            n.Close(nd);
        else{
            nn.cost = _cost;
            stack.Push(nn);
            result_t result = GreedySearch(_cost);
            if(result == SOLVED) return result;
            else n.Close(nd);
        }
        GetCellAvailiable(&n, dir, rowlimit, collimit);
    }
    maze->SetCellDEAD(n.GetRow(),n.GetCol());
    stack.Pop();
    return DEAD;
}

//result_t SearchAlgorithm::AStarSearch()  
//{
    //while(!open_list.IsEmpty())  
    //{  
//#ifdef ADISPLAY
        //if(_cost%3==0)  
        //{
            //Display();
////          std::cout<<stack.GetMinCost().cost<<std::endl;
            //system("sleep 0.1");
            //system("clear");
        //}
//#endif  
        //Node n = open_list.GetMinCost();  
        //if()
    //}
        //return SOLVED;
//}
