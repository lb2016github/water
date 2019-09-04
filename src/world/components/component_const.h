#ifndef WATER_COMPONENT_CONST_H
#define WATER_COMPONENT_CONST_H


namespace water
{
	namespace world
	{
		enum ComponentTag {
			COMP_TRANSFORMATION,	// transform_component
			COMP_MESH,				// MeshComponent
			COMP_MATERIAL,			// MaterialComponent
			COMP_CAMERA_CONTROLLER,	// CameraControlComponent
			COMP_RENDER,			// RenderComponent
		};
	}
}


#endif // !WATER_COMPONENT_CONST_H
