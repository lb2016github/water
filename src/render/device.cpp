#include "device.h"
#include "render/opengl/device_opengl.h"

namespace water
{
	namespace render
	{

		static DeviceBase* device = nullptr;

		DeviceBase* get_device()
		{
			if (device != nullptr) return device;
			switch (cur_device)
			{
			case DeviceTypeOpenGL:
				device = new DeviceOpenGL();
			default:
				device = new DeviceOpenGL();
			}
			return device;
		}
	}
}