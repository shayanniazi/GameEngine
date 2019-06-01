#pragma once

class Component; //forward declaration

class HealthComponent : public Component
{
public:
	float currentHealth = 100;
	float maxHealth = 100;
	bool isDead;
};