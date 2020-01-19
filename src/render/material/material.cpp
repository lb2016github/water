#include "render/material.h"
#include "filesystem/xml_file.h"
#include "common/log.h"
#include "render/technique.h"
#include "boost/algorithm/string.hpp"
#include "technique_common.h"
#include "filesystem/filesystem.h"
#include "material_param.h"

namespace water
{
	namespace render
	{
		void Material::render(IRenderable * render_obj)
		{
			m_tech->render(render_obj);
		}

		void Material::render(const MeshDataPtr mesh)
		{
			m_tech->render(shared_from_this(), mesh);
		}

		MaterialParamMapPtr Material::getParamMap(int index)
		{
			if (m_matParamMap.find(index) != m_matParamMap.end())
			{
				return m_matParamMap[index];
			}
			return nullptr;
		}

		void Material::setParamMap(int index, MaterialParamMapPtr param_map)
		{
			m_matParamMap[index] = param_map;
		}

		unsigned int Material::getParamMapCount()
		{
			return m_matParamMap.size();
		}

		void Material::setTechnique(const std::string & techFilepath)
		{
			m_tech = TechniqueManager::get_instance()->get_technique(techFilepath);
		}

		std::map<int, MaterialPtr> Material::loadFromFile(const std::string & filepath)
		{
			std::map<int, MaterialPtr> rtn;
			filesystem::XMLFile file;
			file.load(filepath);
			if (!file.m_loaded)
			{
				log_error("[Render]Fail to load file: %s", filepath.c_str());
				return rtn;
			}
			auto mat_group = file.get_root_node().first_child();
			for each (auto mat_node in mat_group.children())
			{
				auto mat_ptr = std::make_shared<Material>();
				int index = mat_node.attribute("index").as_int();
				rtn[index] = mat_ptr;
				for each (auto child in mat_node.children())
				{
					if (strcmp(child.name(), "Technique") == 0)
					{
						// load technique
						std::string tech_path = mat_node.child("Technique").child_value();
						mat_ptr->m_tech = TechniqueManager::get_instance()->get_technique(tech_path);
					}
					else if (strcmp(child.name(), "ParameterMap") == 0)
					{
						// load parameters
						MaterialParamMapPtr map_ptr = std::make_shared<MaterialParamMap>();
						int index = child.attribute("index").as_int();
						mat_ptr->m_matParamMap[index] = map_ptr;
						for each(auto param in child.children())
						{
							std::string name = param.attribute("name").as_string();
							std::string type = param.attribute("type").as_string();
							std::string value = param.attribute("value").as_string();
							std::string semantic_value = param.attribute("semantic").as_string();
							map_ptr->setRawParam(name, type, value, semantic_value);
						}
					}

				}
			}
		return rtn;
		}
	}
}