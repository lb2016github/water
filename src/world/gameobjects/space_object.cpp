#include "space_object.h"
#include "world/components/transform_component.h"


namespace water
{
	namespace world
	{
		SpaceObject::~SpaceObject()
		{
			m_children.clear();
		}
		void SpaceObject::set_parent(SpaceObjectPtr space_object)
		{
			m_parent = space_object;
		}
		SpaceObjectPtr SpaceObject::get_parent()
		{
			return m_parent.lock();
		}
		std::set<SpaceObjectPtr>& SpaceObject::get_children()
		{
			return m_children;
		}
		std::set<ComponentTag> SpaceObject::get_comp_tags()
		{
			std::set<ComponentTag> rst;
			rst.insert(COMP_TRANSFORMATION);
			rst.insert(COMP_SCENE_OBJECT);
			return rst;
		}
	}
}