#ifndef WATER_MATERIAL_H
#define WATER_MATERIAL_H
#include "common/common.h"
#include "math3d/math3d.hpp"
#include <memory>
#include "render/render.h"
#include "draw_command.h"
#include "texture.h"


namespace water
{
	namespace render
	{

		class Material: public std::enable_shared_from_this<Material>
		{
		public:
			void load(const char* file_path);
			void render(IRenderable* render_obj);
			void render(const DrawCommand& draw_cmd, const MeshDataPtr mesh);
			ParameterMapPtr get_param_map(int index);
			unsigned int get_param_map_count();
		private:
			TechniquePtr m_tech;
			std::map<int, ParameterMapPtr> m_param_map;
		};

		typedef std::map<std::string, TextureDataPtr> TextureMap;

		struct ParameterMap
		{
			// check has certern parameter
			bool has_param(const std::string& name);
			// set param
			void set_param(const std::string& name, const ParamValue& pvalue);
			void set_param(const std::string& name, int value);
			void set_param(const std::string& name, float value);
			void set_param(const std::string& name, const math3d::Matrix& value);
			void set_param(const std::string& name, const math3d::Vector3& value);
			void set_param(const std::string& name, const math3d::Vector2& value);
			// set texture
			void set_texture(const std::string& name, TextureDataPtr tex_ptr);
			// set param value with str_value and type, which is called when param value is read from material file
			void set_raw_param(const std::string& name, const std::string& type, const std::string& raw_value, const std::string& semantic);
			// get value type of param
			ParamValueType get_value_type(const std::string& name) const;
			// get semantic of param by name
			SemanticType get_semantic(const std::string& name) const;

			// map of {name: value}
			ParamValueMap m_value_map;
			// map of {name: type}
			ParamTypeMap m_type_map;
			// map of textures
			TextureMap m_tex_map;
			// map of {name: semantic}
			std::map<std::string, SemanticType> m_semantic_map;
		};
	}
}

#endif // !WATER_MATERIAL_H
