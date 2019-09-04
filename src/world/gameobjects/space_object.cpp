#include "space_object.h"


namespace water
{
	namespace world
	{
		SpaceObject::~SpaceObject()
		{
			m_parent = nullptr;
			m_children.clear();
		}
		void SpaceObject::set_parent(SpaceObject * space_object)
		{
			m_parent = space_object;
		}
		SpaceObject * SpaceObject::get_parent()
		{
			return m_parent;
		}
		std::set<SpaceObjectPtr>& SpaceObject::get_children()
		{
			return m_children;
		}
		std::set<ComponentTag> SpaceObject::get_comp_tags()
		{
			std::set<ComponentTag> rst;
			rst.insert(COMP_TRANSFORMATION);
			return rst;
		}
	}
}