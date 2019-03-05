#include "world/component.h"

void water::ComponentFactory::register_component(std::string comp_name, FUNC_CREATE_COMPONENT create_func)
{
	this->m_creaters[comp_name] = create_func;
}
