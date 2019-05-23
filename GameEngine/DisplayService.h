#pragma once
#include "SDL.h"

class DisplayService
{
public:
	static SDL_Window& getWindowHandle();
	static void createWindow();
	static void destroyWindow();

private:
	static DisplayService* instance;
	static SDL_Window* window;
	static int screenWidth;
	static int screenHeight;
};

