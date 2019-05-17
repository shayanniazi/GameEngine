#include "ECSEntity.h"

size_t ECSEntity::IDCounter = 0;
std::vector<size_t> ECSEntity::reusableIDPool({}); //initialized to empty vector '{ }'

ECSEntity::ECSEntity()
{
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

}

void ECSEntity::removeEntity()
{
	//put ID back into reusable ID pool
	reusableIDPool.push_back(entityID);
}

size_t ECSEntity::getEntityID()
{
	return entityID;
}
