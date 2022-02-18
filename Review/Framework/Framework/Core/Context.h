#pragma once
#include "Framework.h"
#include "Framework/Core/Subsystem/ISubsystem.h"

class Context final
{
public:
	Context(class Engine* engine) : engine(engine) {}
	~Context()
	{
		for (auto iter = subsystems.rbegin(); iter != subsystems.rend(); iter++)
			SAFE_DELETE(*iter);
	}

	const bool InitializeSubsystems()
	{
		for (auto subsystem : subsystems)
		{
			if (!subsystem->Initialize())
				return false;
		}
		return true;
	}

	template <typename T>
	T* RegistSubsystem();
	
	template <typename T>
	void UnregistSubsystem();

	template <typename T>
	T* GetSubsystem();

	class Engine* GetEngine() { return engine; }

private:
	std::vector<class ISubsystem*> subsystems;
	class Engine* engine;
};

template<typename T>
inline T * Context::RegistSubsystem()
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type does not implement ISubsystem");
	return static_cast<T*>(subsystems.emplace_back(new T(this)));
}

template<typename T>
inline void Context::UnregistSubsystem()
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type does not implement ISubsystem");
	ISubsystem* sub = nullptr;
	for (auto iter = subsystems.begin(); iter != subsystems.end(); )
	{
		if (typeid(T) == typeid(**iter))
		{
			sub = *iter;
			subsystems.erase(iter);
			SAFE_DELETE(sub);
			break;
		}
		iter++;
	}
}

template<typename T>
inline T * Context::GetSubsystem()
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type does not implement ISubsystem");
	for (auto subsystem : subsystems)
	{
		if (typeid(T) == typeid(*subsystem))
			return static_cast<T*>(subsystem);
	}
	return nullptr;
}
