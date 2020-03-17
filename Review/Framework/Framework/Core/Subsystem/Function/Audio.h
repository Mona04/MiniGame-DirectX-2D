#pragma once
#include "../ISubsystem.h"

class Audio final : public ISubsystem
{
public:
	Audio(class Context* context);
	~Audio();

	const bool Initialize() override;

	auto GetFMODSystem() const->FMOD::System* { return system; }
	void Update();

private:
	FMOD::System* system;
	float distanceFactor;
	int maxChannel;
	int result;
	bool bInitialized;
};