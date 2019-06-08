#include "HALService.h"
#include "SDL.h"


//initializes audio, keyboard, openGL and other low level systems (SDL)
void HALService::initEngineSubSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

