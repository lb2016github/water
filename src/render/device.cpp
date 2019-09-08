#include "device.h"
#include "render/opengl/device_opengl.h"

namespace water
{
	namespace render
	{

		static DeviceBase* device = nullptr;
		DeviceType cur_device = DeviceTypeOpenGL;

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
		void set_device(DeviceType dy)
		{
			cur_device = dy;
		}
	}
}