#include "Time.h"
#include <time.h>
#include <Windows.h>

double Time::deltaTime = 0;

double Time::getTime()
{
	LARGE_INTEGER time;
	LARGE_INTEGER freq;
	QueryPerformanceCounter(&time);
	QueryPerformanceFrequency(&freq);
	double ffreq = (double)freq.QuadPart;
	return time.QuadPart / ffreq;
}

void Time::setDeltaTime(double value)
{
	deltaTime = value;
}
