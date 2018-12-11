#include "System.h"

System::System()
{

}


System::~System()
{
}

//initializes audio, keyboard and other low level systems
void System::initEngineSubSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}
