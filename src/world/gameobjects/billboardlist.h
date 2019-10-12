#ifndef WATER_BILLBOARD_LIST_H
#define WATER_BILLBOARD_LIST_H
#include "world/gameobjects/space_object.h"
#include "math3d/math3d.hpp"
#include "render/material.h"
#include "render/mesh.h"

namespace water
{
	namespace world
	{
		class BillboardList: public GameObject
		{
		public:
			BillboardList();
			virtual ~BillboardList();
			void render();
			void set_material(const std::string& mat_path);
			void set_size(const std::string& str);
			void set_positions(std::vector<math3d::Vector3> positions);
		private:
			std::vector<math3d::Vector3> m_positions;
			render::MaterialPtr m_material;
			render::MeshDataPtr m_mesh;
			math3d::Vector2 m_size;
		};

		DECL_SHARED_PTR(BillboardList);

	}
}

#endif // !WATER_BILLBOARD_LIST_H
