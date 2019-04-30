#include "render/material.h"
#include "filesystem/xml_file.h"
#include "common/log.h"


namespace water
{
	namespace render
	{
		void ParameterMap::set_param(std::string name, int value)
		{
			ParamValue p_value;
			p_value.int_1 = value;
			m_value_map[name] = p_value;
			m_type_map[name] = TypeInt;
		}
		void ParameterMap::set_raw_param(std::string name, std::string raw_value)
		{
			int str_length = raw_value.length;
			switch (str_length)
			{
			case 1: 

			default:
				break;
			}
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
			pugi::xml_node material = file.get_root_node();
			// load technique
			std::string tech_path = material.child("Technique").child_value();
			m_tech.load(tech_path.c_str());
			// load param map
			for (pugi::xml_node param_map = material.child("ParameterMap"); param_map; param_map = param_map.next_sibling("ParameterMap"))
			{
				ParameterMap map;
				for (pugi::xml_node param = param_map.child("Parameter"); param; param = param.next_sibling("Parameter"))
				{
					std::string name = param.attribute("name").as_string();
					std::string value = param.attribute("value").as_string();
					map.set_raw_param(name, value);
				}
				int index = param_map.attribute("index").as_int();
				m_param_map[index] = map;
			}
		}

	}
}