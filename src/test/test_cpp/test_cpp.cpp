#include <iostream>
#include <map>
#include <functional>

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


void main()
{
	Derived b;
	b.init();
	system("pause");
}
