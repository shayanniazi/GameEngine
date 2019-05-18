#pragma once
#include <typeinfo>

class Component
{
public:
	//Component();
	//Component(size_t entityID);
	Component** componentPtrHandle = nullptr; //all components wil inherit this and only 1 unique component will exist per object
	virtual ~Component();
	size_t getTypeID() const;
	size_t getEntityID(); //returns the entity ID this component belongs to
	void setEntityID(size_t entityID);
private:
	size_t componentTypeID;
	size_t entityID;
};