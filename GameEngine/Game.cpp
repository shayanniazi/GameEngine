#include "Game.h"
#include "ECSEntity.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include <vector>
#include "ComponentDatabase.h"
#include "EntityDatabase.h"
#include "SystemManager.h"
#include "HealthSystem.h"
#include "ModelLoader.h"
#include "RenderComponent.h"
#include "RenderingSystem.h"
#include "TransformComponent.h"
#include "Camera.h"

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
	
	TransformComponent* neroTransform = new TransformComponent();
	nero->addComponent<TransformComponent>(neroTransform);
	neroTransform->position = Vec3(0.3f, 0.3f, 0.3f);
	neroTransform->scale = Vec3(0.25,0.25,0.25);

	RenderComponent* neroRender = new RenderComponent();
	neroRender->model = ModelLoader::loadOBJ("Cube.obj");
	nero->addComponent<RenderComponent>(neroRender);

	ECSEntity* dante = new ECSEntity("dante");
	
	TransformComponent* danteTransform = new TransformComponent();
	danteTransform->position = Vec3(0.1, 0.1, 0.1);
	danteTransform->scale = Vec3(1,1,1);

	dante->addComponent<TransformComponent>(danteTransform);

	RenderComponent* renderComp = new RenderComponent(); 
	renderComp->model = ModelLoader::loadModel("Boat.obj");
	dante->addComponent<RenderComponent>(renderComp);
	

	/*
	HealthComponent* health = new HealthComponent(); health->currentHealth = 101;
	HealthComponent* health2 = new HealthComponent(); health2->currentHealth = 1;
	nero->addComponent<HealthComponent>(health);
	dante->addComponent<HealthComponent>(health2);
	
	SystemManager::registerSystem<HealthSystem>();
	*/

	Camera* camera = new Camera();
	camera->setActive();
	//set cameras viewDirection to be that of the entities position
	camera->viewDirection = dante->getComponent<TransformComponent>()->position; //Vec3(0.3, 0.3, -0.9);

	SystemManager::registerSystem<RenderingSystem>();
}