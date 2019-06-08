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
	//initialize a few systems here like render system, animation system and stuff
}

void GameService::update()
{
	SystemManager::updateSystems();
}

void GameService::draw()
{
	SystemManager::drawSystems();
}