#include "Game.h"
#include "ECSEntity.h"
#include "ComponentManager.h" //already included in ECSEntity.h but whatever
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include <vector>

//initialize game state
void Game::init()
{
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
	nero->addComponent<HealthComponent>(haaa);
	dante->addComponent<HealthComponent>(a);

	std::vector<HealthComponent>& healths = ComponentManager::getInstance().getAllComponents<HealthComponent>();

	nero->addComponent<PhysicsComponent>(p1);
	dante->addComponent<PhysicsComponent>(p2);

	for (size_t i = 0; i < healths.size(); i++)
		std::cout << healths.at(i).currentHealth << " AND ADDRESS: " << &(healths.at(i)) << std::endl;

	//eg of retrieving 1st component with specific entityID 
	health = ComponentManager::getInstance().getComponent<HealthComponent>(nero->getEntityID());
	if (health)
		std::cout << health->currentHealth << std::endl;
	else
		std::cout << "null pointer it was " << std::endl;
	
	ComponentManager::getInstance().removeComponents<HealthComponent>(nero->getEntityID());
	ComponentManager::getInstance().removeAllComponents<HealthComponent>();
}

//tell SystemManager to update all systems
void Game::update()
{

}