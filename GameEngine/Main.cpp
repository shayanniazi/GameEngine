#pragma once
#include "SubSystems.h"
#include "Display.h"
#include "CoreEngine.h"
#include <iostream>

int main(int argc, char** argv)
{	
	CoreEngine* engine = CoreEngine::getEngineInstance();

	delete engine;
	return 0;
}