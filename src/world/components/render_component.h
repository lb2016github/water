#ifndef WATER_RENDER_COMPONENT_H
#define WATER_RENDER_COMPONENT_H

#include "base_component.h"
#include "render/draw_command.h"

namespace water
{
	namespace world
	{
		class RenderComponent: public BaseComponent
		{
		public:
			using BaseComponent::BaseComponent;
			using BaseComponent::operator=;

			static const ComponentTag tag = COMP_RENDER;

		public:
			void render(const render::DrawCommand& draw_cmd);

		protected:
			void do_render(const render::DrawCommand& draw_cmd, GameObject* game_object);


		};
	}
}

#endif // !WATER_RENDER_COMPONENT_H
