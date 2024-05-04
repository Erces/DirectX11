#pragma once
#include <chrono>
class ErziTimer
{
public:
	ErziTimer();
	float Mark();
	float Peek() const;
private:
	std::chrono::steady_clock::time_point last;
};

