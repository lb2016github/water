#include "billboardlist.h"
#include "world/components/material_component.h"
#include "render/mesh.h"
#include "render/draw_command.h"
#include "render/render_const.h"

namespace water
{
	namespace world
	{
		BillboardList::BillboardList(): GameObject()
		{
			render::MeshDataPtr mesh = std::make_shared<render::MeshData>(
				"BillboardMesh", 0, render::POINTS);
		}
		BillboardList::~BillboardList()
		{
		}
		void BillboardList::render()
		{
			MaterialComponent::update_material(this, m_material);
			m_mesh->position.clear();
			std::copy(m_positions.begin(), m_positions.end(), m_mesh->position.begin());
			m_mesh->dirty = true;
			m_material->render(m_mesh);
		}
	}
}