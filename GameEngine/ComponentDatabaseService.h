#pragma once
#include <vector>
#include <boost/container/flat_map.hpp>
#include <iostream>
#include "Component.h"

//SINGLETON CLASS
class ComponentDatabaseService
{
public:
	static ComponentDatabaseService& getInstance();

private:
	friend class ComponentDatabase;
	friend class ECSEntity;
	friend class CoreEngine;

	ComponentDatabaseService();
	~ComponentDatabaseService();
	void cleanGarbage(); //memory leak cleanup

	static ComponentDatabaseService* instance;
	size_t m_maxEntities = 100000; //size of each individual component cell (eg 100,000 position components can exist only, after which cache thrashing will occur, albeit temporarily)
	size_t m_maxComponentTypes = 10000;
	boost::container::flat_map<void*, size_t> componentDB; //address holder OR container of base pointers of all unique component type vectors (eg, components.at(0) may hold base addr of 1st pos component out of all pos components). the value part is the type of component the vector is
	std::vector<void*> garbage; //this contains pointers to vectors that are returned to user upon calling 'getComponent' functions mainly. If a returned vector is empty, it will be flagged to be destroyed at end of each frame

	template<typename componentType>
	void newComponentDBEntry(size_t entityID, componentType*& component)
	{
		//create new space on heap for component as well as componentType** to hold the pointers addresses. Also, reserve space for vectors
		std::vector<componentType>* compVec = new std::vector<componentType>();
		compVec->reserve(m_maxEntities);

		//set entityID of component
		((Component*)component)->entityID = entityID;

		//insert dereferenced componentType into allocated space (will create a copy of original content), as well as insert handle to pointer
		compVec->push_back(*component);

		//prevent memory leaks by deleting original content
		delete component;

		//retarget original component ptr to copied component in map
		component = &(compVec->at(0));

		//insert newly created component type vectors address into main components vector. Also, insert into pointer database
		componentDB.insert(std::pair<void*, size_t>(compVec, typeid(*component).hash_code()));
	}

	template<typename componentType>
	bool addComponent(size_t entityID, componentType*& component)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//create first element in 'components' vector of type 'component'
		if (componentDB.empty())
		{
			std::cout << "component DB was empty, so new component of type: '" << typeid(componentType).name() << "' was created" << std::endl;
			newComponentDBEntry<componentType>(entityID, component);
			return true;
		}
		//if the componentDB already has stored collection of component map pointers inside it
		else
		{
			bool componentTypeFound = false;

			//search each item from component database (components map) to see if it contains the required component type
			for (boost::container::flat_map<void*, size_t>::iterator compDBIter = componentDB.begin(); compDBIter != componentDB.end(); compDBIter++)
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
							return false;
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

					//set entityID of component
					((Component*)component)->entityID = entityID;

					std::cout << "component of type: " << typeid(componentType).name() << " successfully inserted into Database" << std::endl;
					return true;
				}
			}
			//if the database didnt contain the requisite component type, then create a new entry into the database for that component type
			if (!componentTypeFound)
			{
				std::cout << "component of type: " << typeid(componentType).name() << " did not exist, so creating new entry into DB" << std::endl;
				newComponentDBEntry<componentType>(entityID, component);
				return true;
			}
		}
	}

	//returns all components of type componentType
	template<typename componentType>
	const std::vector<componentType>& getAllComponents()
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();
	
		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB.begin(); i != componentDB.end(); i++)
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
		garbage.push_back(emptyVec);
		return *emptyVec;
	}

	//returns 1st component of componentType that is linked to entity with entityID
	template <typename componentType>
	componentType* getComponent(size_t entityID)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB.begin(); i != componentDB.end(); i++)
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
					if (((Component*)extractedComponent)->entityID == entityID)
					{
						return extractedComponent;
					}
				}
			}
		}
		//if nothing is found then return empty placeholder component
		std::cout << "Component of component type: '" << typeid(componentType).name() << "' with entity ID " << entityID << " not found, returning empty reference" << std::endl;
		return nullptr;
	}

	//returns all components of componentType that is linked to entity with entityID
	template <typename componentType>
	std::vector<componentType*>* getComponents(size_t entityID)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//create new vector which will contain all components of type with entityID
		std::vector<componentType*>* entityVec = new std::vector<componentType>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB.begin(); i != componentDB.end(); i++)
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
					if (((Component*)extractedComponent)->entityID == entityID)
					{
						entityVec->push_back(extractedComponent);
					}
				}
			}
		}
		garbage.push_back(entityVec);
		return entityVec;
	}

	//removes 1st component of componentType with entityID
	template<typename componentType>
	bool removeComponent(size_t entityID)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB.begin(); i != componentDB.end(); i++)
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
					if (((Component*)extractedComponent)->entityID == entityID)
					{
						extractedVector->erase(extractedVector->begin() + j);
						std::cout << "Component of component type: '" << typeid(componentType).name() << "' with entity ID " << entityID << " erased from vector" << std::endl;
						return true;
					}
				}
			}
		}

		return false;
	}

	//removes all components of componentType with entityID
	template<typename componentType>
	bool removeComponents(size_t entityID)
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB.begin(); i != componentDB.end(); i++)
		{
			//check if the component map contains the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//component with matching ID found
				bool componentFound = false;

				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;

				//loop through each component inside extractedVector
				for (size_t j = 0; j < extractedVector->size(); j++)
				{
					//extract component out of vector one by one
					componentType* extractedComponent = &extractedVector->at(j);

					//check if extracted component has the required ID
					if (((Component*)extractedComponent)->entityID == entityID)
					{
						componentFound = true;
						extractedVector->erase(extractedVector->begin() + j);
						std::cout << "Component of component type: '" << typeid(componentType).name() << "' with entity ID " << entityID << " erased from vector" << std::endl;
					}
				}

				if (!componentFound)
				{
					std::cout << "No component of type: " << typeid(componentType).name() << " with entity ID: " << entityID << " found in component database" << std::endl;
					return false;
				}
				else
					return true;
			}
		}
	}

	//removes all components of componentType
	template<typename componentType>
	void removeAllComponents()
	{
		//do a pre check to make sure that component is of the correct type (i.e derived component type, and no other class)
		Utilities::isChildOf<componentType, Component>();

		//loop through component database
		for (boost::container::flat_map<void*, size_t>::iterator i = componentDB.begin(); i != componentDB.end(); i++)
		{
			//check if the component map is of the right type
			if (i->second == typeid(componentType).hash_code())
			{
				//since we now know the type of the component is componentType
				std::vector<componentType>* extractedVector = (std::vector<componentType>*) i->first;
				extractedVector->clear();
				std::cout << "Removed all components of every entity from component vector of type: " << typeid(componentType).name() << std::endl;
				return;
			}
		}
		//assuming appropriate type was not located in DB
		std::cout << "Component vector of type: " << typeid(componentType).name() << " was not found in the component database, therefore unabale to remove all components from it" << std::endl;
	}
};