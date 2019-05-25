#pragma once
#include "SDL.h"

//static class
class InputService
{
public:
	static void initInputStates();
	static void updateInput();
	static void updatePrevInput();
	static const Uint8* currentKeyboardState;
	static Uint8* prevKeyboardState;
	static Uint32 currentMouseState;
	static Uint32 prevMouseState;

private:
	static int numKeys; //number of unique keys of detected from user keyboard (detected by SDL_getKeyboardState(&numKeys))
	static int mouseX, mouseY;

};