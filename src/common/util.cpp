#include "util.h"
#include "boost/algorithm/string.hpp"

namespace water {
	WaterID create_id()
	{
		static unsigned long next_id = 0;
		return ++next_id;
	}
	std::vector<int> stringToInList(std::string str)
	{
		std::vector<std::string> subValues;
		boost::split(subValues, str, boost::is_space());
		std::vector<int> result;
		for (auto iter = subValues.begin(); iter != subValues.end(); ++iter)
		{
			result.emplace_back(atoi(iter->c_str()));
		}
		return result;
	}
}
