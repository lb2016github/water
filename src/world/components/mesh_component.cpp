#include "mesh_component.h"
#include "mesh_component.h"
#include "component_const.h"
#include "mesh/IMeshLoader.h"
#include "world/gameobjects/component_object.hpp"
#include "filesystem/filesystem.h"

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

		void MeshComponent::load_from_file(std::string filename)
		{
			m_mesh_ptr = mesh::get_mesh_loader()->load_mesh(filesystem::FileSystem::get_instance()->get_absolute_path(filename));
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
