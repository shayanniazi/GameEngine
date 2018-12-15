#pragma once
#include "SubSystems.h"
#include "Display.h"
#include "CoreEngine.h"
#include <iostream>

int main(int argc, char** argv)
{	
	CoreEngine* engine = CoreEngine::getEngineInstance();

	int x;
	std::cin >> x;

	delete engine;
	return 0;
}