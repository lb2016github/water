#include "math3d_common.h"
#include "boost/algorithm/string.hpp"

namespace water
{
	namespace math3d
	{
		math3d::Vector3 string_to_vector(std::string str)
		{
			std::vector<std::string> sub_values;
			boost::split(sub_values, str, boost::is_space());
			assert(sub_values.size() == 3);
			return math3d::Vector3(atof(sub_values[0].c_str()), atof(sub_values[1].c_str()), atof(sub_values[2].c_str()));
		}

		Vector2 string_to_vector2(std::string str)
		{
			std::vector<std::string> sub_values;
			boost::split(sub_values, str, boost::is_space());
			assert(sub_values.size() == 2);
			return math3d::Vector2(atof(sub_values[0].c_str()), atof(sub_values[1].c_str()));
		}

	}
}
