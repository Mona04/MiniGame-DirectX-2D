#include "pch.h"
#include "Timer.h"

void Timer::Update()
{
	std::chrono::steady_clock::time_point current_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms = current_time - previous_time;
	previous_time = current_time;
	delta_time_ms = ms.count();
}
