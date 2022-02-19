#pragma once
#include "Core/Subsystem/ISubsystem.h"

class Context final
{
public:
	Context() = default;
	~Context()
	{
		for (auto subsystem : subsystems)
			SAFE_DELETE(subsystem);
	}

	const bool InitializeSubsystems();

	template <typename T>
	T* RegisterSubsystem();

	template <typename T>
	T* GetSubsystem();

private:
	std::vector<class ISubsystem*> subsystems;
};

template<typename T>
inline T* Context::RegisterSubsystem()
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type does not implement ISubsystem");
	return static_cast<T*>(subsystems.emplace_back(new T(this)));
}

template<typename T>
inline T* Context::GetSubsystem()
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type does not implement ISubsystem");
	for (auto subsystem : subsystems)
	{
		if (typeid(T) == typeid(*subsystem))
			return static_cast<T*>(subsystem);
	}
	return nullptr;
}
