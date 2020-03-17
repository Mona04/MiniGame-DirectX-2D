#pragma once
#include <chrono>

class Timer final
{
private:
	Timer() : delta_time_ms(0.0f) { Initialize(); };
	~Timer() = default;

public:
	static Timer* Get() { static Timer instance; return &instance; }

	const bool Initialize()
	{
		previous_time = std::chrono::high_resolution_clock::now();
		return true;
	}

	const float GetDeltaTimeMs() { return static_cast<float>(delta_time_ms); }
	const float GetDeltaTimeSec() { return static_cast<float>(delta_time_ms * 0.001f); }

	void Update();

private:
	double delta_time_ms;

	std::chrono::high_resolution_clock::time_point previous_time;
};

