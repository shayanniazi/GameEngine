#include "ECSEntity.h"
#include "Game.h"
#include "EntityDatabase.h"

ECSEntity::~ECSEntity()
{
}

ECSEntity::ECSEntity(std::string entityName)
{
	components.reserve(100);

	this->entityName = entityName;
	
	//will generate new ID for entity as well as register entity into database
	EntityDatabase::registerEntity(this); 
}

void ECSEntity::destroy()
{
	//flag every component attached to this entity to be 0 (i.e to be deleted)
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->entity = nullptr;
		components.at(i)->entityID = 0;
	}

	//for the frame destroy() is called, remove all dead components whenever a system loops over a set of components
	ComponentDatabaseService::removeDeadComponents = true;

	std::cout << "Entity '" << entityName << "' with ID: " << entityID << " successfully tagged for removal " << std::endl;

	//put ID back into reusable pool as well as removes entity from database
	EntityDatabase::deleteEntity(this);

	delete this;
}

//remove component* from this entities components vector. Called by componentDatabaseService in removeComponents<type>(entity) so that this entity can also remove that particular component from itself
void ECSEntity::remove(const Component* comp)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		//if both point to the same location in a component database
		if (comp == components.at(i))
		{
			components.erase(components.begin() + i);
			break;
		}
	}
}

//removes all components from entity that have certain componentTypeID
void ECSEntity::removeAllOfType(size_t compTypeID)
{
	for (size_t j = 0; j < components.size(); j++)
	{
		if (components.at(j)->getTypeID() == compTypeID)
			components.erase(components.begin() + j);
		else
			j++;
	}
}

//insert component* into this entities components vector. Called when new components is inserted into component database. Called by ComponentDatabaseService.addComponent<type>(entity, component)
void ECSEntity::insert(Component* comp)
{	
	//set this components entity & ID
	comp->entity = this;
	comp->entityID = entityID;

	components.push_back(comp);
}

size_t ECSEntity::getEntityID()
{
	return entityID;
}

std::string ECSEntity::getEntityName()
{
	return entityName;
}