#include "ComponentDatabaseService.h"
#include "ECSEntity.h"

size_t ComponentDatabaseService::maxEntities = 100000;
size_t ComponentDatabaseService::maxComponentTypes = 10000;

boost::container::flat_map<void*, size_t>* ComponentDatabaseService::componentDB = new boost::container::flat_map<void*, size_t>();
std::vector<void*>* ComponentDatabaseService::garbage = new std::vector<void*>();

//reseve/preallocate vector storage space in heap for database & garbage data in CoreEngine.engineSetup();
void ComponentDatabaseService::initializeStorage()
{
	componentDB->reserve(maxComponentTypes);
	garbage->reserve(1000); //reserve an arbitrary amount of memory for 1000 addresses to empty/garbage vectors
}

void ComponentDatabaseService::cleanGarbage()
{
	//if garbage has some stuff in it to be cleaned 
	if (!garbage->empty())
	{
		//freeing up storage used by temporary vectors (which were created as placeholders in getComponent<>() functions)
		for (size_t i = 0; i < garbage->size(); i++)
			delete (std::vector<Component*>*) garbage->at(i);

		//clear garbage after freeing up memory
		garbage->clear();

		std::cout << "garbage cleaned " << std::endl;
	}
}