#ifndef WATER_MODEL_H
#define WATER_MODEL_H

#include "render/render_object.h"
#include "space_object.h"

namespace water
{
	namespace world
	{
		class Model : public SpaceObject, public render::IRenderable
		{
		public:
			// Constructors
			using SpaceObject::GameObject;
			using SpaceObject::SpaceObject;
			using SpaceObject::operator=;

			// implements IRendable
			virtual render::MaterialPtr get_material();
			virtual render::MeshDataPtr get_mesh();
			virtual render::DrawCommand get_draw_command();

			// init from file
			virtual void load_from_file(std::string& filename);
			// render model
			virtual void render();

		protected:
			virtual std::set<ComponentTag> get_comp_tags();
		};
	}
}

#endif // !WATER_MODEL_H
