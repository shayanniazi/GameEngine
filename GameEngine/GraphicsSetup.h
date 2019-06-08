#pragma once
#include "SDL.h"

//STATIC CLASS
class GraphicsSetup
{
public:
	static void initOpenGL(SDL_Window* window, float version);
private:
	static void setRenderingContext(SDL_Window* window);
	static SDL_GLContext renderingContext;
};