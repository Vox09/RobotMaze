/*
* File:   maze.cpp
* Author: Xu Xinyuan
* Date:   2018-05-25
*/


#include "maze.hpp"

using namespace maze;
using std::cout;
using std::endl;

// cell set up 
Cell::Cell():V(UNVISITED)
{
    for(int i =0;i<2;i++)place[i]=-1;
    for(int i =0;i<4;i++)wall[i] = false;
}
Cell::Cell(int _v){Cell();SetV(_v);}
void Cell::SetV(int _V){V = _V;}
int Cell::GetV(){return V;}
void Cell::SetPlace(int _r, int _c)
{place[0] = _r; place[1] = _c;}
int Cell::GetRow(){return place[0];}
int Cell::GetCol(){return place[1];}
void Cell::Open(dir_t d)
{
    switch(d)
    {
        case 'N':wall[0] = true;break;
        case 'E':wall[1] = true;break;
        case 'S':wall[2] = true;break;
        case 'W':wall[3] = true;break;
    }
}

void Cell::Close(dir_t d)
{
    switch(d)
    {
        case 'N':wall[0] = false;break;
        case 'E':wall[1] = false;break;
        case 'S':wall[2] = false;break;
        case 'W':wall[3] = false;break;
    }
}

bool* Cell::GetWallState()
{
    return wall;
}

bool Cell::CellOut(dir_t dir, int r, int c)
{
    switch(dir)
    {
        case 'N':return (GetRow() <= 0);
        case 'S':return (GetRow() >= r-1);
        case 'W':return (GetCol() <= 0);
        case 'E':return (GetCol() >= c-1);
    }
    return true;
}

bool Cell::CellOut(int dir, int r, int c)
{
    switch(dir)
    {
        case 0:return (GetRow() <= 0);
        case 1:return (GetCol() >= c-1);
        case 2:return (GetRow() >= r-1);
        case 3:return (GetCol() <= 0);
    }
    return true;
}

bool Cell::operator==(Cell* c)
{
    if(c == nullptr) return false;
    return(place[0] == c->GetRow() && place[1] == c->GetCol());
}

//=========================================================
//Maze stuff
//Constructor
Maze::Maze(int _row, int _col):wallProp(0.0)
{
    home[0] = -1;home[1] = -1;dest[0] = -1;dest[1] = -1;
	row = _row;
	col = _col;
	if(row<4 && col<4){
		cout<<"not enough space for a maze!"<<endl;
		cout<<"at least 4 x 4."<<endl;
		row = 4;
		col = 4;	
	}
	pc = new Cell* [row];
	for(int i=0;i<row;i++) 
    {
        pc[i] = new Cell [col];
        for(int j=0;j<col;j++)
        {
            pc[i][j].SetPlace(i,j);
        }
    }
}

//Destructor
Maze::~Maze()
{
	for(int j=0;j<row;j++) delete [] pc[j];
	delete [] pc;
}
//simple useless method
void Maze::Hi(){cout<<"hello! I'm a cute maze."<<endl;}
int Maze::GetRow(){return row;}
int Maze::GetCol(){return col;}
void Maze::ShowStatus(){cout<<"row: "<<row<<"\n"<<"col: "<<col<<endl;}
//complex method

void Maze::Display()
{
#ifndef SDISPLAY
	for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<"+";
            if(!pc[i][j].GetWallState()[0])
                cout<<"---";
            else cout<<"   ";
        }
		cout<<"+"<<endl;
		for(int j=0;j<col;j++)
        {
            if(!pc[i][j].GetWallState()[3])cout<<"|";
            else cout<<" ";
  			if(pc[i][j].GetV()==EXPLORED)cout<<" x ";
            else if(pc[i][j].GetV()==DEAD)cout<<" D ";
            else if(pc[i][j].GetV()==SOLVED)cout<<" S ";
            else cout<<"   ";
		}
        if(!pc[i][col-1].GetWallState()[1])cout<<"|";
        cout<<endl;
    }
	for(int j=0;j<col;j++)cout<<"+---";
        cout<<"+"<<endl;

#else 
	for(int j=0;j<col;j++)cout<<"__";
    cout<<"_"<<endl;
	for(int i=0;i<row;i++)
    {

		for(int j=0;j<col;j++)
        {
            if(!pc[i][j].GetWallState()[3])cout<<"|";
            else cout<<" ";
  			if(pc[i][j].GetV()==EXPLORED)cout<<"x";
            else if(!pc[i][j].GetWallState()[2])cout<<"_";
            else cout<<" ";
		}
        if(!pc[i][col-1].GetWallState()[1])cout<<"|";
		cout<<endl;
	}
#endif
}

Cell Maze::GetNextCell(Cell* c,int dir)
{
    if(c->CellOut(dir,row,col))return OUT;
    int nr,nc;
    switch(dir)
    {
        case 0:nr = c->GetRow()-1;
                 nc = c->GetCol();
                 break;
        case 1:nr = c->GetRow();
                 nc = c->GetCol()+1;
                 break;
        case 2:nr = c->GetRow()+1;
                 nc = c->GetCol();
                 break;
        case 3:nr = c->GetRow();
                 nc = c->GetCol()-1;
                 break;
        default: return Cell(OUT);
    }
    return pc[nr][nc];
}

int Maze::GetNextCellState(Cell* c,dir_t dir)
{
    if(c->CellOut(dir,row,col))return OUT;
    int nr,nc;
    switch (dir) {
        case 'N':
            nr = c->GetRow() - 1;
            nc = c->GetCol();
            break;
        case 'E':
            nr = c->GetRow();
            nc = c->GetCol() + 1;
            break;
        case 'S':
            nr = c->GetRow() + 1;
            nc = c->GetCol();
            break;
        case 'W':
            nr = c->GetRow();
            nc = c->GetCol() - 1;
            break;
    }
    return pc[nr][nc].GetV();
}

Cell Maze::GetNextCell(Cell* cur,dir_t dir)
{
    int r = cur->GetRow();
    int c = cur->GetCol();
    bool* wall = cur->GetWallState();
    switch(dir)
    {
        case 'N':if(!cur->CellOut('N',row,col) && wall[0])
                     return GetCell(r-1,c);
                 break;
        case 'E':if(!cur->CellOut('E',row,col) && wall[1])
                     return GetCell(r,c+1);
                 break;
        case 'S':if(!cur->CellOut('S',row,col) && wall[2])
                     return GetCell(r+1,c);
                 break;
        case 'W':if(!cur->CellOut('W',row,col) && wall[3])
                     return GetCell(r,c-1);
                 break;
    }
    return Cell(OUT);
}

void Maze::GetCellUnvisited(Cell* c,bool* r)
{
    if(GetNextCellState(c,'N')==UNVISITED ) 
        r[0] = true;
    else r[0] = false;
    if(GetNextCellState(c,'E')==UNVISITED ) 
        r[1] = true;
    else r[1] = false;
    if(GetNextCellState(c,'S')==UNVISITED ) 
        r[2] = true;
    else r[2] = false;
    if(GetNextCellState(c,'W')==UNVISITED ) 
        r[3] = true;
    else r[3] = false;
}

void Maze::Generate()  
{  
   GenDepth(&pc[rd()%row][rd()%col]);  
   OpenWalls(0);
   for(int i =0;i<row;i++)  
       for(int j =0;j<col;j++)  
           pc[i][j].SetV(UNVISITED);
}
  
void Maze::GenDepth(Cell* ph)
{
    //while cell is not dead
    //check avaiable dir
    //random a direction
    //generate next cell
    ph->SetV(VISITED);
    bool dir[4];
    GetCellUnvisited(ph,dir);
    while(dir[0] || dir [1] || dir[2] || dir[3])
    {
        int nr=ph->GetRow(),nc = ph->GetCol();
        switch(RandomChoice(dir))// at least one available
        {
            case 0:nr = ph->GetRow()-1;
                nc = ph->GetCol();
                ph->Open('N');
                pc[nr][nc].Open('S');
                break;
            case 1:nr = ph->GetRow();
                nc = ph->GetCol()+1;
                ph->Open('E');
                pc[nr][nc].Open('W');
                break;
            case 2:nr = ph->GetRow()+1;
                nc = ph->GetCol();
                ph->Open('S');
                pc[nr][nc].Open('N');
                break;
            case 3:nr = ph->GetRow();
                nc = ph->GetCol()-1;
                ph->Open('W');
                pc[nr][nc].Open('E');
                break;
        }
#ifdef DISPLAY
        Display();
        //cout<<"nr:"<<nr<<"      nc:"<<nc<<endl;
        system("sleep 0.1");
        system("clear");
#endif        
        GenDepth(&pc[nr][nc]);
        GetCellUnvisited(ph,dir);
    }
    ph->SetV(DEAD);
}
  
void Maze::OpenWalls(int done)  
{
    static int wallSum = (row*col-row-col)*wallProp;
    if(done >= wallSum) return;
    int _r ,_c;  
    bool* dir;
    do{  
        _r = rd()%(row-2)+1;  
        _c = rd()%(col-2)+1;
        dir = pc[_r][_c].GetWallState();  
    }
    while((dir[0] && dir [1] && dir[2] && dir[3]));
    bool tmp[4];    
    for (int i = 0;i<4;i++)  tmp[i] =! dir[i];
    int w1 = RandomChoice((tmp));
    int w2;
    pc[_r][_c].Open(IntToDir(w1));
    Cell near = GetNextCell(&pc[_r][_c],w1);
    _r = near.GetRow();
    _c = near.GetCol();
    switch (w1)
    {
        case 0: w2 = 2;break;
        case 1: w2 = 3;break;
        case 2: w2 = 0;break;
        case 3: w2 = 1;break;
    }
    pc[_r][_c].Open(IntToDir(w2));
    done++;
    OpenWalls(done);
}

Cell Maze::GetCell(int _r, int _c){return pc[_r][_c];}
void Maze::SetEntry(int _r, int _c)
{
    home[0] = _r;
    home[1] = _c;
    if(_c == 0)    pc[_r][_c].Open('W');
    else if (_c == col-1)   pc[_r][_c].Open('E');
    else if (_r == 0)       pc[_r][_c].Open('N'); 
    else if (_r == row-1)   pc[_r][_c].Open('S');
}

void Maze::SetExit(int _r, int _c)
{
    dest[0] = _r;
    dest[1] = _c;
    if(_c == 0)    pc[_r][_c].Open('W');
    else if (_c == col-1)   pc[_r][_c].Open('E');
    else if (_r == 0)       pc[_r][_c].Open('N'); 
    else if (_r == row-1)   pc[_r][_c].Open('S');
}

Cell Maze::GetEntry(){return pc[home[0]][home[1]];}
Cell Maze::GetExit(){return pc[dest[0]][dest[1]];}
void Maze::SetWallProp(float p){wallProp = p;}

void Maze::SetCellSolution(int _r, int _c)
{pc[_r][_c].SetV(SOLVED);}
void Maze::SetCellExplored(int _r,int _c)
{pc[_r][_c].SetV(EXPLORED);}

void Maze::SetCellDEAD(int _r,int _c)
{pc[_r][_c].SetV(DEAD);}

int Maze::RandomChoice(bool* dir)
{
    int sum=0;
    int result;
    for(int i = 0; i<4 ;i++) if(dir[i]) {sum++;result = i;}//available dirs
    int r=rd()%sum;//choices less than available dirs
    for(int i = 0; r>=0; i++) if(dir[i]) {result = i;r--;}
    return result;
}
  
dir_t Maze::IntToDir(int _i)  
{
    switch(_i)  
    {
        case 0 :return 'N';
        case 1 :return 'E';
        case 2 :return 'S';
        case 3 :return 'W';
    }
    return '\0';  
}

void Maze::WriteToFile(std::string name)
{
    std::ofstream outf(name);

	for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            outf<<"+";
            if(!pc[i][j].GetWallState()[0])
                outf<<"---";
            else outf<<"   ";
        }
		outf<<"+"<<endl;
		for(int j=0;j<col;j++)
        {
            if(!pc[i][j].GetWallState()[3])outf<<"|";
            else outf<<" ";
  			if(pc[i][j].GetV()==EXPLORED)outf<<" x ";
            else if(pc[i][j].GetV()==DEAD)outf<<" D ";
            else if(pc[i][j].GetV()==SOLVED)outf<<" S ";
            else outf<<"   ";
		}
        if(!pc[i][col-1].GetWallState()[1])outf<<"|";
        outf<<endl;
    }
	for(int j=0;j<col;j++)outf<<"+---";
        outf<<"+"<<endl;
}

void Maze::LoadFromFile(std::string name)
{
    std::ifstream inf(name);
    std::string s;
    while(getline(inf,s))
    {
       s.length(); 
    }

}
