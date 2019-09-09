#ifndef WATER_GAME_OBJECT_H
#define WATER_GAME_OBJECT_H

#include "world/components/component_const.h"
#include "common/common.h"
#include <map>
#include <string>
#include <set>
#include <memory>
#include "component_object.hpp"

#define GET_COMPONENT(obj_ptr, cls) ((cls*)(obj_ptr)->get_component(cls::tag))

namespace water {
	namespace world
	{
		typedef ComponentObject<> GameObject;

		DECL_SHARED_PTR(GameObject);
		DECL_WEEK_PTR(GameObject);
	}
}
#endif
