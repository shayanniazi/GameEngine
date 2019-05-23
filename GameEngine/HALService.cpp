#include "HALService.h"

//initializes audio, keyboard and other low level systems (SDL)
void HALService::initEngineSubSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}
