#include "model.h"
#include "world/components/component_const.h"
#include "world/components/mesh_component.h"
#include "world/components/material_component.h"
#include "filesystem/xml_file.h"
#include "filesystem/filesystem.h"
#include "common/log.h"
#include "render/material.h"

namespace water
{
	namespace world
	{
		void Model::load_from_file(std::string & filepath)
		{
			filesystem::XMLFile xml_file;
			xml_file.load(filepath);
			if (xml_file.m_loaded != true)
			{
				log_error("[MODEL]Fail to load file %s\n", filepath.c_str());
				return;
			}
			auto root_node = xml_file.get_root_node();
			root_node = root_node.first_child();

			std::vector<render::MeshDataPtr> cached_mesh;
			std::string cached_mesh_path = "";
			for each (auto sub_model in root_node.children()) // is SubModel Node
			{
				int index = sub_model.attribute("index").as_int();
				ModelPtr model;
				if (index == 0)
				{
					model = std::dynamic_pointer_cast<Model>(shared_from_this());
				}
				else
				{
					model = std::make_shared<Model>();
					this->add_child(model);
				}
				for each(auto child in sub_model.children())
				{
					// load mesh
					if (strcmp(child.name(), "Mesh") == 0)
					{
						std::string filepath = child.attribute("path").as_string();
						int mesh_idx = child.attribute("mesh_idx").as_int();
						auto mesh_comp = (MeshComponent*)model->get_component(COMP_MESH);
						if (mesh_idx < 0)
						{
							mesh_comp->set_mesh_ptr(mesh_comp->load_from_file(filepath, true)[0]);
							continue;
						}
						else if (filepath != cached_mesh_path)
						{
							cached_mesh = mesh_comp->load_from_file(filepath, false);
							cached_mesh_path = filepath;
						}
						mesh_comp->set_mesh_ptr(cached_mesh[mesh_idx]);
					}
					// load material
					else if (strcmp(child.name(), "Material") == 0)
					{
						std::string filepath = child.attribute("path").as_string();
						int mat_idx = child.attribute("mat_idx").as_int();
						auto mat_map = render::Material::load_from_file(filepath);
						MaterialComponent* comp = (MaterialComponent*)model->get_component(COMP_MATERIAL);
						comp->set_material(mat_map[mat_idx]);
					}
				}
			}
		}
	}
}