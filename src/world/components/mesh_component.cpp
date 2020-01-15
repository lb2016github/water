#include "mesh_component.h"
#include "mesh_component.h"
#include "component_const.h"
#include "world/gameobjects/component_object.hpp"
#include "filesystem/filesystem.h"
#include "world/loaders/assimpLoader.h"

namespace water
{
	namespace world
	{
		REGISTER_COMPONENT(MeshComponent, GameObject)

		MeshComponent & MeshComponent::operator=(const MeshComponent & comp)
		{
			if (&comp == this) return *this;
			BaseComponent::operator=(comp);
			m_mesh_ptr = comp.m_mesh_ptr;
			return *this;
		}
		MeshComponent::~MeshComponent()
		{
			m_mesh_ptr = nullptr;
		}

		std::vector<render::MeshDataPtr> MeshComponent::load_from_file(std::string filename, bool combined_mesh)
		{
			auto loader = AssimpLoader(filename);
			loader.doLoad();
			std::vector<render::MeshDataPtr> meshes;
			if (combined_mesh)
			{
				auto mesh = loader.getCombinedMesh();
				if (mesh)
				{
					meshes.push_back(mesh);
				}
				return meshes;
			}
			else
			{
				return loader.getAllMesh();
			}
		}

		void MeshComponent::set_mesh_ptr(render::MeshDataPtr mesh_ptr)
		{
			m_mesh_ptr = mesh_ptr;
		}

		render::MeshDataPtr MeshComponent::get_mesh_ptr()
		{
			return m_mesh_ptr;
		}

	}
}
