#include "filesystem\filesystem.h"
#include <iostream>
#include "render\technique.h"

using namespace water::render;
void test_load_technique_file();

char filepath[128];
void main() {
	test_load_technique_file();
	std::cout << "Press any key to quit" << std::endl;
	std::cin>>filepath;
}

void test_load_technique_file()
{
	std::cout << "============= Start Test Loading Technique File =================" << std::endl;
	std::string input;
	while (std::cin >> input)
	{
		Technique tech;
		tech.load(input.c_str());
	}
}


