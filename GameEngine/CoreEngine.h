#pragma once
#include "SubSystems.h"
#include "Display.h"
//Singleton class

class CoreEngine
{
public:
	//CoreEngine();
	~CoreEngine();
	static CoreEngine* getEngineInstance();
	void run();

private: 
	CoreEngine();
	void engineSetup();
	//gamestate enum here
	static CoreEngine* instance;
	SubSystems* subSystems = nullptr;
	Display* display = nullptr;
};

