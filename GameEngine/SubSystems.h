#pragma once
#include <SDL\SDL.h>

class SubSystems
{
public:
	~SubSystems();
	static SubSystems* getInstance();

private:
	SubSystems();
	static SubSystems* instance;
	void initEngineSubSystems();
};

