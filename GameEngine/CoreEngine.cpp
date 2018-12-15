#include "CoreEngine.h"

CoreEngine* CoreEngine::instance = nullptr;

CoreEngine::CoreEngine()
{
	engineSetup();
	run(); //gameloop
}

CoreEngine::~CoreEngine()
{
	delete subSystems, display, instance;
	subSystems, display, instance = nullptr;
}

CoreEngine* CoreEngine::getEngineInstance()
{
	if (instance == nullptr)
		instance = new CoreEngine();	
	
	return instance;
}

void CoreEngine::engineSetup()
{
	subSystems = SubSystems::getSubSystems(); //set up SDL and shit
	display = Display::getDisplay(); //create and get the only instance of display that will exist
}

void CoreEngine::run()
{
	//while(isPlaying){ input(); logic(); render(); }
}