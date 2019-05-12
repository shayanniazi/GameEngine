#include "Input.h"

Input* Input::instance = nullptr;

//getting numKeys from SDL_GetKeyboardState() so prevKeyboardState can be initialized;
int Input::numKeys = 0;
const Uint8* Input::currentKeyboardState = SDL_GetKeyboardState(&numKeys);
Uint8* Input::prevKeyboardState = new Uint8[numKeys];

//getting initial x and y positions from SDL_GetMouseState(x,y);
int Input::mouseX, Input::mouseY = 0;
Uint32 Input::currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
Uint32 Input::prevMouseState = Input::currentMouseState;

Input::Input()
{
	SDL_memcpy(prevKeyboardState, currentKeyboardState, numKeys);
}

Input::~Input()
{
	delete[] prevKeyboardState;
}

Input* Input::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Input();
		instance->masterControl = true;
	}
	return instance;
}

void Input::updateInput()
{
	if (!masterControl)
		return;
	currentKeyboardState = SDL_GetKeyboardState(&numKeys);
	currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
}

void Input::updatePrevInput()
{
	if (!masterControl)
		return;
	SDL_memcpy(prevKeyboardState, currentKeyboardState, numKeys);
	prevMouseState = currentMouseState;
}

bool Input::isKeyHeld(KeyCode* keyCode)
{

	return currentKeyboardState[keyCode->getCode()];
}

//returns true during the frame the key is pressed
bool Input::isKeyPressed(KeyCode* keyCode)
{
	//if prev input is false and current input is true
	return !prevKeyboardState[keyCode->getCode()] && currentKeyboardState[keyCode->getCode()];
}

bool Input::isKeyReleased(KeyCode* keyCode)
{
	return prevKeyboardState[keyCode->getCode()] && !currentKeyboardState[keyCode->getCode()];
}

bool Input::isMouseButtonHeld(KeyCode* keyCode)
{
	return currentMouseState & SDL_BUTTON(keyCode->getCode());
}

bool Input::isMouseButtonPressed(KeyCode* keyCode)
{
	return !(prevMouseState & SDL_BUTTON(keyCode->getCode())) && (currentMouseState & SDL_BUTTON(keyCode->getCode()));
} 

bool Input::isMouseButtonReleased(KeyCode* keyCode)
{
	return (prevMouseState & SDL_BUTTON(keyCode->getCode())) && !(currentMouseState & SDL_BUTTON(keyCode->getCode()));
}