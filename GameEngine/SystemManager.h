#pragma once
#include <vector>

class System; //forward declaration

//STATIC CLASS
class SystemManager
{
public:
	static void registerSystem(System*);
	static void removeSystem(System*);
	static void initializeStorage();
	static void updateSystems();
private:
	static std::vector<System*>* systemsVector;

};