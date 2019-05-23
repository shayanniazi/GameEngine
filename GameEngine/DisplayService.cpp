#include "DisplayService.h"

DisplayService* DisplayService::instance = nullptr;
SDL_Window* DisplayService::window = nullptr;
int DisplayService::screenHeight = 600;
int DisplayService::screenWidth = 800;

SDL_Window& DisplayService::getWindowHandle()
{
	return *window;
}

void DisplayService::createWindow()
{
	//SDL_INIT_EVERYTIHNG HAS TO BE DONE BEFORE THIS
	window = SDL_CreateWindow("Shayannazia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DisplayService::screenWidth, DisplayService::screenHeight, SDL_WINDOW_RESIZABLE);
}

void DisplayService::destroyWindow()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}