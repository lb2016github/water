#ifndef WATER_MESH_COMPONENT_H
#define WATER_MESH_COMPONENT_H

#include "world/component.h"
#include "render/mesh.h"
#include <string>

namespace water
{
	namespace world
	{
		class MeshComponent : public Component
		{
		public:
			void set_mesh_ptr(render::MeshDataPtr mesh_ptr) { m_mesh_ptr = mesh_ptr; };
		protected:
			// pointer to mesh data
			render::MeshDataPtr m_mesh_ptr;
		};


	}
}

#endif // !WATER_MESH_COMPONENT_H
