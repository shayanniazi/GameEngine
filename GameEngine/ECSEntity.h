#pragma once
#include <vector>

class ECSEntity
{
public:
	ECSEntity();
	~ECSEntity();
	void removeEntity(); //puts the entity ID back into reusable pool of ID's
	size_t getEntityID();
private:
	static std::vector<size_t> reusableIDPool;
	static size_t IDCounter;
	size_t entityID;
};

