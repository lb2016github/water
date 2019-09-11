#ifndef WATER_COMPONENT_OBJECT_H
#define WATER_COMPONENT_OBJECT_H
#include "world/components/base_component.h"

namespace water
{
	namespace world
	{
		typedef std::map<ComponentTag, BaseComponent*> COMPONENT_MAP;

		template<typename ...Comps>
		struct ComponentObject;

		template<typename Comp, typename ...Comps>
		struct ComponentObject<Comp, Comps...>: public ComponentObject<Comps...>
		{
			ComponentObject<Comp, Comps...>() : ComponentObject<Comps...>()
			{
				add_component(Comp::tag);
			}
		};

		template<>
		struct ComponentObject<>
		{
			ComponentObject() {}
			// copy constructor is deleted. as components cannot be initialized in construtor.
			ComponentObject(const ComponentObject& comp_obj) = delete;

			ComponentObject& operator = (const ComponentObject& comp_obj)
			{
				if (this == &comp_obj) {
					return *this;
				}

				// copy components
				for (COMPONENT_MAP::const_iterator iter = comp_obj.m_components.begin(); iter != comp_obj.m_components.end(); ++iter)
				{
					auto rst = m_components.find(iter->first);
					// not component
					if(rst == m_components.end() || rst->second == nullptr)
					{
						auto comp_ptr = create_component(iter->first, this);
						*comp_ptr = *(iter->second);
						m_components[iter->first] = comp_ptr;
					}
					// found
					else
					{
						*(iter->second) = *(iter->second);
					}
				}
				return *this;
			}
			virtual ~ComponentObject()
			{
				for (COMPONENT_MAP::iterator iter = m_components.begin(); iter != m_components.end(); ++iter) {
					delete iter->second;
				}
				m_components.clear();
			}
			BaseComponent* get_component(ComponentTag comp_tag)
			{
				COMPONENT_MAP::iterator iter = m_components.find(comp_tag);
				if (iter == m_components.end()) {
					return nullptr;
				}
				// component has created
				if (iter->second)
				{
					return iter->second;
				}
				else
				{
					// component is not created
					BaseComponent* comp = create_component(comp_tag, this);
					m_components[comp_tag] = comp;
					return comp;
				}
			}
			void add_component(ComponentTag comp_tag)
			{
				auto rst = m_components.find(comp_tag);
				if (rst == m_components.end()) {
					m_components[comp_tag] = nullptr;
				}
				
			}
		protected:
			COMPONENT_MAP m_components;
		};

		template<typename Comp>
		struct ComponentObject<Comp>: virtual public ComponentObject<>
		{
			ComponentObject<Comp>() : ComponentObject<>()
			{
				add_component(Comp::tag);
			}
		};
	}
}

#endif // !WATER_COMPONENT_OBJECT_H
