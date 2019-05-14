#pragma once
#include "Component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent() {}
	PhysicsComponent(size_t entityID) : Component(entityID) {}
};