#pragma once

class System
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	System();
	~System();
};