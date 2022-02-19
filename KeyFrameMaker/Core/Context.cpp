#include "stdafx.h"
#include "Context.h"

const bool Context::InitializeSubsystems()
{
	for (auto subsystem : subsystems)
	{
		if (!subsystem->Initialize())
			return false;
	}
	return true;
}