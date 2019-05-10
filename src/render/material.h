#ifndef WATER_MATERIAL_H
#define WATER_MATERIAL_H
#include "common/common.h"
#include "render/technique.h"
#include "math3d/math3d.hpp"
#include <memory>

namespace water
{
	namespace render
	{
		struct ParameterMap;
		class Material;
		typedef Material* MaterialPtr;

		WaterInterface IRenderObject;

		class Material
		{
		public:
			void load(const char* file_path);
			void render(IRenderObject* render_obj);
			ParameterMap get_param_map(int index);
		private:
			TechniquePtr m_tech;
			std::map<int, ParameterMap> m_param_map;
		};

		struct ParameterMap
		{
			void set_param(std::string name, int value);
			void set_raw_param(std::string name, std::string raw_value);
			ParamValueMap m_value_map;
			ParamTypeMap m_type_map;
		};
	}
}

#endif // !WATER_MATERIAL_H
