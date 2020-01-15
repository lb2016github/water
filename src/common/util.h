#ifndef WATER_UTIL_H
#define WATER_UTIL_H
#include <vector>
#include <string>

namespace water {
	typedef unsigned long WaterID;
	WaterID create_id();

	std::vector<int> stringToInList(std::string str);
}

#endif
