#include "Input.h"

Input* Input::instance = nullptr;
int Input::numKeys = 0;
const Uint8* Input::currentKeyboardState = SDL_GetKeyboardState(&numKeys);
Uint8* Input::prevKeyboardState = new Uint8[numKeys];

Input::Input()
{
}


Input::~Input()
{
}

Input* Input::getInstance()
{
	if (instance == nullptr)
		instance = new Input();
	return instance;
}

void Input::updateKeyboardState()
{
	currentKeyboardState = SDL_GetKeyboardState(&numKeys);
}

void Input::updatePrevKeyboardState()
{
	SDL_memcpy(prevKeyboardState, currentKeyboardState, numKeys);
}

bool Input::isKeyHeld(SDL_Scancode keyScanCode)
{
	return currentKeyboardState[keyScanCode];
}

//returns true during the frame the key is pressed
bool Input::isKeyPressed(SDL_Scancode keyScanCode)
{
	//if prev input is false and current input is true
	return !prevKeyboardState[keyScanCode] && currentKeyboardState[keyScanCode];
}

bool Input::isKeyReleased(SDL_Scancode keyScanCode)
{
	return prevKeyboardState[keyScanCode] && !currentKeyboardState[keyScanCode];
}