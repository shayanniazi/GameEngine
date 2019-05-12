#pragma once
#include <typeinfo>

class Component
{
public:
	Component();
	Component(size_t entityID);
	virtual ~Component();
	size_t getTypeID() const;
	size_t getEntityID(); //returns the entity ID this component belongs to
	void setEntityID(size_t entityID);
private:
	size_t componentTypeID;
	size_t entityID;

};