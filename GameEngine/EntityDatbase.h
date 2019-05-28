#pragma once
#include <vector>

class ECSEntity; //forward declaration

//singleton class
class EntityDatbase
{
public:
	~EntityDatbase();
	static EntityDatbase& getInstance();
	void registerEntity(ECSEntity* entity); // add entity to entitiesVector
	void deleteEntity(ECSEntity* entity); //removes all associated components of entity
	void cleanUp(); //removes and deletes all entities at the end of frame that are flagged with !isAlvie
private:
	EntityDatbase();
	static EntityDatbase* instance;
	std::vector<ECSEntity*> entitiesVector; //contains entity ID's
};