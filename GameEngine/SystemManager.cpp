#include <iostream>
#include "SystemManager.h"
#include "System.h"

std::vector<System*>* SystemManager::systemsVector = new std::vector<System*>();

//CoreEngine.engineSetup() to call this function
void SystemManager::initializeStorage()
{
	systemsVector->reserve(100);
}

void SystemManager::registerSystem(System* system)
{
	systemsVector->push_back(system);
	std::cout << "System " << typeid(*system).name() << " successfully registered into system database" << std::endl;
}

void SystemManager::removeSystem(System* system)
{
	for (size_t i = 0; i < systemsVector->size(); i++)
	{
		//if both pointing to same location
		if (systemsVector->at(i) == system)
		{
			systemsVector->erase(systemsVector->begin() + i);
			std::cout << "System " << typeid(*system).name() << " successfully removed from system database" << std::endl;
			return;
		}
	}
}

//Called by GameService::udpate()
void SystemManager::updateSystems()
{
	for (size_t i = 0; i < systemsVector->size(); i++)
		systemsVector->at(i)->update();
}