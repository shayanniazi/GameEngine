#pragma once
#include <SDL\SDL.h>
#include "KeyCode.h"

class Input
{
public:
	~Input();
	static Input* getInstance();
	static bool isKeyPressed(KeyCode* keyCode);
	static bool isKeyHeld(KeyCode* keyCode);
	static bool isKeyReleased(KeyCode* keyCode);
	static bool isMouseButtonPressed(KeyCode* keyCode);
	static bool isMouseButtonHeld(KeyCode* keyCode);
	static bool isMouseButtonReleased(KeyCode* keyCode);
	void updateInput();
	void updatePrevInput();

private:
	Input();
	bool masterControl = false;
	static Input* instance;
	static const Uint8* currentKeyboardState;
	static Uint8* prevKeyboardState;
	static int numKeys;
	static int mouseX, mouseY;
	static Uint32 currentMouseState;
	static Uint32 prevMouseState;
};