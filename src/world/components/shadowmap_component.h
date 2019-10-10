#ifndef WATER_SHADOWMAP_COMPONENT_H
#define WATER_SHADOWMAP_COMPONENT_H
#include "base_component.h"
#include "math3d/math3d.hpp"
#include "render/render_target.h"
#include "render/texture.h"
#include "render/material.h"

namespace water {
	namespace world
	{
		class SpaceObject;

		class ShadowMapComponent : public BaseComponent
		{
		public:
			ShadowMapComponent(SpaceObject* space_object);
			virtual ShadowMapComponent& operator = (const ShadowMapComponent& trans_comp);

			static const ComponentTag tag = COMP_SHADOWMAP;
		public:
			void render();
			render::TexturePtr get_shadow_map();
			void init(const std::string& mat_path);

		private:
			render::IRenderTargetPtr m_render_target_ptr;
			render::MaterialPtr m_material;
		};
	}
}

// todo register component

#endif
