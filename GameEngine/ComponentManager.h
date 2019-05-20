#pragma once
#include <vector>
#include <boost/container/flat_map.hpp>
#include <iostream>
#include "Component.h"

//SINGLETON CLASS
class ComponentManager
{
public:
	~ComponentManager();
	static ComponentManager& getInstance();
	static ComponentManager* instance;

	template<typename componentType>
	void addComponent(size_t entityID, componentType*& component)
	{
		//create first element in 'components' vector of type 'component'
		if (componentDatabase.empty())
		{
			std::cout << "component DB was empty, so new component of type: '" << typeid(componentType).name() << "' was created" << std::endl;
			newComponentDBEntry<componentType>(entityID, component);
		}
		//if the componentDatabase already has stored collection of component map pointers inside it
		else
		{
			bool componentTypeFound = false;
			bool retargettingRequired = false;

			//search each item from component database (components map) to see if it contains the required component type
			for (boost::container::flat_map<void*, size_t>::iterator compDBIter = componentDatabase.begin(); compDBIter != componentDatabase.end(); compDBIter++)
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
							std::cout << "cannot re-insert component of type: " << typeid(componentType).name() << " as its address already exists in database, returning..." << std::endl;
							return;
						}
					}

					//component type has been found to exist in database and is not a duplicate
					componentTypeFound = true;

					//before insertion, check if retargetting is going to be needed once component is inserted in next few steps
					if ((extractedVector->capacity() == extractedVector->size()))
						retargettingRequired = true;

					//push copy of component into array (will retarget original pointer to this copied component below)
					extractedVector->push_back(*component);

					//retrieve pointer to newly inserted component at specific location 
					componentType* extractedLastComp = &(extractedVector->at(extractedVector->size() - 1));

					//prevent memory leaks by free-ing mem allocated by user, and retargetting pointer to the copy inside vector
					//so that user uses extractedVec copy instead
					delete component;

					//retarget original component ptr to above pointer
					component = extractedLastComp;

					//store retargetted component address (pointer address) inside component itself
					((Component*)component)->componentPtrHandle = (Component**)(&component);
					*((Component*)component)->componentPtrHandle = extractedLastComp;

					//set entityID of component
					((Component*)component)->setEntityID(entityID);

					//retarget everything if required
					if (retargettingRequired)
					{
						//retarget component DB to new vector location
						for (size_t j = 0; j < extractedVector->size(); j++)
						{
							Component* extractedComp = &(extractedVector->at(j));
							*(extractedComp->componentPtrHandle) = extractedComp;
						}
						//retargetting done
						retargettingRequired = false;
						std::cout << "component vector of type: " << typeid(componentType).name() << " capacity reached. Retarget to new mem location successful" << std::endl;
					}

					std::cout << "component of type: " << typeid(componentType).name() << " successfully inserted into Database" << std::endl;
					break;
				}
			}
			//if the database didnt contain the requisite component type, then create a new entry into the database for that component type
			if (!componentTypeFound)
			{
				std::cout << "component of type: " << typeid(componentType).name() << " did not exist, so creating new entry into DB" << std::endl;
				newComponentDBEntry<componentType>(entityID, component);
			}
		}
	}

	//returns all components of type componentType
	template<typename componentType>
	std::vector<componentType>& getComponents()
	{
		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDatabase.begin(); i != componentDatabase.end(); i++)
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
		return *emptyVec;
	}

	//returns 1st component of componentType that is linked to entity with entityID
	template <typename componentType>
	componentType* getComponent(size_t entityID)
	{
		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDatabase.begin(); i != componentDatabase.end(); i++)
		{
			//check if the component map is of the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;
				
				//loop through each component inside extractedVector
				for (size_t j = 0; j < extractedVector->size(); j++)
				{
					componentType* extractedComponent = extractedVector->at(j);
					
					//check if component has the required ID
					if (((Component*)extractedComponent)->entityID == entityID)
					{
						return extractedTypeComponent;
					}
				}
			}
		}
		//if nothing is found then return empty placeholder component
		std::cout << "Component of component type: '" << typeid(componentType).name() << "' with entity ID " << entityID << " not found, returning empty reference" << std::endl;		
		return nullptr;
	}

private:
	ComponentManager();

	size_t maxEntities = 100000; //size of each individual component cell (eg 100,000 position components can exist only, after which cache thrashing will occur, albeit temporarily)
	size_t maxComponentTypes = 10000;
	boost::container::flat_map<void*, size_t> componentDatabase;//address holder OR container of base pointers of all unique component type vectors (eg, components.at(0) may hold base addr of 1st pos component out of all pos components). the value part is the type of component the vector is

	template<typename componentType>
	void newComponentDBEntry(size_t entityID, componentType*& component)
	{
		//create new space on heap for component as well as componentType** to hold the pointers addresses. Also, reserve space for vectors
		std::vector<componentType>* compVec = new std::vector<componentType>();
		compVec->reserve(maxEntities);

		//set entityID of component
		((Component*)component)->setEntityID(entityID);

		//insert dereferenced componentType into allocated space (will create a copy of original content), as well as insert handle to pointer
		compVec->push_back(*component);

		//prevent memory leaks by deleting original content
		delete component;

		//retarget original component ptr to copied component in map
		component = &(compVec->at(0));

		//store component address inside component itself
		((Component*)component)->componentPtrHandle = (Component**)(&component);

		//insert newly created component type vectors address into main components vector. Also, insert into pointer database
		componentDatabase.insert(std::pair<void*, size_t>(compVec, typeid(*component).hash_code()));
	}
};