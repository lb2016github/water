#include "camera_control_component.h"

namespace water
{
	namespace world
	{
		CameraControlComponent::CameraControlComponent(Camera * camera): Component(camera), camera(camera)
		{
		}
		CameraControlComponent::~CameraControlComponent()
		{
			camera = nullptr;
		}
		Component * CameraControlComponent::create_component(Camera * camera)
		{
			return new CameraControlComponent(camera);
		}
	}
}