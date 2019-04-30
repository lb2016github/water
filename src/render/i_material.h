#ifndef WATER_I_MATERIAL_H
#define WATER_I_MATERIAL_H
#include "common/common.h"
#include "render/technique.h"
#include "math3d/math3d.hpp"

namespace water
{
	namespace render
	{
		struct Material
		{
			Technique m_tech;
			std::vector<ParameterMap> m_uniform_params;
		};

		// represent value of varial types
		union ParamValue
		{
			math3d::Vector3 vec3;
			math3d::Vector2 vec2;
			math3d::Matrix mat;
			float float_1;
			int int_1;
		};
		struct ParameterMap
		{
			std::map<std::string, ParamValue> m_param_map;
			std::map<std::string, std::string> m_param_type_map;
		};
	}
}

#endif // !WATER_I_MATERIAL_H
