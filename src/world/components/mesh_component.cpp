#include "mesh_component.h"
#include "mesh_component.h"
#include "component_const.h"

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

	}
}

water::world::MeshComponent::~MeshComponent()
{
	m_mesh_ptr = nullptr;
}
