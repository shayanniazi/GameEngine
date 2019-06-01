#include "HealthSystem.h"
#include "ComponentDatabase.h"
#include "HealthComponent.h"
#include "ECSEntity.h"

void HealthSystem::update()
{
	std::vector<HealthComponent>& healths = ComponentDatabase::getAllComponents<HealthComponent>();

	for (size_t i = 0; i < healths.size(); i++)
	{
		healths.at(i).currentHealth = healths.at(i).currentHealth + 1;
		//std::cout << "Entity: " << healths.at(i).getOwner()->getEntityName() << " and its health: " << healths.at(i).currentHealth <<std::endl;
	}
}