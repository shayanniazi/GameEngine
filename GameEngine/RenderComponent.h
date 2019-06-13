#pragma once
#include "Component.h"
#include "Model.h"
#include <memory>

class RenderComponent : public Component
{
public:
	std::shared_ptr<Model> model;
};