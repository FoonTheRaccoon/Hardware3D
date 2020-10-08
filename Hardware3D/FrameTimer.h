#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float Mark();
	float TimeSinceStart();
	float TimeSinceLast();
private:
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point startTime;
};