#include <iostream>
#include <map>
#include <functional>

using namespace std;




class Base
{
public:
	Base() { std::cout << "Base::Base" << std::endl; }
	Base(Base*) {}
};

class Derived : public Base
{
public:
	Derived(Derived*) {};
};

typedef std::function<Base* (void*)> FUNC_CREATE_COMPOENT;
std::map<std::string, FUNC_CREATE_COMPOENT> comp_map;


Base b;


void main()
{
	system("pause");

}
