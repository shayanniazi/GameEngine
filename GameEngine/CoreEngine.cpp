#include "CoreEngine.h"
#include "HALService.h"
#include "DisplayService.h"
#include "InputService.h"
#include "GameService.h"
#include "ShaderService.h"
#include "GraphicsSetup.h"
#include "RenderingService.h"
#include "ComponentDatabaseService.h" //obtains access to private members using friend class 'pass'
#include "Time.h"
#include "Input.h"
#include "KeyCode.h"
#include <iostream>
#include "glew.h"
#include "SDL.h"
#include "Camera.h"

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
	GraphicsSetup::initOpenGL(DisplayService::getWindowHandle(), 4.5); //init opengl and set rendering context to displays window handle
	ShaderService::create("basic.vertex", "basic.fragment");
	InputService::initInputStates(); //initializes keyboard and mouse states
	GameService::init(); //initialize game state as well as allocate storages for ECS management classes (ComponentDatabaseService, EntityDatabase, SystemManager)
	isRunning = true;
	RenderingService::useWireframeMode();
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
	Camera::activeCamera->update();

	if (Input::isKeyHeld(KeyCode::T))
		std::cout << "Pressing T" << std::endl;
	if (Input::isKeyPressed(KeyCode::F))
		std::cout << "Pressing F" << std::endl;
	if (Input::isMouseButtonHeld(KeyCode::rightMouse))
		std::cout << "Pressing right mouse" << std::endl;

	GameService::update();
}

void CoreEngine::lateUpdate()
{
	InputService::updatePrevInput();
	ComponentDatabaseService::cleanGarbage();
	ComponentDatabaseService::removeDeadComponents = false;
}

void CoreEngine::render()
{
	//clear gl buffer bits before drawing all meshes
	RenderingService::clearBufferBits();

	DisplayService::updateWindow();
	GameService::draw();

	//make back buffer active buffer
	RenderingService::swapBuffers();
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
		deltaTime = currentTime - prevTime; Time::setDeltaTime(deltaTime);
		elapsedTime += deltaTime;
		deltaAccumulator += deltaTime;

		processInput();
		update();
		lateUpdate();
		render();

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