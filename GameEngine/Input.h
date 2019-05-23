#pragma once
#include "InputService.h"
#include "KeyCode.h"

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