#pragma once
#include "SDL.h"

class Mat4;

class DisplayService
{
public:
	static int screenWidth;
	static int screenHeight;
	static float FOV;
	static float nearClippingPlane, farClippingPlane, leftClippingPlane, rightClippingPlane, topClippingPlane, bottomClippingPlane;

	static SDL_Window* getWindowHandle();
	static void createWindow();
	static void destroyWindow(SDL_Window* window);
	static void updateWindow();
private:
	static SDL_Window* window;
};

