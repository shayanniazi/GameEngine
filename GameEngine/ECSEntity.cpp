#include "ECSEntity.h"
#include "Game.h"
#include "EntityDatbase.h"

size_t ECSEntity::IDCounter = 1;
std::vector<size_t> ECSEntity::reusableIDPool({}); //initialized to empty vector '{ }'

ECSEntity::ECSEntity(std::string entityName)
{
	components.reserve(100);

	//if reusable pool is empty, then generate an ID
	if (reusableIDPool.empty())
	{
		entityID = IDCounter;
		IDCounter++;
	}
	else //if not empty, then retrieve fiset entityID 
	{
		entityID = reusableIDPool.front();
		reusableIDPool.erase(reusableIDPool.begin());
	}
}

ECSEntity::~ECSEntity()
{
	//put ID back into reusable ID pool
	reusableIDPool.push_back(entityID);

	//flag every component attached to this entity to be 0 (i.e to be deleted)
	for (size_t i = 0; i < components.size(); i++)
		components.at(i)->entityID = 0;

	std::cout << "Entity with ID: " << entityID << " successfully tagged for removal " << std::endl;
}

size_t ECSEntity::getEntityID()
{
	return entityID;
}

std::string ECSEntity::getEntityName()
{
	return entityName;
}
