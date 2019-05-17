#pragma once
#include "Component.h"

class HealthComponent : public Component
{
public:
	//HealthComponent() {}
	//HealthComponent(size_t entityID) : Component(entityID) {}
	float currentHealth = 100;
	float maxHealth = 100;
	bool isDead;
};