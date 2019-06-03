#include "GameService.h"
#include "Game.h"
#include "SystemManager.h"
#include "ComponentDatabaseService.h"
#include "EntityDatabase.h"

void GameService::init()
{
	ComponentDatabaseService::initializeStorage();
	EntityDatabase::initializeStorage();
	SystemManager::initializeStorage();
	Game::init();
}

void GameService::update()
{
	SystemManager::updateSystems();
}