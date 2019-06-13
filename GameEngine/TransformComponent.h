#pragma once
#include "Component.h"
#include "Vec3.h"

class TransformComponent : public Component
{
public:
	Vec3 position = Vec3(0,0,2);
	Vec3 scale = Vec3(0.25,0.25,0.25);
	Vec3 orientation = Vec3(0,0,0);
};