#pragma once
#include "Component.h"

class Component; //forward declaration

class TagComponent : public Component
{
public:
	std::string tag = "nil";
};