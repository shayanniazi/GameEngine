#pragma once
//#include "KeyCode.h"

class KeyCode; //forward declaration

class Input
{
public:
	static bool isKeyPressed(const KeyCode* const keyCode);
	static bool isKeyHeld(const KeyCode* const keyCode);
	static bool isKeyReleased(const KeyCode* const keyCode);
	static bool isMouseButtonPressed(const KeyCode* const keyCode);
	static bool isMouseButtonHeld(const KeyCode* const keyCode);
	static bool isMouseButtonReleased(const KeyCode* const keyCode);
};