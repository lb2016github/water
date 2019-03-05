#ifndef WATER_SPACE_OBJECT_H
#define WATER_SPACE_OBJECT_H

#include "math3d/math3d.hpp"
#include "world/component.h"
#include <map>

namespace water {
	class GameObject {
	public:
		GameObject() {}
		~GameObject() {}

		Component* get_component(std::string comp_name);

	protected:
		bool add_component(std::string comp_name);

	public:
		GameObject * m_parent;		// parent
	private:
		std::map<std::string, Component*> m_components;
	};

}
#endif
