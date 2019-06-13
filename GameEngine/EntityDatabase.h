#pragma once
#include <vector>

class ECSEntity; //forward declaration

//STATIC CLASS
class EntityDatabase
{
public:
	//static ECSEntity* emptyEntity;
	static ECSEntity* getEntity(std::string entityName);
	static ECSEntity* getEntity(size_t entityID);
	static ECSEntity* getEntity(ECSEntity* entity);

private:
	friend class GameService; //needs to initialize storage i.e reserve space (entitiesVector)
	friend class ECSEntity;

	static void registerEntity(ECSEntity* entity); // add entity to entitiesVector
	static void deleteEntity(ECSEntity* entity); //removes all associated components of entity
	static void initializeStorage();

	static std::vector<size_t>* reusableIDPool;
	static size_t IDCounter;
	static std::vector<ECSEntity*>* entitiesVector; //contains entity ID's
};