#pragma once
#include "../ISubsystem.h"

class Timer final : public ISubsystem
{
public:
	Timer(class Context* context);
	~Timer() = default;

	const bool Initialize() override;

	float GetDeltaTimeMs() const { return deltaTimeMs_Return; }
	float GetDeltaTimeSec() const { return deltaTimeSec_Return; }

	void Update();

	const bool IsUpdatedFPS() { return isUpdatedFPS; }

private:
	float deltaTimeMs;
	float deltaTimeSec;
	float deltaTimeMs_Cumulated;
	float deltaTimeSec_Cumulated;
	float deltaTimeMs_Return;
	float deltaTimeSec_Return;

	float deltaTime1Sec;
	int deltaNumUpdated;

	bool isUpdatedFPS;

	std::chrono::high_resolution_clock::time_point prevTime;
};