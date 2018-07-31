/*
* File:   xxystack.cpp
* Author: Xu Xinyuan
* Date:   2018-05-26
*/

using namespace maze;

template<typename CustomType>
bool XXYStack<CustomType>::IsEmpty(void)
{
	if( top == base)return true;
	return false;
}

template<typename CustomType>
bool XXYStack<CustomType>::Push(CustomType e)
{
	CustomClass<CustomType>* tmp;
	tmp = top;
	top = new CustomClass<CustomType>;
	if(!top) return false;
	top->elem = e;
	top->link = tmp;
	size++;
	return true;
}

template<typename CustomType>
CustomType XXYStack<CustomType>::Pop(void)
{
	//if(this->size<=0) return NULL;
	CustomClass<CustomType> tmp;
	tmp.elem = top->elem;
	tmp.link = top->link;
	delete top;
	top = tmp.link;
	size--;
	return tmp.elem;
}

template<typename CustomType>
CustomType XXYStack<CustomType>::GetTop(void)
{
	return top->elem;
}
  
