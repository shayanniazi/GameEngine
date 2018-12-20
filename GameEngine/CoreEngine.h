#pragma once
#include "SubSystems.h"
#include "Display.h"
#include "Input.h"
#include <iostream>

//Singleton class

class CoreEngine
{
public:
	//CoreEngine();
	~CoreEngine();
	static CoreEngine* getEngineInstance();
	void run();
	void processInput();
	void update();

private: 
	CoreEngine();
	void engineSetup();
	bool isRunning = false;
	static CoreEngine* instance;
	SubSystems* subSystems = nullptr;
	Display* display = nullptr;
	Input* input = nullptr;
};

