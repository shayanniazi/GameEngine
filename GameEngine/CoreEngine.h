#pragma once

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
	void render();

	bool isRunning = false;
	double deltaTime;

	static CoreEngine* instance;
};

