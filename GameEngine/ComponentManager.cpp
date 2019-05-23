#include "ComponentManager.h"

ComponentManager* ComponentManager::instance = nullptr;

ComponentManager::ComponentManager()
{
	componentDatabase.reserve(maxComponentTypes);
	garbage.reserve(1000); //reserve an arbitrary amount of memory for 1000 addresses to empty/garbage vectors
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

void ComponentManager::cleanGarbage()
{
	for (size_t i = 0; i < garbage.size(); i++)
		delete (std::vector<Component*>*) garbage.at(i);

	if (!garbage.empty())
		garbage.clear();
}
