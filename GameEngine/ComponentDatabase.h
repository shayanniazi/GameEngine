#pragma once
#include "ComponentDatabaseService.h" //obtains access to private members using friend class 'pass'
#include <vector>

class ComponentDatabase
{
public:
	static ComponentDatabase& getInstance();

	template<typename componentType>
	const std::vector<componentType>& getAllComponents()
	{
		return ComponentDatabaseService::getInstance().getAllComponents<componentType>();
	}

private:
	ComponentDatabase();
	~ComponentDatabase();

	static	ComponentDatabase* instance;
};