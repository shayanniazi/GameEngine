#include "ComponentManager.h"

ComponentManager::ComponentManager()
{
	componentDatabase.reserve(maxComponentTypes);
	pointerDatabase.reserve(maxComponentTypes);
}


ComponentManager::~ComponentManager()
{
}