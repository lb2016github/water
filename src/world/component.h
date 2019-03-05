#ifndef WATER_COMPONENT_H
#define WATER_COMPONENT_H

#include "math3d/math3d.hpp"
#include "world/game_object.h"
#include <map>


namespace water {

	typedef void* (*FUNC_CREATE_COMPONENT)();

	class Component {
	public:
		Component() = delete;
		Component(GameObject* game_object) : m_game_object(game_object) {}

		GameObject* get_game_object() { return m_game_object; }

	private:
		GameObject * m_game_object;
	public:
		static std::string COMPONENT_NAME = "base_component";
	};

	class ComponentFactory {
	public:
		void register_component(std::string comp_name, FUNC_CREATE_COMPONENT create_func);
		void* create_component(std::string comp_name);

		static ComponentFactory* instance() { return &m_instance; }

	private:
		ComponentFactory() {}
		ComponentFactory(const ComponentFactory& comp_factory)=delete
		ComponentFactory& operater = (const ComponentFactory&)=delete
		~ComponentFactory() {}
	private:
		std::map<std::string, FUNC_CREATE_COMPONENT> m_creaters;
		static ComponentFactory m_instance;
	};

}
#endif
