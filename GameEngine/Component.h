#pragma once
#include <iostream>

class ECSEntity; //forward declaration

class Component
{
public:
	size_t getTypeID() const;
	ECSEntity* const getOwner() const;
	~Component();

private:
	friend class ComponentDatabaseService; 
	friend class ECSEntity; 

	ECSEntity* entity = nullptr;
	size_t componentTypeID;
	size_t entityID;
	//void operator delete(void* mem);
};