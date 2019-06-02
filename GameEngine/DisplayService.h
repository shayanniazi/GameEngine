#pragma once
#include "SDL.h"

class DisplayService
{
public:
	static SDL_Window& getWindowHandle();
	static void createWindow();
	static void destroyWindow();
	static void updateWindow();

private:
	static SDL_Window* window;
	static int screenWidth;
	static int screenHeight;
};

