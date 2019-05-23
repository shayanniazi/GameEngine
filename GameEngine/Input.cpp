#include "Input.h"

bool Input::isKeyHeld(const KeyCode* const keyCode)
{
	return InputService::currentKeyboardState[keyCode->getCode()];
}

//returns true during the frame the key is pressed
bool Input::isKeyPressed(const KeyCode* const keyCode)
{
	//if prev input is false and current input is true
	return !InputService::prevKeyboardState[keyCode->getCode()] && InputService::currentKeyboardState[keyCode->getCode()];
}

bool Input::isKeyReleased(const KeyCode* const keyCode)
{
	return InputService::prevKeyboardState[keyCode->getCode()] && !InputService::currentKeyboardState[keyCode->getCode()];
}

bool Input::isMouseButtonHeld(const KeyCode* const keyCode)
{
	return InputService::currentMouseState & SDL_BUTTON(keyCode->getCode());
}

bool Input::isMouseButtonPressed(const KeyCode* const keyCode)
{
	return !(InputService::prevMouseState & SDL_BUTTON(keyCode->getCode())) && (InputService::currentMouseState & SDL_BUTTON(keyCode->getCode()));
}

bool Input::isMouseButtonReleased(const KeyCode* const keyCode)
{
	return (InputService::prevMouseState & SDL_BUTTON(keyCode->getCode())) && !(InputService::currentMouseState & SDL_BUTTON(keyCode->getCode()));
}