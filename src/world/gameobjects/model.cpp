#include "model.h"
#include "world/components/component_const.h"
#include "world/components/mesh_component.h"
#include "world/components/material_component.h"
#include "filesystem/xml_file.h"
#include "filesystem/filesystem.h"
#include "common/log.h"

namespace water
{
	namespace world
	{
		void Model::load_from_file(std::string & filepath)
		{
			auto fs = filesystem::FileSystem::get_instance();
			filesystem::XMLFile xml_file;
			xml_file.load(fs->get_absolute_path(filepath));
			if (xml_file.m_loaded != true)
			{
				log_error("[MODEL]Fail to load file %s\n", filepath.c_str());
				return;
			}
			auto root_node = xml_file.get_root_node();
			for each (auto child in root_node.children())
			{
				// load mesh
				if (strcmp(child.name(), "Mesh") == 0)
				{
					std::string filepath = child.attribute("path").as_string();
					MeshComponent* mesh_comp = (MeshComponent*)get_component(COMP_MESH);
					mesh_comp->load_from_file(fs->get_absolute_path(filepath));
				}
				// load material
				else if (strcmp(child.name(), "Material") == 0)
				{
					std::string filepath = child.attribute("path").as_string();
					MaterialComponent* comp = (MaterialComponent*)get_component(COMP_MATERIAL);
					comp->load_from_file(fs->get_absolute_path(filepath));
				}
			}
		}
		std::set<ComponentTag> Model::get_comp_tags()
		{
			auto rst = SpaceObject::get_comp_tags();
			rst.insert(COMP_MESH);
			rst.insert(COMP_MATERIAL);
			return rst;
		}
	}
}