#ifndef WATER_MATERIAL_H
#define WATER_MATERIAL_H
#include "common/common.h"
#include "render/technique.h"
#include "math3d/math3d.hpp"

namespace water
{
	namespace render
	{
		class Material
		{
		public:
			void load(const char* file_path);
		private:
			Technique m_tech;
			std::map<int, ParameterMap> m_param_map;
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

		enum ParamValueType
		{
			TypeVector3,
			TypeVector2,
			TypeMatrix,
			TypeFloat,
			TypeInt,
		};
		struct ParameterMap
		{
			void set_param(std::string name, int value);
			void set_raw_param(std::string name, std::string raw_value);
			std::map<std::string, ParamValue> m_value_map;
			std::map<std::string, ParamValueType> m_type_map;
		};
	}
}

#endif // !WATER_MATERIAL_H
