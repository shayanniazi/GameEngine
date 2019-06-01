#include "GameService.h"
#include "Game.h"
#include "SystemManager.h"

void GameService::init()
{
	Game::init();
}

void GameService::update()
{
	SystemManager::updateSystems();
}