#ifndef WATER_MATH3D_COMMON_H
#define WATER_MATH3D_COMMON_H
#include <string>
#include "math3d.hpp"

namespace water
{
	namespace math3d
	{
		Vector3 string_to_vector(std::string str);
		Vector2 string_to_vector2(std::string str);
	}
}

#endif // !WATER_MATH3D_COMMON_H
