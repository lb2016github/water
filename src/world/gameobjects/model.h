#ifndef WATER_MODEL_H
#define WATER_MODEL_H

#include "game_object.h"
#include "render/render_object.h"

namespace water
{
	namespace world
	{
		class Model : public GameObject, public render::IRenderObject
		{
		public:
			// Constructors and desconstructor
			Model();
			Model(const Model& model);
			Model& operator = (const Model& model);
			virtual ~Model();

			// methods implement IRenderObject
			virtual render::MaterialPtr get_material();
			virtual render::MeshPtr get_mesh();
		};
	}
}

#endif // !WATER_MODEL_H
