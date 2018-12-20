#include "SubSystems.h"

//NOTE: Make this a singleton class

SubSystems* SubSystems::instance = nullptr;

SubSystems::SubSystems()
{
	initEngineSubSystems();
}

SubSystems::~SubSystems()
{
	//delete instance;
}

SubSystems* SubSystems::getInstance()
{
	if (instance == nullptr)
		instance = new SubSystems();
	return instance;
}

//initializes audio, keyboard and other low level systems
void SubSystems::initEngineSubSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}
