#include "CoreEngine.h"

CoreEngine* CoreEngine::instance = nullptr;

CoreEngine::CoreEngine()
{
	engineSetup();
	gameLoop(); //gameloop
}

CoreEngine::~CoreEngine()
{
	instance = nullptr;
}

CoreEngine& CoreEngine::getInstance()
{
	if (instance == nullptr)
		instance = new CoreEngine();	
	
	return *instance;
}

void CoreEngine::engineSetup()
{
	HALService::initEngineSubSystems(); //set up SDL and shit (sub systems have to be initialized before window is created)
	DisplayService::createWindow(); //create and setup SDL Window
	InputService::initInputStates(); //initializes keyboard and mouse states
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
		}
	}

	InputService::updateInput();
}

void CoreEngine::update()
{
	if(Input::isKeyHeld(KeyCode::T))
		std::cout << "Pressing T" << std::endl;
	if (Input::isKeyPressed(KeyCode::F))
		std::cout << "Pressing F" << std::endl;
	if (Input::isMouseButtonHeld(KeyCode::rightMouse))
		std::cout << "Pressing right mouse" << std::endl;
}

void CoreEngine::lateUpdate()
{
	InputService::updatePrevInput();
	ComponentManager::getInstance().cleanGarbage();
}

void CoreEngine::gameLoop()
{
	double prevTime = Time::getTime();
	double elapsedTime = 0;
	double deltaAccumulator = 0;
	double frameCap = (double) 1 / (double) 60;
	int ticks = 0;

	while (isRunning) 
	{
		double currentTime = Time::getTime();
		deltaTime = currentTime - prevTime;
		elapsedTime += deltaTime;
		deltaAccumulator += deltaTime;

		processInput();
		update();
		lateUpdate();
		//render();

		while (deltaAccumulator >= frameCap)
		{
			ticks++;
			deltaAccumulator -= frameCap;
		}

		//print out # of frames passed after time >= 1s
		if (elapsedTime >= 1)
		{
			elapsedTime = 0;
			std::cout << ticks << " frame rate" << std::endl;
			ticks = 0;
		}

		prevTime = currentTime;
	}
}