#pragma once
#include <vector>
#include "ComponentManager.h"

class ECSEntity
{
public:
	ECSEntity();
	~ECSEntity();
	void removeEntity(); //puts the entity ID back into reusable pool of ID's
	size_t getEntityID();
	
	template<typename componentType>
	void addComponent(componentType*& component)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		checkValidityOfT<componentType>();

		ComponentManager::getInstance().addComponent<componentType>(entityID, component);
	}

private:
	template<typename T>
	void checkValidityOfT()
	{
		//checking if 'T' is of a valid type (derived from component)
		const bool T_DerivedFromComponent = std::is_base_of<Component, T>::value;
		const bool T_is_Component = std::is_same<T, Component>::value;
		static_assert(T_DerivedFromComponent, "T should be derived from component");
		static_assert(!T_is_Component, "T cannot be base type 'Component'");
	}

	static std::vector<size_t> reusableIDPool;
	static size_t IDCounter;
	size_t entityID;
};

