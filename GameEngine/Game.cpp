#include "Game.h"
#include "ECSEntity.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include <vector>
#include "ComponentDatabase.h"

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
	dante->addComponent<PhysicsComponent>(p2);

	for (size_t i = 0; i < healths.size(); i++)
		std::cout << healths.at(i).currentHealth << " AND ADDRESS: " << &(healths.at(i)) << std::endl;


	HealthComponent* ass = new HealthComponent();
	delete ass;
	
}

//tell SystemManager to update all systems
void Game::update()
{

}