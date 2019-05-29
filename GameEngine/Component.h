#pragma once

class ECSEntity; //forward declaration

class Component
{
public:
	//Component();
	//Component(size_t entityID);
	
	void operator delete(void* mem);
	size_t getTypeID() const;
	size_t entityID;
	ECSEntity* entity = nullptr;

private:
	size_t componentTypeID;
	virtual ~Component();

};