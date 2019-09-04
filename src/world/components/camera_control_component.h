#ifndef WATER_CAEMRA_CONTROL_COMPONENT_H
#define WATER_CAEMRA_CONTROL_COMPONENT_H
#include "base_component.h"
#include "world/gameobjects/camera.h"

namespace water
{
	namespace world
	{
		class CameraControlComponent : public BaseComponent
		{
		public:
			CameraControlComponent(Camera* camera);
			using BaseComponent::operator=;
			virtual ~CameraControlComponent();

			static const ComponentTag tag = COMP_CAMERA_CONTROLLER;

		private:
			Camera* camera = { nullptr };
		};

	}
}

#endif // !WATER_CAEMRA_CONTROL_COMPONENT_H
