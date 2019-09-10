#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include "game_objects.hpp"


using namespace std;


class Base
{
public:
	Base() { this->print(); }
	Base(Base*) {}
	void init() { print(); }

	virtual void print(){std::cout << "Base::print" << std::endl;}
};

class Derived : public Base
{
public:
	virtual void print(){std::cout << "Derived::print" << std::endl;}
};

template<typename ...args>
struct Test;

template<typename first, typename ...args>
struct Test<first, args...>: public Test<args...>
{
	Test<first, args...>(): Test<args...>()
	{
		objs.push_back(new first());
	}
};

template<>
struct Test<>
{
	Test()
	{
	}
	std::vector<Base*> objs;
};


void main()
{
	DerivedAB ab;
	system("pause");
}
