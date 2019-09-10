#ifndef WATER_SPACE_OBJECT_H
#define WATER_SPACE_OBJECT_H

#include "game_object.h"
#include "component_object.hpp"
#include "world/components/transform_component.h"
#include "world/components/scene_object_component.h"
#include <memory>

namespace water
{
	namespace world
	{
		class SpaceObject: 
			public ComponentObject<SceneObjectComponent, TransformComponent>, 
			public std::enable_shared_from_this<SpaceObject>
		{
		public:
			virtual ~SpaceObject();

		public:
			// set parent and get parent
			void set_parent(std::shared_ptr<SpaceObject> space_object);
			std::shared_ptr<SpaceObject> get_parent();

			// get children
			std::set<std::shared_ptr<SpaceObject>>& get_children();

		protected:
			virtual std::set<ComponentTag> get_comp_tags();

		//====================== Start attributes =============================//
		public:
			// visibility
			bool visible = { true };

		protected:
			std::weak_ptr<SpaceObject> m_parent;		// parent
			std::set<std::shared_ptr<SpaceObject>> m_children;	// childen
			
		};

		DECL_SHARED_PTR(SpaceObject)
		DECL_WEEK_PTR(SpaceObject)

	}
}

#endif // !WATER_SPACE_OBJECT_H
