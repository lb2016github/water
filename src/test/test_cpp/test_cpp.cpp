#include <iostream>

using namespace std;

class Base
{
public:
	Base() { std::cout << "Base::Base" << std::endl; }
	Base(const Base&) = delete;
	~Base() { std::cout << "Base::~Base" << std::endl; }

	static int b;
	static void prin_static();
};

int Base::b = 3;

void Base::prin_static()
{
	std::cout << "Base::b" << Base::b << std::endl;
}

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
	static int b;

};
int Derived::b = 4;



void main()
{
	Derived* d = new Derived();
	Derived b(*d);

	d->prin_static();
	Derived::prin_static();

	system("pause");

}
