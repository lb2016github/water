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
			// set param
			void set_param(const std::string& name, const ParamValue& pvalue);
			void set_param(const std::string& name, int value);
			void set_param(const std::string& name, float value);
			void set_param(const std::string& name, const math3d::Matrix& value);
			void set_param(const std::string& name, const math3d::Vector3& value);
			void set_param(const std::string& name, const math3d::Vector2& value);
			// set param value with str_value and type, which is called when param value is read from material file
			void set_raw_param(const std::string& name, const std::string& type, const std::string& raw_value);
			ParamValueType get_value_type(const std::string& name) const;

			// map of {name: value}
			ParamValueMap m_value_map;
			// map of {name: type}
			ParamTypeMap m_type_map;
		};
	}
}

#endif // !WATER_MATERIAL_H
