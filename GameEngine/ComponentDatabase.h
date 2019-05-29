#pragma once
#include "ComponentDatabaseService.h" //obtains access to private members using friend class 'pass'
#include <vector>

//STATIC CLASS
class ComponentDatabase
{
public:
	template<typename componentType>
	static const std::vector<componentType>& getAllComponents()
	{
		return ComponentDatabaseService::getAllComponents<componentType>();
	}

	template<typename componentType>
	static void removeAllComponents() 
	{
		ComponentDatabaseService::removeAllComponents<componentType>();
	}

	//adds component of type componentType to entity
	template<typename componentType>
	static void addComponent(componentType*& component, ECSEntity* entity)
	{
		ComponentDatabaseService::addComponent<componentType>(entity, component);
	}

	//removes component of type componentType from this entity
	template<typename componentType>
	static void removeComponent(ECSEntity* entity)
	{
		ComponentDatabaseService::removeComponent<componentType>(entity);
	}

	//removes all components of type componentType from this entity
	template<typename componentType>
	static void removeComponents(ECSEntity* entity)
	{
		ComponentDatabaseService::removeComponents<componentType>(entity);
	}

	//gets component of type componentType from this entity
	template<typename componentType>
	static componentType* getComponent(ECSEntity* entity)
	{
		return ComponentDatabaseService::getComponent<componentType>(entity);
	}

	//gets all components of type componentType from this entity
	template<typename componentType>
	static std::vector<componentType*>* getComponents(ECSEntity* entity)
	{
		return ComponentDatabaseService::getComponents<componentType>(entity);
	}

};