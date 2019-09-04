#include "world.h"

namespace water
{
	namespace world
	{
		World::World(): GameObject()
		{
		}
		std::set<ComponentTag> World::get_comp_tags()
		{
			// todo
			return std::set<ComponentTag>();
		}
	}
}