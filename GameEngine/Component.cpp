#include "Component.h"

/*Component::Component() { }
Component::Component(size_t entityID)
{
	this->entityID = entityID;
}
*/
Component::~Component()
{

}

size_t Component::getTypeID() const
{
	return typeid(*this).hash_code();
}