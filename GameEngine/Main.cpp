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

	HealthComponent* health = new HealthComponent(); health->currentHealth = 2222;
	HealthComponent* h3 = new HealthComponent();
	HealthComponent* haaa = new HealthComponent(333);
	HealthComponent* a = new HealthComponent();
	PhysicsComponent* p1 = new PhysicsComponent();
	PhysicsComponent* p2 = new PhysicsComponent();

	ComponentManager* comp = new ComponentManager();

	comp->addComponent<HealthComponent>(1, health);
	comp->addComponent<HealthComponent>(1, a); 
	comp->addComponent<HealthComponent>(1, h3); 
	comp->addComponent<PhysicsComponent>(1, p1);
	comp->addComponent<PhysicsComponent>(1, p2);
	comp->addComponent<HealthComponent>(1, h3);
	comp->addComponent<PhysicsComponent>(1, p2);




	//new code end

	//test code end

	//delete engine;
	return 0;
}