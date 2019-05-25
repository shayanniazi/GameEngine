#include "EntityManager.h"
#include "ECSEntity.h"
#include "Game.h"

EntityManager* EntityManager::instance = nullptr;

EntityManager::~EntityManager() {}

EntityManager::EntityManager()
{
	entitiesVector.reserve(Game::maxEntities);
}

EntityManager& EntityManager::getInstance()
{
	if (instance == nullptr)
		instance = new EntityManager();
	return *instance;
}

void EntityManager::createEntity()
{

}

//removes all associated components of entity
void EntityManager::deleteEntity()
{

}

//removes all entities flagged as !isAlive
void EntityManager::cleanUp()
{

}