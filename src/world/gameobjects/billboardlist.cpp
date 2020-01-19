#include "billboardlist.h"
#include "world/components/material_component.h"
#include "render/mesh.h"
#include "render/draw_command.h"
#include "render/render_const.h"
#include "math3d/math3d_common.h"

namespace water
{
	namespace world
	{
		BillboardList::BillboardList(): GameObject()
		{
			m_mesh = std::make_shared<render::MeshData>(
				"BillboardMesh", 0, render::POINTS);

		}
		BillboardList::~BillboardList()
		{
		}
		void BillboardList::render()
		{
			MaterialComponent::update_material(this, m_material);
			m_material->get_param_map(0)->setParam("size", m_size);
			m_mesh->position.resize(m_positions.size());
			std::copy(m_positions.begin(), m_positions.end(), m_mesh->position.begin());
			m_mesh->dirty = true;
			m_material->render(m_mesh);
		}
		void BillboardList::set_material(const std::string & mat_path)
		{
			auto rst = render::Material::load_from_file(mat_path);
			assert(rst.size() > 0);
			m_material = rst.begin()->second;
		}
		void BillboardList::set_size(const std::string & str)
		{
			m_size = math3d::string_to_vector2(str);
		}
		void BillboardList::set_positions(std::vector<math3d::Vector3> positions)
		{
			m_positions.resize(positions.size());
			std::copy(positions.begin(), positions.end(), m_positions.begin());
		}
	}
}