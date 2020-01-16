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
			COMP_SCENE_OBJECT,		// SceneObjectComponent
			COMP_SHADOWMAP,			// ShadowMapComponent
			COMP_ANIMATOR,			// AnimatorComponent
		};
	}
}


#endif // !WATER_COMPONENT_CONST_H
