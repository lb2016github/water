#include "world/component.h"

void water::ComponentFactory::register_component(std::string comp_name, FUNC_CREATE_COMPONENT create_func)
{
	assert(m_creaters.find(comp_name) == m_creaters.end());
	m_creaters[comp_name] = create_func;
}

water::Component* water::ComponentFactory::create_component(std::string comp_name, GameObject* game_object)
{
	assert(m_creaters.find(comp_name) == m_creaters.end());
	FUNC_CREATE_COMPONENT create_func = m_creaters[comp_name];
	return create_func(game_object);
}

water::ComponentFactory* water::ComponentFactory::instance() {
	return &water::ComponentFactory::m_instance;
}

water::Component::Component(): m_game_object(NULL)
{

}

water::Component::Component(const Component& comp, GameObject* game_object)
{
	Component(comp);
	m_game_object = game_object;
}

water::Component::~Component()
{
	m_game_object = NULL;
}

water::GameObject* water::Component::get_game_object()
{
	return m_game_object;
}

void water::Component::set_game_object(GameObject* game_object)
{
	m_game_object = game_object;
}

water::Component& water::Component::operator=(const Component& comp)
{
	if (&comp == this) {
		return *this;
	}
	//m_game_object = comp.m_game_object;
	return *this;
}

water::Component::Component(const Component& comp)
{
	
}

water::Component::Component(GameObject* game_object): m_game_object(game_object)
{
	
}
