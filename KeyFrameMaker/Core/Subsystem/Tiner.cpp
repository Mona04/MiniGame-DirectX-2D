#include "stdafx.h"
#include "Timer.h"

#define FPS 1.0f/60.0f

Timer::Timer(Context * context)
	: ISubsystem(context)
	, deltaTimeMs(0.0f)
	, deltaTimeSec(0.0f)
	, deltaTimeCumulated(0.0f)
	, deltaNumUpdated(0.0f)
{
}

const bool Timer::Initialize()
{
	prevTime = std::chrono::high_resolution_clock::now();
	return true;
}

void Timer::Update()
{
	auto curTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms = curTime - prevTime;
	prevTime = curTime;

	deltaTimeMs = static_cast<float>(ms.count());
	deltaTimeSec = static_cast<float>(ms.count() * 0.001);

	deltaTimeCumulated += deltaTimeSec;

	if (deltaTimeCumulated > FPS)
	{
		deltaTimeCumulated -= FPS;
		deltaNumUpdated += 1;
		if (deltaNumUpdated > 60)
			deltaTimeCumulated = 0;
		isUpdatedFPS = true;
	}
	else
	{
		isUpdatedFPS = false;
	}

	deltaTime1Sec += deltaTimeSec;

	if (deltaTime1Sec > 1.0f)
	{
		SetWindowTextA(Setting::Get()->GetHWND(), std::to_string(deltaNumUpdated).c_str());
		deltaTime1Sec = 0;
		deltaNumUpdated = 0;
	}
}
