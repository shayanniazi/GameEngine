#include <iostream>
#include "SystemManager.h"
#include "System.h"

std::vector<System*>* SystemManager::systemsVector = new std::vector<System*>();

//CoreEngine.engineSetup() to call this function
void SystemManager::initializeStorage()
{
	systemsVector->reserve(100);
}

//Called by GameService::udpate()
void SystemManager::updateSystems()
{
	for (size_t i = 0; i < systemsVector->size(); i++)
		systemsVector->at(i)->update();
}

void SystemManager::drawSystems()
{
	for (size_t i = 0; i < systemsVector->size(); i++)
		systemsVector->at(i)->draw();
}