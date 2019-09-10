#ifndef WATER_COMPONENT_OBJECT_H
#define WATER_COMPONENT_OBJECT_H
#include <map>

		typedef int ComponentTag;

		struct BaseComponent
		{
			static const ComponentTag tag = 1;
		};

		struct A : public BaseComponent
		{
			static const ComponentTag tag = 2;
		};
		struct B : public BaseComponent
		{
			static const ComponentTag tag = 3;
		};

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
			ComponentObject(const ComponentObject& comp_obj)
			{
				// copy components
				for (COMPONENT_MAP::const_iterator iter = comp_obj.m_components.begin(); iter != comp_obj.m_components.end(); ++iter)
				{
					BaseComponent* comp = add_component(iter->first);
					if (comp) {
						*comp = *(iter->second);
					}
				}
			}

			ComponentObject& operator = (const ComponentObject& game_object)
			{
				if (this == &game_object) {
					return *this;
				}
				// copy components
				for (COMPONENT_MAP::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
				{
					COMPONENT_MAP::const_iterator find_iter = game_object.m_components.find(iter->first);
					if (find_iter != game_object.m_components.end())
					{
						*(iter->second) = *(find_iter->second);
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
			BaseComponent* get_component(ComponentTag comp)
			{
				COMPONENT_MAP::iterator iter = m_components.find(comp);
				if (iter == m_components.end()) {
					return NULL;
				}
				return iter->second;
			}
			BaseComponent* add_component(ComponentTag comp_tag)
			{
				auto rst = m_components.find(comp_tag);
				if (rst != m_components.end()) {
					return rst->second;
				}
				return nullptr;
			}
		protected:
			COMPONENT_MAP m_components;
		};


#endif // !WATER_COMPONENT_OBJECT_H
