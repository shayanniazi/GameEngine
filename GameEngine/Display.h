#pragma once
#include "SDL.h"

class Display
{
public:
	~Display();
	static Display* getInstance();
	SDL_Window* getWindowHandle();

private:
	Display();
	static Display* instance;
	SDL_Window* window = nullptr;
	int screenWidth = 800;
	int screenHeight = 600;

	void createWindow();
	void destroyWindow();
};

