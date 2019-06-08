#include "CoreEngine.h"
#include "HALService.h"
#include "DisplayService.h"
#include "InputService.h"
#include "GameService.h"
#include "ShaderService.h"
#include "GraphicsSetup.h"
#include "Time.h"
#include "Input.h"
#include "KeyCode.h"
#include "ComponentDatabaseService.h" //obtains access to private members using friend class 'pass'
#include <iostream>
#include "glew.h"
#include "SDL.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Mesh.h"
#include "ModelLoader.h"

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

	/////////////////TEMPORARY DRAW CODE 
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	Mesh mesh = ModelLoader::loadOBJ("RandomModel.blend");

	size_t VAO;
	glGenVertexArrays(1, &VAO);
	size_t vbo;
	glGenBuffers(1, &vbo);
	size_t EBO;
	glGenBuffers(1, &EBO);

	//bind VAO before binding anything else
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.positionVertices.size() * 3, &mesh.positionVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.positionIndices.size() * sizeof(size_t), &mesh.positionIndices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	glDrawElements(GL_TRIANGLES, mesh.positionIndices.size(), GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(DisplayService::getWindowHandle()); //swap back and front buffers so that its visible now
	///////////////////CODE END
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
	DisplayService::updateWindow();
	GameService::draw();
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