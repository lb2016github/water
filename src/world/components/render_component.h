#ifndef WATER_RENDER_COMPONENT_H
#define WATER_RENDER_COMPONENT_H

#include "base_component.h"
#include "render/draw_command.h"
#include "world/gameobjects/space_object.h"
#include "render/render.h"

namespace water
{
	namespace world
	{
		class RenderComponent: public BaseComponent
		{
		public:
			RenderComponent(SpaceObject* space_object);

			using BaseComponent::operator=;

			static const ComponentTag tag = COMP_RENDER;

		public:
			void render(const render::DrawCommand& draw_cmd);
			void render(const render::DrawCommand& draw_cmd, render::MaterialPtr mat_ptr);

		protected:
			SpaceObject * m_space_object;
		};
	}
}

#endif // !WATER_RENDER_COMPONENT_H
