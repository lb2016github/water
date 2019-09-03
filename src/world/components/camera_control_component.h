#ifndef WATER_CAEMRA_CONTROL_COMPONENT_H
#define WATER_CAEMRA_CONTROL_COMPONENT_H
#include "component.h"
#include "world/gameobjects/camera.h"

namespace water
{
	namespace world
	{
		class CameraControlComponent : public Component
		{
		public:
			CameraControlComponent(Camera* camera);
			using Component::operator=;
			virtual ~CameraControlComponent();

			// component info
			static ComponentTag tag;
			static Component* create_component(Camera* camera);

		private:
			Camera* camera = { nullptr };
		};

	}
}

#endif // !WATER_CAEMRA_CONTROL_COMPONENT_H
