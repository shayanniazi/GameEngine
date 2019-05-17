#pragma once

#include "SubSystems.h"
#include "Display.h"
#include "CoreEngine.h"
#include <iostream>

#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ECSEntity.h"
#include "ComponentManager.h"
#include <boost/container/flat_map.hpp>

int main(int argc, char** argv)
{	
	//CoreEngine* engine = CoreEngine::getEngineInstance();

	//test code
	ECSEntity* nero = new ECSEntity();
	ECSEntity* dante = new ECSEntity();

	HealthComponent* health = new HealthComponent(); 
	HealthComponent* h3 = new HealthComponent();
	HealthComponent* haaa = new HealthComponent();
	HealthComponent* a = new HealthComponent();
	PhysicsComponent* p1 = new PhysicsComponent();
	PhysicsComponent* p2 = new PhysicsComponent();
	
	health->currentHealth = 101;
	h3->currentHealth = 1;
	haaa->currentHealth = 2;
	a->currentHealth = 3;

	nero->addComponent<HealthComponent>(health); 
	dante->addComponent<HealthComponent>(h3);

	std::cout << health << "NERO ADDRESS" << std::endl;
	std::cout << h3 << "DANTE ADDRESS" << std::endl;

	std::vector<HealthComponent>& healths = ComponentManager::getInstance().getComponents<HealthComponent>();
	for (int i = 0; i < healths.size(); i++)
		std::cout << healths.at(i).currentHealth << " AND ADDRESS: " << &(healths.at(i)) << std::endl;

	//delete engine;
	return 0;
}