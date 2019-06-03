#include "DisplayService.h"
#include <iostream>
#include "glew.h"

SDL_Window* DisplayService::window = nullptr;
SDL_GLContext DisplayService::renderingContext = nullptr;

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

	//set rendering context
	renderingContext = SDL_GL_CreateContext(window);

	if (renderingContext == NULL)
	{
		std::cout << "Error in setting openGL rendering context: " << SDL_GetError() << std::endl;
		return;
	}

	glClearColor(0.0, 0.0, 0.5, 1.0);; //set color values
	glClear(GL_COLOR_BUFFER_BIT); //set back buffer with this shit
	SDL_GL_SwapWindow(window); //swap back and front buffers so that its visible now
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