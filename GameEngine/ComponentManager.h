#pragma once
#include <vector>
#include <boost/container/flat_map.hpp>
#include <iostream>
#include "Component.h"

//also make this singleton

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	template<typename componentType>
	void addComponent(int entityID, componentType*& component)
	{
		//create first element in 'components' vector of type 'component'
		if (componentDatabase.empty())
		{
			std::cout << "component DB was empty, so new component of type: " << typeid(componentType).name() << " was created" << std::endl;
			newComponentDBEntry<componentType>(component);
		}
		//if the componentDatabase already has stored collection of component map pointers inside it
		else
		{
			bool componentTypeFound = false;

			//search each vector from vector database (components vector) to see if it contains the required component type
			for (boost::container::flat_map<void*, size_t>::iterator i = componentDatabase.begin(); i != componentDatabase.end(); i++)
			{
				//if type matches, then insert the passed in component parameter to the vector database's appropriate index
				if (i->second == typeid(*component).hash_code())
				{
					//since we now know the type of the component is componentType
					boost::container::flat_map<componentType**, componentType>* extractedMap = (boost::container::flat_map<componentType**, componentType>*) i->first;
					//get access to the vector pointer from the pointer database now

					//loop through the extracted vector to make sure if same address component hasnt been inserted
					//if it already exists in extracted vector, then simply return from function
					for (boost::container::flat_map<componentType**, componentType>::iterator j = extractedMap->begin(); j != extractedMap->end(); j++)
					{
						if (&(j->second) == component)
						{
							std::cout << "cannot re-insert component of type: " << typeid(componentType).name() << " as its address already exists in database, returning..." << std::endl;
							return;
						}
					}

					//component type exists in database and is not a duplicate
					componentTypeFound = true;

					//push copy of component into array (will retarget original pointer to this copied component below)
					extractedMap->insert(std::pair<componentType**, componentType>(&component, *component));

					componentType* extractedComponent = &(extractedMap->at(&component));

					//prevent memory leaks by free-ing mem allocated by user, and retargetting pointer to the copy inside vector
					//so that user uses extractedVec copy instead
					delete component;

					//retarget original component ptr to above pointer
					component = extractedComponent;
					std::cout << "component of type: " << typeid(componentType).name() << " successfully inserted into Database" << std::endl;
					break;
				}
			}
			//if the database didnt contain the requisite component type, then create a new entry into the database for that component type
			if (!componentTypeFound)
			{
				std::cout << "component of type: " << typeid(componentType).name() << " did not exist, so creating new entry into DB" << std::endl;
				newComponentDBEntry<componentType>(component);
			}
		}

	}

private:
	template<typename componentType>
	void newComponentDBEntry(componentType*& component)
	{
		//create new space on heap for component as well as componentType** to hold the pointers addresses. Also, reserve space for vectors
		boost::container::flat_map<componentType**, componentType>* compMap = new boost::container::flat_map< componentType**, componentType>();
		compMap->reserve(maxEntities);

		//insert dereferenced componentType into allocated space (will create a copy of original content), as well as insert handle to pointer
		compMap->insert(std::pair<componentType**, componentType>(&component, *component));

		//prevent memory leaks by deleting original content
		delete component;

		//retarget original component ptr to copied component in map
		component = &(compMap->begin()->second);

		//insert newly created component type vectors address into main components vector. Also, insert into pointer database
		componentDatabase.insert(std::pair<void*, size_t>(compMap, typeid(*component).hash_code()));
	}

	size_t maxEntities = 100000; //size of each individual component cell (eg 100,000 position components can exist only, after which cache thrashing will occur, albeit temporarily)
	size_t maxComponentTypes = 10000;
	boost::container::flat_map<void*, size_t> componentDatabase;//address holder OR container of base pointers of all unique component type vectors (eg, components.at(0) may hold base addr of 1st pos component out of all pos components). the value part is the type of component the vector is
};