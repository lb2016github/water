#include "model.h"
#include "world/components/component_const.h"
#include "world/components/mesh_component.h"
#include "world/components/material_component.h"
#include "filesystem/xml_file.h"
#include "common/log.h"

namespace water
{
	namespace world
	{
		Model::~Model()
		{
		}
		render::MaterialPtr Model::get_material()
		{
			MaterialComponent* comp = (MaterialComponent*)get_component(COMP_MATERIAL);
			return comp->get_material();
		}
		render::MeshDataPtr Model::get_mesh()
		{
			MeshComponent* mesh_comp = (MeshComponent*)get_component(COMP_MESH);
			return mesh_comp->get_mesh_ptr();
		}
		render::DrawCommand Model::get_draw_command()
		{
			render::DrawCommand dc;
			dc.draw_mode = render::TRIANGLES;
			return dc;
		}
		void Model::load_from_file(std::string & filename)
		{
			filesystem::XMLFile xml_file;
			xml_file.load(filename.c_str());
			if (xml_file.m_loaded != true)
			{
				log_error("[MODEL]Fail to load file %s\n", filename.c_str());
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
					mesh_comp->load_from_file(filename);
				}
				// load material
				else if (strcmp(child.name(), "Material") == 0)
				{
					std::string filepath = child.attribute("path").as_string();
					MaterialComponent* comp = (MaterialComponent*)get_component(COMP_MATERIAL);
					comp->load_from_file(filepath);
				}
			}
		}
		void Model::render()
		{
			auto comp_mat = (MaterialComponent*)get_component(COMP_MATERIAL);
			if (comp_mat)
			{
				comp_mat->render(get_draw_command(), get_mesh());
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