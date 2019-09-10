#include "space_object.h"
#include "world/components/transform_component.h"


namespace water
{
	namespace world
	{
		SpaceObjectTpl<>::~SpaceObjectTpl()
		{
			m_children.clear();
		}
		void SpaceObjectTpl<>::set_parent(SpaceObjectPtr space_object)
		{
			m_parent = space_object;
		}
		SpaceObjectPtr SpaceObjectTpl<>::get_parent()
		{
			return m_parent.lock();
		}
		std::set<SpaceObjectPtr>& SpaceObjectTpl<>::get_children()
		{
			return m_children;
		}
		std::set<ComponentTag> SpaceObjectTpl<>::get_comp_tags()
		{
			std::set<ComponentTag> rst;
			rst.insert(COMP_TRANSFORMATION);
			rst.insert(COMP_SCENE_OBJECT);
			return rst;
		}
	}
}