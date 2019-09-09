#include "camera_control_component.h"
#include "world/gameobjects/camera.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(CameraControlComponent, Camera)

		CameraControlComponent::CameraControlComponent(Camera * camera): BaseComponent(camera), camera(camera)
		{
		}
		CameraControlComponent::~CameraControlComponent()
		{
			camera = nullptr;
		}
	}
}