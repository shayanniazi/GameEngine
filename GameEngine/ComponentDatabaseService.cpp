#include "ComponentDatabaseService.h"

ComponentDatabaseService* ComponentDatabaseService::instance = nullptr;

ComponentDatabaseService::ComponentDatabaseService()
{
	componentDB.reserve(m_maxComponentTypes);
	garbage.reserve(1000); //reserve an arbitrary amount of memory for 1000 addresses to empty/garbage vectors
}

ComponentDatabaseService::~ComponentDatabaseService()
{
}

ComponentDatabaseService& ComponentDatabaseService::getInstance()
{
	if (instance == nullptr)
		instance = new ComponentDatabaseService();

	return *instance;
}

void ComponentDatabaseService::cleanGarbage()
{
	for (size_t i = 0; i < garbage.size(); i++)
		delete (std::vector<Component*>*) garbage.at(i);

	if (!garbage.empty())
		garbage.clear();
}
