#ifndef WATER_MESH_COMPONENT_H
#define WATER_MESH_COMPONENT_H

#include "base_component.h"
#include "render/mesh.h"
#include <string>
#include "render/render_const.h"

namespace water
{
	namespace world
	{
		class MeshComponent : public BaseComponent
		{
		public:
			using BaseComponent::BaseComponent;
			virtual MeshComponent& operator = (const MeshComponent& comp);
			virtual ~MeshComponent();

			static const ComponentTag tag = COMP_MESH;


		public:
			std::vector<render::MeshDataPtr> load_from_file(std::string filename, bool combined_mesh);
			void set_mesh_ptr(render::MeshDataPtr mesh_ptr);
			render::MeshDataPtr get_mesh_ptr();

		protected:
			// pointer to mesh data
			render::MeshDataPtr m_mesh_ptr;
		};
	}
}

#endif // !WATER_MESH_COMPONENT_H
