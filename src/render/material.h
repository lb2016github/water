#ifndef WATER_MATERIAL_H
#define WATER_MATERIAL_H
#include "common/common.h"
#include "math3d/math3d.hpp"
#include <memory>
#include "render/render.h"

namespace water
{
	namespace render
	{
		class Material
		{
		public:
			void load(const char* file_path);
			void render(IRenderable* render_obj);
			ParameterMap get_param_map(int index);
		private:
			TechniquePtr m_tech;
			std::map<int, ParameterMap> m_param_map;
		};

		struct ParameterMap
		{
			void set_param(std::string name, int value);
			void set_raw_param(std::string name, std::string raw_value);
			ParamValueType get_value_type(std::string name) const;
			ParamValueMap m_value_map;
			ParamTypeMap m_type_map;
		};
	}
}

#endif // !WATER_MATERIAL_H
