#include "Game.h"
#include "ECSEntity.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include <vector>
#include "ComponentDatabase.h"
#include "EntityDatabase.h"

/*
Little description on how to make a game with this framework:

1) Create entities (entity pointers), you can destroy those entities, upon which the entity database will remove the entity and tag all its corresponding
   components to be deleted by systems that act upon those components

2a) Create components. You should NOT delete components, otherwise you're just asking for undefined behavior and possibly a program crash
   you should only tell componentDatabase to remove component or tell entity to remove component.
2b) Call getComponents<>(entity) when you know the entity HAS said component, otherwise it might return a nullptr or an empty reference and the program
    may crash

3) Create Systems (system pointers). They will automatically register themselves into the system database and will be updated automatically by the
   Engine.

*/


//initialize game state
void Game::init()
{
	ECSEntity* nero = new ECSEntity("nero");
	ECSEntity* dante = new ECSEntity("dante");
	
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
	nero->addComponent<HealthComponent>(haaa);
	dante->addComponent<HealthComponent>(a);
	
	const std::vector<HealthComponent>& healths = ComponentDatabase::getAllComponents<HealthComponent>();

	nero->addComponent<PhysicsComponent>(p1);
	//dante->addComponent<PhysicsComponent>(p2);

	for (size_t i = 0; i < healths.size(); i++)
		std::cout << healths.at(i).currentHealth << " AND OWNER: " << healths.at(i).getOwner()->getEntityName() << std::endl;
}