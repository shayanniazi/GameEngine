#pragma once
#include <vector>
#include "Utilities.h"

class System; //forward declaration

//STATIC CLASS
class SystemManager
{
public:
	template <typename systemType>
	static void registerSystem()
	{
		Utilities::isChildOf<systemType, System>();

		//make sure system of type doesnt already exist in system database
		for (size_t i = 0; i < systemsVector->size(); i++)
		{
			if (typeid(*systemsVector->at(i)).hash_code() == typeid(systemType).hash_code())
			{
				std::cout << "System of type " << typeid(systemType).name() << " already exists in system database, cannot register" << std::endl;
				return;
			}
		}

		systemType* system = new systemType();
		systemsVector->push_back(system);
		std::cout << "System " << typeid(*system).name() << " successfully registered into system database" << std::endl;
	}

	template <typename systemType>
	static void removeSystem()
	{
		Utilities::isChildOf<systemType, System>();

		for (size_t i = 0; i < systemsVector->size(); i++)
		{
			//if both pointing to same location
			if (typeid(*systemsVector->at(i)).hash_code() == typeid(systemType).hash_code())
			{
				System* extractedSystem = systemsVector->at(i);

				systemsVector->erase(systemsVector->begin() + i);
				
				delete extractedSystem;

				std::cout << "System " << typeid(systemType).name() << " successfully removed from system database" << std::endl;
				return;
			}
		}
		std::cout << "System " << typeid(systemType).name() << " could not be removed, as it was not in system database" << std::endl;
	}


private:
	friend class CoreEngine;
	friend class GameService;

	static void initializeStorage();
	static void updateSystems();
	static void drawSystems();
	static std::vector<System*>* systemsVector;
};