#include "ComponentManager.h"

ComponentManager* ComponentManager::instance = nullptr;

ComponentManager::ComponentManager()
{
	componentDatabase.reserve(maxComponentTypes);
}


ComponentManager::~ComponentManager()
{
}

ComponentManager& ComponentManager::getInstance()
{
	if (instance == nullptr)
		instance = new ComponentManager();

	return *instance;
}