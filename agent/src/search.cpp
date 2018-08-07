/*
 * File:   search.cpp
 * Author: Xu Xinyuan
 * Date:   2018-07-05
 */
 
#include "search.hpp"

using namespace solution;
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
    Node n(entry);
    EvaluateNode(&n,0);
    open_list.Push(n);
}


result_t  SearchAlgorithm::Search()  
{  
    return GreedySearch(0);  
    //return AStarSearch();  
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

float SearchAlgorithm::HeuristicCost(int r, int c)
{
    int fr = dest[0];
    int fc = dest[1];
    return sqrt((r-fr)*(r-fr)+(c-fc)*(c-fc));
    //return fr+fc-r-c;
}

float SearchAlgorithm::HeuristicCost(Node* n, dir_t dir)
{
    int r = n->GetRow();
    int c = n->GetCol();
    switch(dir)
    {
        case 'N': r--;break;
        case 'S': r++;break;
        case 'E': c++;break;
        case 'W': c--;break; 
    }
    return HeuristicCost(r,c);
}

float SearchAlgorithm::HeuristicCost(Node* n)
{
    int r = n->GetRow();
    int c = n->GetCol();
    return HeuristicCost(r,c);
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

void SearchAlgorithm::EvaluateNode(Node* pn ,int f)
{
    pn->gx = f;
    pn->hx = HeuristicCost(pn);
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
            nn.gx = _cost;
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

result_t SearchAlgorithm::AStarSearch()  
{
    result_t result = DEAD;
    bool dir[4];
    int curcost=0;
    Node* end;
    while(!open_list.IsEmpty())
    {
        Node n = open_list.GetMinCost();
        cout<<"current node "<<n.GetRow()<<" , "<<n.GetCol()<<endl;
        curcost = n.gx;
        if(GoalTest(&n))
        {
            end = &n;
            result = SOLVED;
            break;
        }
        maze->SetCellDEAD(n.GetRow(),n.GetCol());
        close_list.Push(n);
        GetCellAvailiable(&n,dir,rowlimit,collimit);
        for(int i=0;i<4;i++)
        {
            if(dir[i] && !n.CellOut(i,rowlimit,collimit))
            {
                // set parent pointer to the element in the list which is stored
                Node nn(maze->GetNextCell(&n,IntToDir(i)),close_list.GetTopP());
                EvaluateNode(&nn,curcost+1);
                if(!open_list.Contain(&nn) && !close_list.Contain(&nn)) {
                    maze->SetCellExplored(nn.GetRow(), nn.GetCol());
                    open_list.Push(nn);
                }
            }
        }
//        open_list.Display();
//        cout<<"=================="<<endl;
//        close_list.Display();
#ifdef ADISPLAY
        Display();
        std::cout<<n.gx<<std::endl;
        std::cout<<n.hx<<std::endl;
        std::cout<<n.Fx()<<std::endl;
        system("sleep 0.1");
        system("clear");
#endif
        open_list.Delete(&n);
    }
    for(Node* tmp=end;tmp != nullptr;tmp=tmp->parent)
    {
        stack.Push(*tmp);
        maze->SetCellSolution(tmp->GetRow(),tmp->GetCol());
    }
    Display();
    return result;
}
