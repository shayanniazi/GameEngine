#pragma once
#include <vector>
#include "ComponentDatabaseService.h"
#include "Utilities.h"

class ECSEntity
{
public:
	ECSEntity(std::string entityName);
	~ECSEntity();
	size_t getEntityID();
	std::string getEntityName();

	//adds component of type componentType to this entity
	template<typename componentType>
	void addComponent(componentType*& component)
	{
		ComponentDatabaseService::addComponent<componentType>(this, component);
	}

	//removes component of type componentType from this entity
	template<typename componentType>
	void removeComponent()
	{
		ComponentDatabaseService::removeComponent<componentType>(this);
	}

	//removes all components of type componentType from this entity
	template<typename componentType>
	void removeComponents()
	{
		ComponentDatabaseService::removeComponents<componentType>(this);
	}

	//gets component of type componentType from this entity
	template<typename componentType>
	componentType* getComponent()
	{
		return ComponentDatabaseService::getComponent<componentType>(this);
	}

	//gets all components of type componentType from this entity
	template<typename componentType>
	std::vector<componentType*>* getComponents()
	{
		return ComponentDatabaseService::getComponents<componentType>(this);
	}

private:
	friend class ComponentDatabaseService; //so that ComponentDatabaseService can have access to 'components' vector manipulation methods, that are 1) remove. 2) removeAllOfType. 3) insert

	static std::vector<size_t> reusableIDPool;
	static size_t IDCounter;

	std::vector<Component*> components; //storage of all types of components the entity has
	size_t entityID;
	std::string entityName;

	void remove(const Component* comp); //used by componentDatabase to remove components from this entity
	void removeAllOfType(size_t compTypeID); //used by componentDatabase to remove components of certain type from this entity
	void insert(Component* comp); //used by componentDatabase to insert components into this entity
};

