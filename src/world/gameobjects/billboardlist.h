#ifndef WATER_BILLBOARD_LIST_H
#define WATER_BILLBOARD_LIST_H
#include "world/gameobjects/space_object.h"
#include "math3d/math3d.hpp"
#include "render/material.h"

namespace water
{
	namespace world
	{
		class BillboardList: public GameObject
		{
		public:
			void render();
		private:
			std::vector<math3d::Vector3> m_positions;
			render::MaterialPtr m_material;
		};

	}
}

#endif // !WATER_BILLBOARD_LIST_H
