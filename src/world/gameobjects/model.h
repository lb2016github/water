#ifndef WATER_MODEL_H
#define WATER_MODEL_H

#include "game_object.h"
#include "render/render_object.h"

namespace water
{
	namespace world
	{
		class Model : public GameObject, public render::IRenderable
		{
		public:
			// Constructors and desconstructor
			Model();
			Model(const Model& model);
			Model& operator = (const Model& model);
			virtual ~Model();

			// implements IRendable
			virtual render::MaterialPtr get_material();
			virtual render::MeshDataPtr get_mesh();
			virtual render::DrawCommand get_draw_command();

			// init from file
			virtual void load_from_file(std::string& filename);
		};
	}
}

#endif // !WATER_MODEL_H
