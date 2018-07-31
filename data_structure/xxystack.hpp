/*
* File:   xxystack.hpp
* Author: Xu Xinyuan
* Date:   2018-05-26
*/
#ifndef XXYSTACK_HPP
#define XXYSTACK_HPP
#include <cstdlib>

namespace maze{
	template <typename CustomType>
	struct CustomClass
	{
		CustomType elem;
		CustomClass* link;
	};

	template<typename CustomType>
	class XXYStack
	{
		CustomClass<CustomType>* base;
		CustomClass<CustomType>* top;
		int size;
	public:
		XXYStack():base(NULL),top(NULL),size(0){}
		~XXYStack(){}
		bool IsEmpty(void);
		CustomType GetTop(void);
		CustomType Pop(void);
		bool Push(CustomType e);
	};

}
#include "../src/xxystack.cc"
#endif


