#pragma once
#include "System.h"

class HealthSystem : public System
{
	virtual void update () override;
	virtual void draw() override;
};