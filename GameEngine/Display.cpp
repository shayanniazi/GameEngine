#include "Display.h"

Display::Display()
{
	createWindow();
}

Display::~Display()
{
	destroyWindow();
}

void Display::createWindow()
{
	//SDL_INIT_EVERYTIHNG HAS TO BE DONE BEFORE THIS
	window = SDL_CreateWindow("Shayannazia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Display::screenWidth, Display::screenHeight, SDL_WINDOW_RESIZABLE);
}

void Display::destroyWindow()
{
	SDL_DestroyWindow(window);
}