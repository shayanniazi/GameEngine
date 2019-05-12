#pragma once
#include "SubSystems.h"
#include "Display.h"
#include "Input.h"
#include "KeyCode.h"
#include "Time.h"
#include <iostream>

//Singleton class

class CoreEngine
{
public:
	//CoreEngine();
	~CoreEngine();
	static CoreEngine* getEngineInstance();

private: 
	CoreEngine();
	void engineSetup();
	void run();
	void processInput();
	void update();
	void lateUpdate();

	bool isRunning = false;
	double deltaTime;

	static CoreEngine* instance;
	SubSystems* subSystems = nullptr;
	Display* display = nullptr;
	Input* input = nullptr;
	KeyCode* keyCode = nullptr;
};

