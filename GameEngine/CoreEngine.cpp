#include "CoreEngine.h"

CoreEngine* CoreEngine::instance = nullptr;

CoreEngine::CoreEngine()
{
	engineSetup();
	run(); //gameloop
}

CoreEngine::~CoreEngine()
{
	delete subSystems;
	delete display;
	delete input;
	keyCode->cleanUp(); //deletes all keycodes in memory
	delete keyCode;
	//delete subSystems;
	//delete display;
	subSystems, display, input, keyCode, instance = nullptr;
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
	keyCode = KeyCode::getInstance(); //master control, controls all other keycodes in mem
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

	input->updateInput();
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
	input->updatePrevInput();
}

void CoreEngine::run()
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

		if (elapsedTime >= 1)
		{
			elapsedTime = 0;
			std::cout << ticks << " frame rate" << std::endl;
			ticks = 0;
		}

		prevTime = currentTime;
	}
}