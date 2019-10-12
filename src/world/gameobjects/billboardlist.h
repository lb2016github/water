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
		private:
			std::vector<math3d::Vector3> m_positions;
			render::MaterialPtr m_material;
			render::MeshDataPtr m_mesh;
		};

	}
}

#endif // !WATER_BILLBOARD_LIST_H
