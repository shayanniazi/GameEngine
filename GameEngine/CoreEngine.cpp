#include "CoreEngine.h"

CoreEngine* CoreEngine::instance = nullptr;

CoreEngine::CoreEngine()
{
	engineSetup();
	run(); //gameloop
}

CoreEngine::~CoreEngine()
{
	subSystems->~SubSystems();
	display->~Display();
	input->~Input();
	//delete subSystems;
	//delete display;
	subSystems, display, input, instance = nullptr;
}

CoreEngine* CoreEngine::getEngineInstance()
{
	if (instance == nullptr)
		instance = new CoreEngine();	
	
	return instance;
}

void CoreEngine::engineSetup()
{
	subSystems = SubSystems::getInstance(); //set up SDL and shit
	display = Display::getInstance(); //create and get the only instance of display that will exist
	input = Input::getInstance();
	isRunning = true;
}

void CoreEngine::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYUP:
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_MOUSEMOTION:
			break;
		default:
			break;
		}
	}

	input->updateKeyboardState();
}

void CoreEngine::update()
{
	if (Input::isKeyPressed(SDL_SCANCODE_Z))
		std::cout << "Pressing z" << std::endl;
}

void CoreEngine::run()
{
	while (isRunning) 
	{
		processInput();
		update();
		//render();
		input->updatePrevKeyboardState();
	}
}