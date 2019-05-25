#include "InputService.h"
#include "KeyCode.h"

//getting numKeys from SDL_GetKeyboardState() so prevKeyboardState can be initialized;
int InputService::numKeys = 0;
const Uint8* InputService::currentKeyboardState = SDL_GetKeyboardState(&numKeys);
Uint8* InputService::prevKeyboardState = new Uint8[numKeys];

//getting initial x and y positions from SDL_GetMouseState(x,y) and storing in mouseX and mouseY;
int InputService::mouseX = 0;
int InputService::mouseY = 0;
Uint32 InputService::currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
Uint32 InputService::prevMouseState = currentMouseState;

//intialzing keyboard and mouse states
void InputService::initInputStates()
{
	//intializing prevKeyboardState once it has its size determined by numKeys)
	SDL_memcpy(prevKeyboardState, currentKeyboardState, numKeys);
}

void InputService::updateInput()
{
	currentKeyboardState = SDL_GetKeyboardState(&numKeys);
	currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
}

void InputService::updatePrevInput()
{
	SDL_memcpy(prevKeyboardState, currentKeyboardState, numKeys);
	prevMouseState = currentMouseState;
}