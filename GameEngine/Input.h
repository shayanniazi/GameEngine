#pragma once
#include <SDL\SDL.h>

class Input
{
public:
	~Input();
	static Input* getInstance();
	static bool isKeyPressed(SDL_Scancode KeyScanCode);
	static bool isKeyHeld(SDL_Scancode KeyScanCode);
	static bool isKeyReleased(SDL_Scancode KeyScanCode);
	void updateKeyboardState();
	void updatePrevKeyboardState();

private:
	Input();
	static Input* instance;
	static const Uint8* currentKeyboardState;
	static Uint8* prevKeyboardState;
	static int numKeys;
};