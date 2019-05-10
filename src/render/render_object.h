#ifndef WATER_RENDER_OBJECT_H
#define WATER_RENDER_OBJECT_H
#include "common/common.h"
#include "render/material.h"
#include <memory>

namespace water
{
	namespace render
	{
		WaterInterface IMesh;
		WaterInterface IRenderObject;
		typedef std::shared_ptr<IMesh> MeshPtr;

		WaterInterface IMesh
		{
			unsigned int base_vertex;
			unsigned int base_index;
			unsigned int num_indices;
		};


		WaterInterface IRenderObject
		{
			virtual Material* get_material() = 0;
			virtual MeshPtr get_mesh() = 0;
			virtual void render()
			{
				Material* mat = get_material();
				mat->render(this);
			}
		};

	}
}

#endif // !WATER_RENDER_OBJECT_H
