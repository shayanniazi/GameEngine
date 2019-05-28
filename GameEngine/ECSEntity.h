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

	template<typename componentType>
	void addComponent(componentType*& component)
	{
		if (ComponentDatabase::getInstance().addComponent<componentType>(entityID, component))
		{
			//if component insertion successful in component manager, then add type data of component into entity for bookkeeping
			components.push_back(component);
		}

	}

	template<typename componentType>
	void removeComponent()
	{
		//1st check if ComponentDatabaseService has the right component in its database and remove it if it does
		if (ComponentDatabase::getInstance().removeComponent<componentType>(entityID))
		{
			size_t typeID = typeid(componentType).hash_code()

			//if component successfully removed from ComponentDatabaseService, then erase from componentTypeVec
			for (size_t i = 0; i < componentTypeVec.size(); i++)
			{
				if (typeid(*components.at(i)).hash_code() == typeID)
				{
					components.erase(components.begin() + i);
					break;
				}
			}
		}
	}

	template<typename componentType>
	void removeComponents()
	{
		//1st check if ComponentDatabaseService has the right component in its database and remove it if it does
		if (ComponentDatabase::getInstance().removeComponents<componentType>(entityID))
		{
			size_t typeID = typeid(componentType).hash_code()

			//if component successfully removed from ComponentDatabaseService, then erase from componentTypeVec
				for (size_t i = 0; i < componentTypeVec.size();)
				{
					if (typeid(*components.at(i)).hash_code() == typeID)
						components.erase(componentTypeVec.begin() + i);
					else
						i++;
				}
		}
	}

private:
	static std::vector<size_t> reusableIDPool;
	static size_t IDCounter;

	std::vector<Component*> components; //storage of all types of components the entity has
	size_t entityID;
	std::string entityName;
};

