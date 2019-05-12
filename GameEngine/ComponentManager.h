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
		//if the componentDatabase already has stored collection of component vector pointers inside it
		else
		{
			bool componentTypeFound = false;
			boost::container::flat_map<void*, size_t>::iterator iter;

			//search each vector from vector database (components vector) to see if it contains the required component type
			for (iter = componentDatabase.begin(); iter != componentDatabase.end(); iter++)
			{
				//if type matches, then insert the passed in component parameter to the vector database's appropriate index
				if (iter->second == typeid(*component).hash_code())
				{
					//since we now know the type of the component is componentType
					std::vector<componentType>* extractedVector = (std::vector<componentType>*) iter->first;
					//get access to the vector pointer from the pointer database now
					std::vector<componentType**>* extractedPtrVector = nullptr;//(std::vector<componentType**>*) pointerDatabase.at(i);

					//loop through the extracted vector to make sure if same address component hasnt been inserted
					//if it already exists in extracted vector, then simply return from function
					for (size_t j = 0; j < extractedVector->size(); j++)
					{
						if (&(extractedVector->at(j)) == component)
						{
							std::cout << "cannot re-insert component of type: " << typeid(componentType).name() << " as its address already exists in database, returning..." << std::endl;
							return;
						}
					}

					//component type exists in database and is not a duplicate
					componentTypeFound = true;

					//push copy of component into array (will retarget original pointer to this copied component below)
					extractedVector->push_back(*component);
					extractedPtrVector->push_back(&component);

					//get pointer to newly inserted component (retarget the pointer)
					componentType* extractedLastComp = &(extractedVector->at(extractedVector->size() - 1));

					//prevent memory leaks by free-ing mem allocated by user, and retargetting pointer to the copy inside vector
					//so that user uses extractedVec copy instead
					delete component;

					//retarget original component ptr to above pointer
					component = extractedLastComp;
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
		//new code here
		boost::container::flat_map<componentType**, componentType>* compMap = new boost::container::flat_map< componentType**, componentType>();
		compMap->reserve(12);
		compMap->insert(std::pair<componentType**, componentType>(&component, *component));
		boost::container::flat_map<void*, size_t>::iterator iter = compMap->begin();

		component = &(compMap->begin()->second);

		//new code end


		//create new space on heap for component as well as componentType** to hold the pointers addresses. Also, reserve space for vectors
		std::vector<componentType>* compVec = new std::vector<componentType>();
		std::vector<componentType**>* compPtrAddresses = new std::vector<componentType**>();
		compVec->reserve(maxEntities);
		compPtrAddresses->reserve(maxEntities);

		//insert dereferenced componentType into allocated space (will create a copy of original content)
		compVec->push_back(*component);
		compPtrAddresses->push_back(&component);

		//prevent memory leaks by deleting original content
		delete component;

		//retarget original component ptr to copied component in array
		component = &(compVec->at(0));

		//insert newly created component type vectors address into main components vector. Also, insert into pointer database
		componentDatabase.insert(std::pair<void*, size_t>(compMap, typeid(componentType).hash_code()));
		pointerDatabase.push_back(compPtrAddresses);
	}

	size_t maxEntities = 100000; //size of each individual component cell (eg 100,000 position components can exist only, after which cache thrashing will occur, albeit temporarily)
	size_t maxComponentTypes = 10000;
	boost::container::flat_map<void*, size_t> componentDatabase;//address holder OR container of base pointers of all unique component type vectors (eg, components.at(0) may hold base addr of 1st pos component out of all pos components). the value part is the type of component the vector is
	std::vector<void*> pointerDatabase; //this holds the vectors address which in turn is a componentType** vector. That holds addresses of the actual pointers

};