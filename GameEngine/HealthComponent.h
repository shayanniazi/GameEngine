#pragma once
#include "Component.h"

class HealthComponent : public Component
{
public:
	float currentHealth = 100;
	float maxHealth = 100;
	bool isDead;
};