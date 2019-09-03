#include "mesh_component.h"
#include "mesh_component.h"
#include "component_const.h"
#include "mesh/IMeshLoader.h"

namespace water
{
	namespace world
	{
		ComponentTag MeshComponent::tag = COMP_MESH;
		MeshComponent::MeshComponent(GameObject * game_object): Component(game_object)
		{
		}
		MeshComponent & MeshComponent::operator=(const MeshComponent & comp)
		{
			if (&comp == this) return *this;
			Component::operator=(comp);
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
