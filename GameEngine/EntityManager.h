#pragma once
#include <vector>

//singleton class
class EntityManager
{
public:
	~EntityManager();
	static EntityManager& getInstance();
	void createEntity(); // add entity to entitiesVector
	void deleteEntity(); //removes all associated components of entity
	void cleanUp(); //removes and deletes all entities at the end of frame that are flagged with !isAlvie
private:
	EntityManager();
	static EntityManager* instance;
	std::vector<size_t> entitiesVector; //contains entity ID's
};