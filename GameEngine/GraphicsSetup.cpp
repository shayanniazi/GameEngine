#include "GraphicsSetup.h"
#include "DisplayService.h"
#include "SDL.h"
#include "glew.h"
#include <iostream>

SDL_GLContext GraphicsSetup::renderingContext = nullptr;

void GraphicsSetup::initOpenGL(SDL_Window* window, float version)
{
	//parse version
	float fractionalPart, integerPart;
	fractionalPart = modf(version, &integerPart);
	int majorVersion = (int)integerPart;
	int minorVersion = (int)(fractionalPart * 10);

	//set a bunch of OPENGL attributes before CoreEngine sets up the window

	//SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) == -1)
		std::cout << "Could not set GL context profile mask: " << SDL_GetError() << std::endl;

	//OPENGL major version+ eg 4+ (4 and beyond) version if major version is 4
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion) == -1)
		std::cout << "Could not set GL context major version to: " << majorVersion << "\n" << SDL_GetError() << std::endl;

	//OPENGL 4.5 to be specific
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion) == -1)
		std::cout << "Could not set GL context minor version to: " << minorVersion << "\n" <<  SDL_GetError() << std::endl;

	//0 would be single buffering which is terrible anyway. 1 for double buffering
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1)
		std::cout << "Could not configure openGL to have double buffering: " << SDL_GetError() << std::endl;

	//set rendering context to displays window handle
	setRenderingContext(window);

	//init glew
	GLenum initResult = glewInit();

	if (initResult != GLEW_OK)
		std::cout << "Error in initializing glew: " << glewGetErrorString(initResult) << std::endl;

	//Since some graphics cards think a lot of the functions are experimental, so this is needed in that situation
	glewExperimental = GL_TRUE;

	std::cout << "openGL version in use: " << glGetString(GL_VERSION) << std::endl;
}

void GraphicsSetup::setRenderingContext(SDL_Window* window)
{
	//set rendering context
	renderingContext = SDL_GL_CreateContext(window);

	if (renderingContext == NULL)
	{
		std::cout << "Error in setting openGL rendering context: " << SDL_GetError() << std::endl;
		return;
	}
}