#include "Game.h"
#include "ECSEntity.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include <vector>
#include "ComponentDatabase.h"
#include "EntityDatabase.h"
#include "SystemManager.h"
#include "HealthSystem.h"

/*
Little description on how to make a game with this framework:

1) Create entities (entity pointers), you can destroy those entities, upon which the entity database will remove the entity and tag all its corresponding
   components to be deleted by systems that act upon those components

2a) Create components. You should NOT delete components, otherwise you're just asking for undefined behavior and possibly a program crash
   you should only tell componentDatabase to remove component or tell entity to remove component.
2b) Call getComponents<>(entity) when you know the entity HAS said component, otherwise it might return a nullptr or an empty reference and the program
    may crash

3) Create Systems using SystemManager. They will register themselves into the system database and will be updated 
   automatically by the Engine.
   Order of instantiation for systems doesn't have an effect on components or entities having to be 
   initialized before systems, since updating  takes place after game::init 

*/


//initialize game state
void Game::init()
{
	ECSEntity* nero = new ECSEntity("nero");
	ECSEntity* dante = new ECSEntity("dante");
	
	HealthComponent* health = new HealthComponent();
	HealthComponent* health2 = new HealthComponent();

	PhysicsComponent* p1 = new PhysicsComponent();
	
	health->currentHealth = 101;
	health2 ->currentHealth = 1;

	
	nero->addComponent<HealthComponent>(health);
	dante->addComponent<HealthComponent>(health2);
	
	const std::vector<HealthComponent>& healths = ComponentDatabase::getAllComponents<HealthComponent>();

	nero->addComponent<PhysicsComponent>(p1);

	SystemManager::registerSystem<HealthSystem>();
}