#include "render_component.h"

namespace water
{
	namespace world
	{
		RenderComponent::RenderComponent(GameObject* game_object): Component(game_object)
		{
		}
		RenderComponent::RenderComponent(const RenderComponent& comp, GameObject* game_object): Component(game_object)
		{

		}

		RenderComponent& RenderComponent::operator=(const RenderComponent& comp)
		{
			if (&comp == this) return *this;
			Component::operator=(comp);
			return *this;
		}

		RenderComponent::~RenderComponent()
		{
		}

		RenderComponent* RenderComponent::create_component(GameObject* gameobject)
		{
			return new RenderComponent(gameobject);
		}

		ComponentTag RenderComponent::tag = COMP_RENDER;

		ComponentInfo comp_info(tag, create_component);
	}
}

