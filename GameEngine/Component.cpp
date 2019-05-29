#include "Component.h"
#include <typeinfo>
#include <iostream>
#include "ECSEntity.h"
#include "ComponentDatabase.h"

/*Component::Component() { }
Component::Component(size_t entityID)
{
	this->entityID = entityID;
}
*/
void Component::operator delete(void* mem)
{
	
	free(mem);
}

Component::~Component()
{

	if (entity)
	{
		//entity->removeComponent<type>(this); 
		ComponentDatabaseService::removeComponent<componentType>()

	}

	std::cout << "MY TURN MOTHERFUCKERF" << std::endl;


}

size_t Component::getTypeID() const
{
	return typeid(*this).hash_code();
}