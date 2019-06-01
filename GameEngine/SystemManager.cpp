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
	for (size_t i = 0; i < systemsVector->size(); i++)
	{
		if (systemsVector->at(i) == system)
		{
			std::cout << "System " << typeid(*system).name() << " of same address already exists in system database" << std::endl;
			return;
		}
	}

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
	std::cout << "System " << typeid(*system).name() << " could not be removed, as it was not in system database" << std::endl;

}

//Called by GameService::udpate()
void SystemManager::updateSystems()
{
	for (size_t i = 0; i < systemsVector->size(); i++)
		systemsVector->at(i)->update();
}