#ifndef WATER_SPACE_OBJECT_H
#define WATER_SPACE_OBJECT_H

#include "game_object.h"
#include "component_object.hpp"
#include "world/components/transform_component.h"
#include "world/components/scene_object_component.h"

namespace water
{
	namespace world
	{
		class SpaceObject;
		DECL_SHARED_PTR(SpaceObject);
		DECL_WEEK_PTR(SpaceObject);

		class SpaceObject : 
			public ComponentObject<SceneObjectComponent, TransformComponent>, 
			public std::enable_shared_from_this<SpaceObject>
		{
		public:
			virtual ~SpaceObject();

		public:
			// set parent and get parent
			void set_parent(SpaceObjectPtr space_object);
			SpaceObjectPtr get_parent();

			// get children
			std::set<SpaceObjectPtr>& get_children();

		protected:
			virtual std::set<ComponentTag> get_comp_tags();

		//====================== Start attributes =============================//
		public:
			// visibility
			bool visible = { true };

		protected:
			SpaceObjectWeekPtr m_parent;		// parent
			std::set<SpaceObjectPtr> m_children;	// childen
			
		};

	}
}

#endif // !WATER_SPACE_OBJECT_H
