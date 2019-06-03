#include "HALService.h"
#include "SDL.h"
#include "glew.h" //OPENGL 
#include <iostream>

//initializes audio, keyboard, openGL and other low level systems (SDL)
void HALService::initEngineSubSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	initOpenGL();
}

void HALService::initOpenGL()
{
	//set a bunch of OPENGL attributes before CoreEngine sets up the window

	//SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) == -1)
		std::cout << "Could not set GL context profile mask: " << SDL_GetError() << std::endl;

	//OPENGL 4+
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) == -1)
		std::cout << "Could not set GL context major version to 4: " << SDL_GetError() << std::endl;

	//OPENGL 4.5 to be specific
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5) == -1)
		std::cout << "Could not set GL context minor version to 5: " << SDL_GetError() << std::endl;

	//0 would be single buffering which is terrible anyway. 1 for double buffering
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1)
		std::cout << "Could not configure openGL to have double buffering: " << SDL_GetError() << std::endl;

	//Since some graphics cards think a lot of the functions are experimental, so this is needed in that situation
	glewExperimental = GL_TRUE;

	glewInit();
}
