#include "ComponentManager.h"

ComponentManager::ComponentManager()
{
	componentDatabase.reserve(maxComponentTypes);
}


ComponentManager::~ComponentManager()
{
}