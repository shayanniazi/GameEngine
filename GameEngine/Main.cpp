#pragma once
#include "System.h"
#include "Display.h"
#include <iostream>

int main(int argc, char** argv)
{	
	System* system = new System(); 
	Display* display = new Display(); //creates the window

	system->initEngineSubSystems(); //initialize low level systems such as audio, keyboard etc
	
	int x;
	std::cin >> x;

	delete system, display;
	return 0;
}