#pragma once
#include "space_object.h"
#include "world/components/mesh_component.h"
#include "world/components/material_component.h"
#include "world/components/render_component.h"

namespace water
{
	namespace world
	{
		/*
		SkeletonObject should be binded to a model with animator, and it can draw skeleton bones on run time
		*/
		class SkeletonObject : 
			public SpaceObject, 
			public ComponentObject<MeshComponent, MaterialComponent, RenderComponent>
		{
		public:
			void init();
			virtual void tick(float deltaTimeMic);
		};
	}
}
