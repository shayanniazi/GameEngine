#include "EntityDatbase.h"
#include "ECSEntity.h"
#include "Game.h"

std::vector<ECSEntity*>* EntityDatbase::entitiesVector = new std::vector<ECSEntity*>();

//intialized by CoreEngine in CoreEngine.engineSetup();
void EntityDatbase::initializeStorage()
{
	entitiesVector->reserve(Game::maxEntities);
}

void EntityDatbase::registerEntity(ECSEntity* entity)
{
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entity == entitiesVector->at(i))
		{
			std::cout << "cannot reinsert entity with ID: " << entity->getEntityID() << " as its already registered in database" << std::endl;
			return;
		}
	}

	entitiesVector->push_back(entity);
	std::cout << "Entity '" << entity->getEntityName() << "' with ID: " << entity->getEntityID() << " successfully registered in entity database" << std::endl;

}

void EntityDatbase::deleteEntity(ECSEntity* entity)
{
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entity == entitiesVector->at(i))
		{
			entitiesVector->erase(entitiesVector->begin() + i);
			std::cout << "Entity '" << entity->getEntityName() << "' with ID: " << entity->getEntityID() << " successfully removed from entity database" << std::endl;
			break;
		}
	}	
}

ECSEntity* EntityDatbase::getEntity(std::string entityName)
{
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entitiesVector->at(i)->getEntityName() == entityName)
			return entitiesVector->at(i);
	}
	
	std::cout << "Warning, EntityDatabase::getEntity(std::string entityName) returned nullptr as entity with name: " << entityName << " was not found in entity database!" << std::endl;
	return nullptr;
}

ECSEntity* EntityDatbase::getEntity(size_t entityID)
{
	for (size_t i = 0; i < entitiesVector->size(); i++)
	{
		if (entitiesVector->at(i)->getEntityID() == entityID)
			return entitiesVector->at(i);
	}

	std::cout << "Warning, EntityDatabase::getEntity(std::string entityName) returned nullptr as entity with ID: " << entityID << " was not found in entity database!" << std::endl;
	return nullptr;
}

//removes all entities flagged as !isAlive
void EntityDatbase::cleanUp()
{

}