#pragma once
#include <SDL\SDL.h>

class Display
{
public:
	Display();
	~Display();
private:
	SDL_Window* window = nullptr;
	int screenWidth = 800;
	int screenHeight = 600;

	void createWindow();
	void destroyWindow();
};

