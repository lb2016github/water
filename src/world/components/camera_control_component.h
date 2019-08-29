#ifndef WATER_CAEMRA_CONTROL_COMPONENT_H
#define WATER_CAEMRA_CONTROL_COMPONENT_H
#include "component.h"

namespace water
{
	namespace world
	{
		class CameraControlComponent : public Component
		{
		public:
			CameraControlComponent();
			CameraControlComponent(GameObject* game_object);
			CameraControlComponent(const CameraControlComponent& comp);
			CameraControlComponent(const CameraControlComponent& comp, GameObject* game_object);
			CameraControlComponent& operator = (const CameraControlComponent& comp);
			virtual ~CameraControlComponent();

			// component info
			static ComponentTag tag;
			static Component* create_component(GameObject*);

		};

	}
}

#endif // !WATER_CAEMRA_CONTROL_COMPONENT_H
