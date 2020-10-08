#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
	startTime = steady_clock::now();
}

float FrameTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float FrameTimer::TimeSinceStart()
{
	const auto now = steady_clock::now();
	const duration<float> frameTime = now - startTime;
	return frameTime.count();
}

float FrameTimer::TimeSinceLast()
{
	const auto now = steady_clock::now();
	const duration<float> frameTime = now - last;
	return frameTime.count();
}
