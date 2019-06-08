#include "DisplayService.h"
#include <iostream>
#include "glew.h"

SDL_Window* DisplayService::window = nullptr;

int DisplayService::screenHeight = 600;
int DisplayService::screenWidth = 800;

SDL_Window* DisplayService::getWindowHandle()
{
	return window;
}

void DisplayService::createWindow()
{
	//SDL_INIT_EVERYTIHNG HAS TO BE DONE BEFORE THIS
	window = SDL_CreateWindow("Shayannazia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth , screenHeight, SDL_WINDOW_OPENGL);
	
	if (window == NULL) 
	{
		std::cout << "Could not create openGL window: " << SDL_GetError() << std::endl;
		return;
	}
}

void DisplayService::destroyWindow()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}

void DisplayService::updateWindow()
{
	SDL_UpdateWindowSurface(window);
}