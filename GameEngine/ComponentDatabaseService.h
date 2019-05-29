#pragma once
#include <vector>
#include <boost/container/flat_map.hpp>
#include <iostream>
#include "Component.h"

//STATIC CLASS
class ComponentDatabaseService
{
private:
	friend class ComponentDatabase;
	friend class ECSEntity;
	friend class CoreEngine;
	friend class Component;

	static size_t maxEntities; //size of each individual component cell (eg 100,000 position components can exist only, after which cache thrashing will occur, albeit temporarily)
	static size_t maxComponentTypes;
	static boost::container::flat_map<void*, size_t>* componentDB; //address holder OR container of base pointers of all unique component type vectors (eg, components.at(0) may hold base addr of 1st pos component out of all pos components). the value part is the type of component the vector is
	static std::vector<void*>* garbage; //this contains pointers to vectors that are returned to user upon calling 'getComponent' functions mainly. If a returned vector is empty, it will be flagged to be destroyed at end of each frame

	static void cleanGarbage(); //memory leak cleanup
	static void initializeStorage(); //reserve memory for garbage and componentDB maps

	template<typename componentType>
	static void newComponentDBEntry(ECSEntity* entity, componentType*& component)
	{
		//create new space on heap for component as well as componentType** to hold the pointers addresses. Also, reserve space for vectors
		std::vector<componentType>* compVec = new std::vector<componentType>();
		compVec->reserve(maxEntities);

		//set entityID of component
		((Component*)component)->entity = entity;

		//insert dereferenced componentType into allocated space (will create a copy of original content), as well as insert handle to pointer
		compVec->push_back(*component);

		//prevent memory leaks by deleting original content
		delete component;

		//retarget original component ptr to copied component in map
		component = &(compVec->at(0));

		//insert component copy into entitys own list after components been retargetted to componentDatabase vector location
		entity->insert(component);		

		//insert newly created component type vectors address into main components vector. Also, insert into pointer database
		componentDB->insert(std::pair<void*, size_t>(compVec, typeid(*component).hash_code()));

		std::cout << "component of type: " << typeid(componentType).name() << " of entity: '" << entity->entityName << "' with ID: " << entity->entityID << "' successfully inserted into component database" << std::endl;
	}

	template<typename componentType>
	static void addComponent(ECSEntity* entity, componentType*& component)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//create first element in 'components' vector of type 'component'
		if (componentDB->empty())
		{
			std::cout << "component DB was empty, so new component of type: '" << typeid(componentType).name() << "' was created" << std::endl;
			newComponentDBEntry<componentType>(entity, component);
			return;
		}
		//if the componentDB already has stored collection of component map pointers inside it
		else
		{
			bool componentTypeFound = false;

			//search each item from component database (components map) to see if it contains the required component type
			for (boost::container::flat_map<void*, size_t>::iterator compDBIter = componentDB->begin(); compDBIter != componentDB->end(); compDBIter++)
			{
				//check if passed in component parameter type exists in database
				if (compDBIter->second == typeid(*component).hash_code())
				{
					//get access to the vector pointer from the database. Since we now know the type of the component is componentType
					std::vector<componentType>* extractedVector = (std::vector<componentType>*) compDBIter->first;

					for (size_t j = 0; j < extractedVector->size(); j++)
					{
						if (&(extractedVector->at(j)) == component)
						{
							std::cout << "cannot re-insert component of type: " << typeid(componentType).name() << " to entity: '" << entity->entityName <<"' with ID: " << entity->entityID <<" as its address already exists in component database, returning..." << std::endl;
							return;
						}
					}

					//component type has been found to exist in database and is not a duplicate
					componentTypeFound = true;

					//push copy of component into array (will retarget original pointer to this copied component below)
					extractedVector->push_back(*component);

					//retrieve pointer to newly inserted component at specific location 
					componentType* extractedLastComp = &(extractedVector->at(extractedVector->size() - 1));

					//prevent memory leaks by free-ing mem allocated by user, and retargetting pointer to the copy inside vector
					//so that user uses extractedVec copy instead
					delete component;

					//retarget original component ptr to above pointer
					component = extractedLastComp;

					//insert component copy into entitys own list after components been retargetted to componentDatabase vector location
					entity->insert(component);

					//set entity of inserted component
					((Component*)component)->entity = entity;

					std::cout << "component of type: " << typeid(componentType).name() << " of entity: '"<< entity->entityName <<"' with ID: " << entity->entityID <<"' successfully inserted into component database" << std::endl;
					return;
				}
			}
			//if the database didnt contain the requisite component type, then create a new entry into the database for that component type
			if (!componentTypeFound)
			{
				std::cout << "component of type: " << typeid(componentType).name() << " did not exist, so creating new entry into component database" << std::endl;
				newComponentDBEntry<componentType>(entity, component);
				return;
			}
		}
	}

	//returns all components of type componentType
	template<typename componentType>
	static const std::vector<componentType>& getAllComponents()
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();
	
		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB->begin(); i != componentDB->end(); i++)
		{
			//check if the component map is of the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;
				return *extractedVector;
			}
		}
		//if nothing is found then return empty placeholder component vector
		std::cout << "Components of component type: '" << typeid(componentType).name() << "' not found, returning empty reference" << std::endl;
		std::vector<componentType>* emptyVec = new std::vector<componentType>();
		//store into eraseable pool
		garbage->push_back(emptyVec);
		return *emptyVec;
	}

	//returns 1st component of componentType that is linked to entity with entityID
	template <typename componentType>
	static componentType* getComponent(ECSEntity* entity)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB->begin(); i != componentDB->end(); i++)
		{
			//check if the component map is of the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;

				//loop through each component inside extractedVector
				for (size_t j = 0; j < extractedVector->size(); j++)
				{
					//extract component out of vector one by one
					componentType* extractedComponent = &extractedVector->at(j);

					//check if extracted component has the required ID
					if (((Component*)extractedComponent)->entity->entityID == entity->entityID)
					{
						return extractedComponent;
					}
				}
			}
		}
		//if nothing is found then return empty placeholder component
		std::cout << "Warning! Component of component type: '" << typeid(componentType).name() << "' of entity '" << entity->entityName << "' with ID: '" << entity->entityID << "' not found, returning nullptr" << std::endl;
		return nullptr;
	}

	//returns all components of componentType that is linked to entity with entityID
	template <typename componentType>
	static std::vector<componentType*>* getComponents(ECSEntity* entity)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//create new vector which will contain all components of type with entityID
		std::vector<componentType*>* entityVec = new std::vector<componentType*>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB->begin(); i != componentDB->end(); i++)
		{
			//check if the component map is of the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;

				//loop through each component inside extractedVector
				for (size_t j = 0; j < extractedVector->size(); j++)
				{
					//extract component out of vector one by one
					componentType* extractedComponent = &extractedVector->at(j);

					//check if extracted component has the required ID
					if (((Component*)extractedComponent)->entity->entityID == entity->entityID)
					{
						entityVec->push_back(extractedComponent);
					}
				}
			}
		}
		garbage->push_back(entityVec);
		return entityVec;
	}

	//removes 1st component of componentType with entityID
	template<typename componentType>
	static void removeComponent(ECSEntity* entity)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB->begin(); i != componentDB->end(); i++)
		{
			//check if the component map contains the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;

				//loop through each component inside extractedVector
				for (size_t j = 0; j < extractedVector->size(); j++)
				{
					//extract component out of vector one by one
					componentType* extractedComponent = &extractedVector->at(j);

					//check if extracted component has the required ID
					if (((Component*)extractedComponent)->entity->entityID == entity->entityID)
					{
						//before removing from component, make sure to remove the entitys component that points to same thing as extractedComp
						entity->remove(extractedComponent);
						
						//now remove component from the database
						extractedVector->erase(extractedVector->begin() + j);
						std::cout << "Component of component type: '" << typeid(componentType).name() << "' of entity '" << entity->entityName << "' with ID: '" << entity->entityID << "' erased from component database" << std::endl;
						return;
					}
				}
			}
		}
	}

	//removes all components of componentType with entityID
	template<typename componentType>
	static bool removeComponents(ECSEntity* entity)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB->begin(); i != componentDB->end(); i++)
		{
			//check if the component map contains the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//component with matching ID found
				bool componentFound = false;

				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;

				//loop through each component inside extractedVector
				for (size_t j = 0; j < extractedVector->size();)
				{
					//extract component out of vector one by one
					componentType* extractedComponent = &extractedVector->at(j);

					//check if extracted component has the required ID
					if (((Component*)extractedComponent)->entity->entityID == entity->entityID)
					{
						//before removing from component, make sure to remove the entitys component that points to same thing as extractedComp
						entity->remove(extractedComponent);

						componentFound = true;
						extractedVector->erase(extractedVector->begin() + j);
						std::cout << "Component of component type: '" << typeid(componentType).name() << "' of entity '" << entity->entityName << "' with ID: '" << entity->entityID << "' erased from component database" << std::endl;
					}
					else
						j++;
				}

				if (!componentFound)
				{
					std::cout << "No component of type: '" << typeid(componentType).name() << "' of entity '" << entity->entityName << "' with ID: '" << entity->entityID << "' found in component database" << std::endl;
					return false;
				}
				else
					return true;
			}
		}
	}

	//removes all components of componentType
	template<typename componentType>
	static void removeAllComponents()
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB->begin(); i != componentDB->end(); i++)
		{
			//check if the component map is of the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;
				
				//before clearing extracted vector, make sure to remove the entitys components that have the same type
				for (size_t i = 0; i < extractedVector->size(); i++)
				{
					Component* extractedComp = &extractedVector->at(i);
					extractedComp->entity->removeAllOfType(extractedComp->getTypeID());
				}

				//once all entities have removed their components that have type componentType, clear extractedVector
				extractedVector->clear();
				std::cout << "Removed all components of every entity from component database of type: " << typeid(componentType).name() << std::endl;
				return;
			}
		}
		//assuming appropriate type was not located in DB
		std::cout << "Component of type: " << typeid(componentType).name() << " was not found in the component database, therefore unabale to fulfill removal request" << std::endl;
	}

	//removes particular component whose handle (pointer) we have 
	template<typename componentType>
	static void removeComponent(componentType* component)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB->begin(); i != componentDB->end(); i++)
		{
			//check if the component map contains the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;

				//loop through each component inside extractedVector
				for (size_t j = 0; j < extractedVector->size(); j++)
				{
					//extract component out of vector one by one
					componentType* extractedComponent = &extractedVector->at(j);

					//check if both point to same location, if yes, then delete component
					if (component == extractedComponent)
					{
						//before removing from component, make sure to remove the entitys component that points to same thing as extractedComp
						((Component*)component)->entity->remove(extractedComponent);

						//now remove component from the database
						extractedVector->erase(extractedVector->begin() + j);
						std::cout << "Component of component type: '" << typeid(componentType).name() << "' of entity '" << entity->entityName << "' with ID: '" << entity->entityID << "' erased from component database" << std::endl;
						return;
					}
				}
			}
		}
	}
};