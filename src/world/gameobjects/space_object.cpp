#include "space_object.h"


namespace water
{
	namespace world
	{
		SpaceObject::SpaceObject(SpaceObject * parent): m_parent(parent)
		{
		}
		SpaceObject::~SpaceObject()
		{
			m_parent = nullptr;
		}
		SpaceObject & SpaceObject::operator=(const SpaceObject & game_object)
		{
			if (this == &game_object) return *this;
			GameObject::operator=(game_object);
			m_parent = game_object.m_parent;
			return *this;
		}
		void SpaceObject::set_parent(SpaceObject * space_object)
		{
			m_parent = space_object;
		}
		SpaceObject * SpaceObject::get_parent()
		{
			return m_parent;
		}
		std::set<ComponentTag> SpaceObject::get_comp_tags()
		{
			std::set<ComponentTag> rst;
			rst.insert(COMP_TRANSFORMATION);
		}
	}
}