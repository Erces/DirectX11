#include "ErziTimer.h"

using namespace std::chrono;

ErziTimer::ErziTimer()
{
	
	last = steady_clock::now();
}

float ErziTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;

	return frameTime.count();
}

float ErziTimer::Peek() const
{
	return duration<float>(steady_clock::now()- last).count();
}
