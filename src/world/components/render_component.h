#ifndef WATER_RENDER_COMPONENT_H
#define WATER_RENDER_COMPONENT_H

#include "component.h"

namespace water
{
	namespace world
	{
		class RenderComponent : public Component
		{
		public:
			RenderComponent() : RenderComponent(nullptr) {};
			RenderComponent(GameObject* game_object);
			RenderComponent(const RenderComponent& comp) : RenderComponent(comp, nullptr) {};
			RenderComponent(const RenderComponent& comp, GameObject* game_object);
			RenderComponent& operator = (const RenderComponent& comp);
			virtual ~RenderComponent() override;

			// component info
			static ComponentTag tag;
			static Component* create_component(GameObject*);
		};

	}
}

#endif // !WATER_RENDER_COMPONENT_H
