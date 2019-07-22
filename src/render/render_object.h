#ifndef WATER_RENDER_OBJECT_H
#define WATER_RENDER_OBJECT_H
#include "common/common.h"
#include <memory>
#include "render/render.h"
#include "render/material.h"

namespace water
{
	namespace render
	{

		WaterInterface IMesh
		{
			virtual void render() = 0;
		};


		WaterInterface IRenderObject
		{
			virtual MaterialPtr get_material() = 0;
			virtual MeshPtr get_mesh() = 0;
			virtual void render()
			{
				MaterialPtr mat = get_material();
				mat->render(this);
			}
		};

	}
}

#endif // !WATER_RENDER_OBJECT_H
