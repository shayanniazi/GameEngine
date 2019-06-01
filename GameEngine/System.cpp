#include "System.h"
#include "SystemManager.h"

//whenever user instantiates a system, it is automatically registered into the database
System::System()
{
	SystemManager::registerSystem(this);
}

System::~System()
{
	SystemManager::removeSystem(this); //NOTE: MAKE SURE TO CHECK IF THIS ACTUALLY FUCKING WORKS
}