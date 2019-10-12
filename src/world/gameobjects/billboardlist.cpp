#include "billboardlist.h"
#include "world/components/material_component.h"
#include "render/mesh.h"
#include "render/draw_command.h"

namespace water
{
	namespace world
	{
		void BillboardList::render()
		{
			MaterialComponent::update_material(this, m_material);
			render::MeshDataPtr mesh = std::make_shared<render::MeshData>();
			for each(auto pos in m_positions)
			{
				mesh->position.push_back(pos);
			}
			m_material->render(mesh);
		}
	}
}