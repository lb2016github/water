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
		Model::Model()
		{
			// add components
			add_component(COMP_MESH);
			add_component(COMP_RENDER);
			add_component(COMP_TRANSFORMATION);
			add_component(COMP_MATERIAL);
		}
		Model::Model(const Model& model): GameObject(model)
		{
		}
		Model& Model::operator=(const Model& model)
		{
			if (&model == this) return *this;

			GameObject::operator=(model);
			return *this;
		}
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
				if (child.name == "Mesh")
				{
					std::string filepath = child.attribute("path").as_string();
					MeshComponent* mesh_comp = (MeshComponent*)get_component(COMP_MESH);
					mesh_comp->load_from_file(filename);
				}
				// load material
				else if (child.name == "Material")
				{
					std::string filepath = child.attribute("path").as_string();
					MaterialComponent* comp = (MaterialComponent*)get_component(COMP_MATERIAL);
					comp->load_from_file(filepath);
				}
			}
		}
	}
}