#ifndef WATER_SPACE_OBJECT_H
#define WATER_SPACE_OBJECT_H

#include "game_object.h"

namespace water
{
	namespace world
	{
		class SpaceObject;
		DECL_SHARED_PTR(SpaceObject);
		DECL_WEEK_PTR(SpaceObject);

		class SpaceObject : public GameObject
		{
		public:
			using GameObject::GameObject;
			using GameObject::operator=;
			virtual ~SpaceObject();

		public:
			// set parent and get parent
			void set_parent(SpaceObject* space_object);
			SpaceObject* get_parent();

			// get children
			std::set<SpaceObjectPtr>& get_children();

		protected:
			virtual std::set<ComponentTag> get_comp_tags();

		//====================== Start attributes =============================//
		public:
			// visibility
			bool visible = { true };

		protected:
			SpaceObject * m_parent{ nullptr };		// parent
			std::set<SpaceObjectPtr> m_children;	// childen
			
		};


	}
}

#endif // !WATER_SPACE_OBJECT_H
