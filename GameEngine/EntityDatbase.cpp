#include "EntityDatbase.h"
#include "ECSEntity.h"
#include "Game.h"

EntityDatbase* EntityDatbase::instance = nullptr;

EntityDatbase::~EntityDatbase() {}

EntityDatbase::EntityDatbase()
{
	entitiesVector.reserve(Game::maxEntities);
}

EntityDatbase& EntityDatbase::getInstance()
{
	if (instance == nullptr)
		instance = new EntityDatbase();
	return *instance;
}

void EntityDatbase::registerEntity(ECSEntity* entity)
{
	for (size_t i = 0; i < entitiesVector.size(); i++)
	{
		if (entity == entitiesVector.at(i))
		{
			std::cout << "cannot reinsert entity with ID: " << entity->getEntityID() << " as its already registered in database" << std::endl;
			return;
		}
	}

	entitiesVector.push_back(entity);
	std::cout << "Entity with ID: " << entity->getEntityID() << " successfully registered in database" << std::endl;

}

void EntityDatbase::deleteEntity(ECSEntity* entity)
{
	for (size_t i = 0; i < entitiesVector.size(); i++)
	{
		if (entity == entitiesVector.at(i))
		{
			entitiesVector.erase(entitiesVector.begin() + i);
			std::cout << "Entity with ID: " << entity->getEntityID() << " successfully removed from database" << std::endl;
			break;
		}
	}	
}

//removes all entities flagged as !isAlive
void EntityDatbase::cleanUp()
{

}