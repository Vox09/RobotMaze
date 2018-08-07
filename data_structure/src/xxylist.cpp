/*
 * File:   xxylist.cpp
 * Author: Xu Xinyuan
 * Date:   2018-08-01
 */
 
#include "xxylist.hpp"
using namespace solution;
//====================node staff=========================
Node::Node():Cell(),parent(nullptr),previous(nullptr),gx(0),hx(0){};
Node::Node(Cell c):Cell(c),parent(nullptr),gx(0),hx(0){};
Node::Node(Cell c,Node* p):Cell(c),parent(p),gx(0),hx(0){};
int Node::Fx(){return gx+hx;}
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
Node* Listxxy::GetTopP()
{
    return top;
}

bool Listxxy::Contain(Node* n)
{
    int r = n->GetRow();
    int c = n->GetCol();
    Node* tmp = top;
    while(tmp!=nullptr)
    {
        if(tmp->GetRow()==r && tmp->GetCol()==c)return true;
        tmp=tmp->previous;
    }
    return false;
}
  
bool Listxxy::Delete(Node* d)
{
    int r = d->GetRow();
    int c = d->GetCol();
    Node* tmp = top;
    if(tmp->GetRow()==r && tmp->GetCol()==c)
    {
        top = top->previous;
        size--;
        delete tmp;
        cout<<"delete empty"<<endl;
        return true;
    }
    while(tmp->previous->GetRow()!=r || tmp->previous->GetCol()!=c)
            tmp=tmp->previous;
    Node* backup = tmp->previous;
    tmp->previous = backup->previous;
    cout<<"deleting "<<backup->GetRow()<<" , "<<backup->GetCol()<<endl;
    delete backup;
    size--;
    return true;
}

Node Listxxy::GetMinCost()  
{    
    if(IsEmpty())return Node();
    Node* tmp = top;  
    int minFx = tmp->Fx();
    for(tmp;tmp!=nullptr;tmp = tmp->previous)
        minFx = tmp->Fx()<minFx?tmp->Fx():minFx;
    tmp = top;    
    for(tmp;tmp->Fx() > minFx;tmp = tmp->previous);
    return *tmp;
}
  
void Listxxy::Display()
{
    Node* tmp = top;
    for(tmp;tmp!=nullptr;tmp=tmp->previous){
        cout<<tmp->GetRow()<<" , "<<tmp->GetCol()<<endl;
    }
}