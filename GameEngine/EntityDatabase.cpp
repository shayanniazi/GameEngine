#include "EntityDatabase.h"
#include "ECSEntity.h"
#include "Game.h"

std::vector<ECSEntity*>* EntityDatabase::entitiesVector = new std::vector<ECSEntity*>();
std::vector<size_t>* EntityDatabase::reusableIDPool = new std::vector<size_t>();
size_t EntityDatabase::IDCounter = 1;

//intialized by CoreEngine in CoreEngine.engineSetup();
void EntityDatabase::initializeStorage()
{
	entitiesVector->reserve(Game::maxEntities);
	reusableIDPool->reserve(1000); 
}

void EntityDatabase::registerEntity(ECSEntity* entity)
{
	//if reusable pool is empty, then generate an ID
	if (reusableIDPool->empty())
	{
		entity->entityID = IDCounter;
		IDCounter++;
	}
	else //if not empty, then retrieve fiset entityID 
	{
		entity->entityID = reusableIDPool->front();
		reusableIDPool->erase(reusableIDPool->begin());
	}

	entitiesVector->push_back(entity);
	std::cout << "Entity '" << entity->getEntityName() << "' with ID: " << entity->getEntityID() << " successfully registered in entity database" << std::endl;

}

void EntityDatabase::deleteEntity(ECSEntity* entity)
{
	//put ID back into reusable ID pool
	reusableIDPool->push_back(entity->entityID);
	
	//delete entity with particular address from database
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entity == entitiesVector->at(i))
		{
			entitiesVector->erase(entitiesVector->begin() + i);
			std::cout << "Entity '" << entity->getEntityName() << "' with ID: " << entity->getEntityID() << " successfully removed from entity database" << std::endl;
			//entity = nullptr;
			break;
		}
	}	
}

ECSEntity* EntityDatabase::getEntity(std::string entityName)
{
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entitiesVector->at(i)->getEntityName() == entityName)
			return entitiesVector->at(i);
	}
	
	std::cout << "Warning, EntityDatabase::getEntity(std::string entityName) returned nullptr as entity with name: " << entityName << " was not found in entity database!" << std::endl;
	return nullptr;
}

ECSEntity* EntityDatabase::getEntity(size_t entityID)
{
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entitiesVector->at(i)->getEntityID() == entityID)
			return entitiesVector->at(i);
	}

	std::cout << "Warning, EntityDatabase::getEntity(std::string entityName) returned nullptr as entity with ID: " << entityID << " was not found in entity database!" << std::endl;
	return nullptr;
}

ECSEntity* EntityDatabase::getEntity(ECSEntity* entity)
{
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entitiesVector->at(i) == entity)
			return entitiesVector->at(i);
	}

	std::cout << "Warning, EntityDatabase::getEntity(std::string entityName) returned nullptr as entity with ID: " << entity->entityID << "and name: " << entity->entityName << " was not found in entity database!" << std::endl;
	return nullptr;
}