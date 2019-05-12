#include "Time.h"

Time::Time()
{

}


Time::~Time()
{
}

double Time::getTime()
{
	LARGE_INTEGER time;
	LARGE_INTEGER freq;
	QueryPerformanceCounter(&time);
	QueryPerformanceFrequency(&freq);
	double ffreq = (double)freq.QuadPart;
	return time.QuadPart / ffreq;
}
