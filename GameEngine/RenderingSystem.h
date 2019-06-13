#pragma once
#include "System.h"

class RenderingSystem : public System
{
	virtual void update() override;
	virtual void draw() override;
};