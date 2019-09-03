#include "camera_control_component.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(COMP_CAMERA_CONTROLLER, CameraControlComponent, Camera)

		CameraControlComponent::CameraControlComponent(Camera * camera): BaseComponent(camera), camera(camera)
		{
		}
		CameraControlComponent::~CameraControlComponent()
		{
			camera = nullptr;
		}
	}
}