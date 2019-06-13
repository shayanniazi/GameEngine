#pragma once

class Time
{
public:
	static double deltaTime;
private:
	friend class CoreEngine;

	static double getTime();
	static void setDeltaTime(double value);
};

