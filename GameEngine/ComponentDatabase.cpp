#include "ComponentDatabase.h"

ComponentDatabase* ComponentDatabase::instance = nullptr;

ComponentDatabase& ComponentDatabase::getInstance()
{
	if (instance == nullptr)
		instance = new ComponentDatabase();
	return *instance;
}