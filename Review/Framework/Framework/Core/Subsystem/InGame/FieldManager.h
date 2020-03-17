#pragma once
#include "../ISubsystem.h"

class FieldManager final : public ISubsystem
{
public:
	FieldManager(class Context* context);
	~FieldManager();

	const bool Initialize() override;
	void Update();
};