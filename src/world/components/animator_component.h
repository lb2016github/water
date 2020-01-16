#ifndef WATER_ANIMATOR_COMPONENT_H
#define WATER_ANIMATOR_COMPONENT_H

#include "base_component.h"
#include <string>
#include "render/render_const.h"

namespace water
{
	namespace world
	{
		class AnimatorComponent : public BaseComponent
		{
		public:
			using BaseComponent::BaseComponent;

			static const ComponentTag tag = COMP_MESH;
		};
	}
}

#endif // !WATER_ANIMATOR_COMPONENT_H
