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

		void MeshComponent::set_mesh_ptr(render::MeshDataPtr mesh_ptr)
		{
			m_mesh_ptr = mesh_ptr;
		}

		void MeshComponent::initMesh(const std::string& filepath, std::vector<int> meshIndices)
		{
			auto loader = AssimpLoader(filepath);
			loader.doLoad();
			auto meshList = loader.getAllMesh();
			std::vector<render::MeshDataPtr> meshes;
			for each (int idx in meshIndices)
			{
				meshes.push_back(meshList[idx]);
			}
			m_mesh_ptr = render::MeshData::combineMeshes(meshes);

		}

		render::MeshDataPtr MeshComponent::get_mesh_ptr()
		{
			return m_mesh_ptr;
		}

	}
}
