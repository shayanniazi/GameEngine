#pragma once
#include <SDL\SDL.h>

class Display
{
public:
	static Display* getDisplay();
	~Display();
	SDL_Window* getWindowHandle();

private:
	Display();
	static Display* instance;
	SDL_Window* window = nullptr;
	int screenWidth = 800;
	int screenHeight = 600;

	void createWindow();
	void destroyWindow();
};

