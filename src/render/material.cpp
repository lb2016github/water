#include "render/material.h"
#include "filesystem/xml_file.h"
#include "common/log.h"
#include "render/technique.h"
#include "boost/algorithm/string.hpp"
#include "technique_common.h"
#include "filesystem/filesystem.h"

namespace water
{
	namespace render
	{
		bool ParameterMap::has_param(const std::string& name)
		{
			return m_value_map.find(name) != m_value_map.end();
		}
		void ParameterMap::set_param(const std::string& name, const ParamValue& pvalue)
		{
			if (m_value_map.find(name) == m_value_map.end()) return;
			m_value_map[name] = pvalue;
		}
		void ParameterMap::set_param(const std::string& name, int value)
		{
			if (m_value_map.find(name) == m_value_map.end()) return;
			m_value_map[name].int_1 = value;
		}
		void ParameterMap::set_param(const std::string& name, float value)
		{
			if (m_value_map.find(name) == m_value_map.end()) return;
			m_value_map[name].float_1 = value;
		}
		void ParameterMap::set_param(const std::string& name, const math3d::Matrix& value)
		{
			if (m_value_map.find(name) == m_value_map.end()) return;
			m_value_map[name].mat = value;
		}
		void ParameterMap::set_param(const std::string& name, const math3d::Vector3& value)
		{
			if (m_value_map.find(name) == m_value_map.end()) return;
			m_value_map[name].vec3 = value;
		}
		void ParameterMap::set_param(const std::string& name, const math3d::Vector2& value)
		{
			if (m_value_map.find(name) == m_value_map.end()) return;
			m_value_map[name].vec2 = value;
		}
		void ParameterMap::set_texture(const std::string& name, TextureDataPtr tex_ptr)
		{
			m_tex_map[name] = tex_ptr;
		}
		void ParameterMap::set_raw_param(const std::string& name, const std::string& type, const std::string& raw_value, const std::string& semantic )
		{
			if (CONFIG_param_type.find(type) == CONFIG_param_type.end())
			{
				log_error("Type %s is unkown\n", type);
				return;
			}
			std::vector<std::string> sub_values;
			ParamValue p_value;
			boost::split(sub_values, raw_value, boost::is_space());

			if (type == MATERIAL_VALUE_TYPE_MATRIX)
			{
				assert(sub_values.size() == 16);
				for (int i = 0; i < 16; ++i)
				{
					int col = i / 4, row = i % 4;
					p_value.mat[col][row] = atof(sub_values[i].c_str());
				}

			}
			else if (type == MATERIAL_VALUE_TYPE_FLOAT)
			{
				assert(sub_values.size() >= 1);
				p_value.float_1 = atof(sub_values[0].c_str());
			}
			else if (type == MATERIAL_VALUE_TYPE_INT)
			{
				assert(sub_values.size() >= 1);
				p_value.int_1 = atoi(sub_values[0].c_str());
			}
			else if (type == MATERIAL_VALUE_TYPE_VECTOR2)
			{
				assert(sub_values.size() >= 2);
				p_value.vec2.x = atof(sub_values[0].c_str());
				p_value.vec2.y = atof(sub_values[1].c_str());

			}
			else if (type == MATERIAL_VALUE_TYPE_VECTOR3)
			{
				assert(sub_values.size() >= 3);
				p_value.vec3.x = atof(sub_values[0].c_str());
				p_value.vec3.y = atof(sub_values[1].c_str());
				p_value.vec3.z = atof(sub_values[2].c_str());
			}
			else if (type == MATERIAL_VALUE_TYPE_SAMPLE2D)
			{
				auto tex_ptr = std::make_shared<TextureData>();
				auto img_ptr = std::make_shared<filesystem::Image>();
				img_ptr->load(raw_value);
				tex_ptr->tex_type = TEXTURE_2D;
				tex_ptr->images.push_back(img_ptr);
				set_texture(name, tex_ptr);
				return;
			}
			else
			{
				log_error("Unkown material type %s\n", type);
				return;
			}

			m_value_map[name] = p_value;
			m_type_map[name] = CONFIG_param_type[type];

			// init semantic
			auto sem_rst = CONFIG_Semantic.find(semantic);
			if (sem_rst != CONFIG_Semantic.end())
			{
				m_semantic_map[name] = sem_rst->second;
			}
		}
		ParamValueType ParameterMap::get_value_type(const std::string& name) const
		{
			auto rst = m_type_map.find(name);
			if (rst != m_type_map.end())
			{
				return rst->second;
			}
			log_warn("[Material]No parameter type is found with name: %s", name);
			return TypeNone;
		}
		SemanticType ParameterMap::get_semantic(const std::string& name) const
		{
			auto rst = m_semantic_map.find(name);
			if (rst == m_semantic_map.end()) return render::SemanticNone;
			return rst->second;
		}
		void Material::load(const char * file_path)
		{
			filesystem::XMLFile file;
			file.load(file_path);
			if (!file.m_loaded)
			{
				log_error("[Render]Fail to load file: %s", file_path);
				return;
			}
			auto material = file.get_root_node().first_child();
			// load technique
			std::string tech_path = material.child("Technique").child_value();
			m_tech = TechniqueManager::get_instance()->get_technique(tech_path);
			// load param map
			for (pugi::xml_node param_map = material.child("ParameterMap"); param_map; param_map = param_map.next_sibling("ParameterMap"))
			{
				ParameterMapPtr map_ptr = std::make_shared<ParameterMap>();
				for (pugi::xml_node param = param_map.child("Parameter"); param; param = param.next_sibling("Parameter"))
				{
					std::string name = param.attribute("name").as_string();
					std::string type = param.attribute("type").as_string();
					std::string value = param.attribute("value").as_string();
					std::string semantic_value = param.attribute("semantic").as_string();
					map_ptr->set_raw_param(name, type, value, semantic_value);
				}
				int index = param_map.attribute("index").as_int();
				m_param_map[index] = map_ptr;
			}
		}

		void Material::render(IRenderable * render_obj)
		{
			m_tech->render(render_obj);
		}

		void Material::render(const DrawCommand& draw_cmd, const MeshDataPtr mesh)
		{
			m_tech->render(draw_cmd, shared_from_this(), mesh);
		}

		ParameterMapPtr Material::get_param_map(int index)
		{
			if (m_param_map.find(index) != m_param_map.end())
			{
				return m_param_map[index];
			}
			return nullptr;
		}

		unsigned int Material::get_param_map_count()
		{
			return m_param_map.size();
		}

	}
}