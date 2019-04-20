#ifndef WATER_COMPONENT_H
#define WATER_COMPONENT_H

#include "math3d/math3d.hpp"
#include <string>
#include <map>


namespace water {

	class GameObject;

	class Component {
	public:
		Component();
		Component(GameObject* game_object);
		Component(const Component& comp);	// ���´��m_game_object
		Component(const Component& comp, GameObject* game_object);
		Component& operator = (const Component& comp);	// ���´��m_game_object
		~Component();

		GameObject* get_game_object();
		void set_game_object(GameObject* game_object);

	protected:
		GameObject * m_game_object;
	};

	typedef Component* (*FUNC_CREATE_COMPONENT)(GameObject*);

	class ComponentFactory {
	public:
		~ComponentFactory() {}
		ComponentFactory(const ComponentFactory&) = delete;
		ComponentFactory operator = (const ComponentFactory&) = delete;
		void register_component(std::string comp_name, FUNC_CREATE_COMPONENT create_func);
		Component* create_component(std::string comp_name, GameObject* game_object);

		static ComponentFactory* instance();

	private:
		ComponentFactory() {}
	private:
		std::map<std::string, FUNC_CREATE_COMPONENT> m_creaters;
		static ComponentFactory m_instance;
	};

}
#endif
