#include "filesystem\filesystem.h"
#include <iostream>
#include "filesystem\xml_file.h"

using namespace water::filesystem;

void test_xml_file();
void test_filesystem();

char filepath[128];
void main() {
	test_xml_file();
	std::cout << "Press any key to quit" << std::endl;
	std::cin>>filepath;
}

void test_filesystem() {
	std::cout << "======================Start Test FileSystem ========================" << std::endl;
	water::filesystem::FileSystem& fs = water::filesystem::FileSystem::instance;
	char filepath[128] = "g:/test.txt";
	for (int i = 0; i < 100000; ++i)
	{
		char* buffer = fs.read_file(filepath);
		delete buffer;
	}
}

void test_xml_file() {
	std::cout << "============= Start Test Xml File =================" << std::endl;
	XMLFile file;
	std::string input;
	while (std::cin >> input) {
		if (input.compare("q") == 0) break;
		file.load(input.c_str());
	}
}

