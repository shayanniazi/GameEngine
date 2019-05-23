#pragma once
#include "HALService.h"
#include "DisplayService.h"
#include "InputService.h"
#include "Input.h"
#include "KeyCode.h"
#include "Time.h"
#include "ComponentManager.h"
#include <iostream>

//Singleton class

class CoreEngine
{
public:
	~CoreEngine();
	static CoreEngine& getInstance();

private: 
	CoreEngine();
	void engineSetup();
	void gameLoop();
	void processInput();
	void update();
	void lateUpdate();

	bool isRunning = false;
	double deltaTime;

	static CoreEngine* instance;
};

