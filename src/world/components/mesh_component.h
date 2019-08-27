#ifndef WATER_MESH_COMPONENT_H
#define WATER_MESH_COMPONENT_H

#include "component.h"
#include "render/mesh.h"
#include <string>
#include "render/render_const.h"

namespace water
{
	namespace world
	{
		class MeshComponent : public Component
		{
		public:
			MeshComponent() : m_mesh_ptr(nullptr) {};
			MeshComponent(GameObject* game_object) : Component(game_object), m_mesh_ptr(nullptr) {};
			MeshComponent(const MeshComponent& comp) : MeshComponent(comp, nullptr) {};
			MeshComponent(const MeshComponent& comp, GameObject* game_object) : Component(game_object), m_mesh_ptr(comp.m_mesh_ptr){};
			MeshComponent& operator = (const MeshComponent& comp);
			virtual ~MeshComponent();

			// component info
			static ComponentTag tag;
			static Component* create_component(GameObject*);

		public:
			void set_mesh_ptr(render::MeshDataPtr mesh_ptr) { m_mesh_ptr = mesh_ptr; };
			render::MeshDataPtr get_mesh_ptr() { return m_mesh_ptr; }

		protected:
			// pointer to mesh data
			render::MeshDataPtr m_mesh_ptr;
		};
	}
}

#endif // !WATER_MESH_COMPONENT_H
