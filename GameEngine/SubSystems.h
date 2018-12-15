#pragma once
#include <SDL\SDL.h>

class SubSystems
{
public:
	~SubSystems();
	static SubSystems* getSubSystems();
private:
	SubSystems();
	static SubSystems* instance;
	void initEngineSubSystems();
};

