#pragma once

//Hardware Abstraction Layer: initializes audio, keyboard and other low level systems (Currently using SDL to perform the job)
class HALService
{
public:
	static void initEngineSubSystems();
private:
	static void initOpenGL();
};

