#include <iostream>

using namespace std;

class Base
{
public:
	Base() { std::cout << "Base::Base" << std::endl; }
	Base(const Base&) = delete;
	~Base() { std::cout << "Base::~Base" << std::endl; }
};
class Base1
{
public:
	Base1() { std::cout << "Base1::Base1" << std::endl; }
	~Base1() { std::cout << "Base1::~Base1" << std::endl; }
};

class Derived : public Base, public Base1
{
public:
	Derived() {}
	Derived(const Derived&) {}

};



void main()
{
	Derived* d = new Derived();
	Derived b(*d);

	system("pause");

}
