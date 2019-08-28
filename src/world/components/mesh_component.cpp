#include "mesh_component.h"
#include "mesh_component.h"
#include "component_const.h"
#include "mesh/IMeshLoader.h"

namespace water
{
	namespace world
	{
		ComponentTag MeshComponent::tag = COMP_MESH;
		MeshComponent & MeshComponent::operator=(const MeshComponent & comp)
		{
			Component::operator=(comp);
			if (&comp == this) return *this;
			m_mesh_ptr = comp.m_mesh_ptr;
			return *this;
		}
		MeshComponent::~MeshComponent()
		{
			m_mesh_ptr = nullptr;
		}
		Component* MeshComponent::create_component(GameObject* gameobject)
		{
			return new MeshComponent(gameobject);
		}

		void MeshComponent::load_from_file(std::string filename)
		{
			m_mesh_ptr = mesh::get_mesh_loader()->load_mesh(filename);
		}

	}
}
