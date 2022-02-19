#pragma once
#include "ISubsystem.h"

class Timer final : public ISubsystem
{
public:
	Timer(class Context* context);
	~Timer() = default;

	const bool Initialize() override;

	const float& GetDeltaTimeMs() const { return deltaTimeMs; }
	const float& GetDeltaTimeSec() const { return deltaTimeSec; }

	void Update();

	const bool& IsUpdatedFPS() { return isUpdatedFPS; }

private:
	float deltaTimeMs;
	float deltaTimeSec;
	float deltaTimeCumulated;

	float deltaTime1Sec;
	int deltaNumUpdated;

	bool isUpdatedFPS;

	std::chrono::high_resolution_clock::time_point prevTime;
};