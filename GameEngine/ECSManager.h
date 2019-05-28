#pragma once

class ECSManager
{
public:

	void createEntity(); //generates and returns new entity ID
	 void deleteEntity(); //removes all components associated with entity as well

	template<typename fucker>
	void bich();

	template<typename componentType>
	void addComponent(componentType*& component)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		if (ComponentManager::getInstance().addComponent<componentType>(entityID, component))
		{
			//if component insertion successful in component manager, then add type data of component into entity for bookkeeping
			componentTypeVec.push_back(typeid(componentType).hash_code());
		}

	}

	template<typename componentType>
	void removeComponent()
	{
		Utilities::isChildOf<componentType, Component>();

		//1st check if ComponentManager has the right component in its database and remove it if it does
		if (ComponentManager::getInstance().removeComponent<componentType>(entityID))
		{
			size_t typeID = typeid(componentType).hash_code()

				//if component successfully removed from ComponentManager, then erase from componentTypeVec
				for (size_t i = 0; i < componentTypeVec.size(); i++)
				{
					if (componentTypeVec.at(i) == typeID)
					{
						componentTypeVec.erase(componentTypeVec.begin() + i);
						break;
					}
				}
		}
	}

	template<typename componentType>
	void removeComponents()
	{
		Utilities::isChildOf<componentType, Component>();

		//1st check if ComponentManager has the right component in its database and remove it if it does
		if (ComponentManager::getInstance().removeComponents<componentType>(entityID))
		{
			size_t typeID = typeid(componentType).hash_code()

				//if component successfully removed from ComponentManager, then erase from componentTypeVec
				for (size_t i = 0; i < componentTypeVec.size(); i++)
					if (componentTypeVec.at(i) == typeID)
						componentTypeVec.erase(componentTypeVec.begin() + i);
		}
	}

};