#pragma once

//static class
class Game
{
public:
	static void init(); //initialize game state. Called after engine is initialized
	//static void update(); //tells SystemManager to update all systems

	static const size_t maxEntities = 100000; //what is the max number of entities the games container should allocate when starting out 
};