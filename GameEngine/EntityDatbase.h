#pragma once
#include <vector>

class ECSEntity; //forward declaration

//STATIC CLASS
class EntityDatbase
{
public:
	static void registerEntity(ECSEntity* entity); // add entity to entitiesVector
	static void deleteEntity(ECSEntity* entity); //removes all associated components of entity
	static void cleanUp(); //removes and deletes all entities at the end of frame that are flagged with !isAlvie
	static ECSEntity* getEntity(std::string entityName);
	static ECSEntity* getEntity(size_t entityID);

private:
	friend class CoreEngine;

	static void initializeStorage();
	static std::vector<ECSEntity*>* entitiesVector; //contains entity ID's
};