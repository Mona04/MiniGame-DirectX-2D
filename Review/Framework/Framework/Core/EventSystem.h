#pragma once
#include "Framework.h"

enum class EventType : uint
{
	Default_Update,
	Update,
	Render
};

#define EVENT_HANDLER_STATIC(func) []() {func();}
#define EVENT_HANDLER(func) [this](){ func(); }

class EventSystem final
{
public:
	typedef std::function<void()> Subscriber;

public:
	static EventSystem* Get()
	{
		static EventSystem instance;
		return &instance;
	}

	void Subscribe(const EventType& type, Subscriber&& subscriber)
	{
		subscribers[type].emplace_back(std::forward<Subscriber>(subscriber));
	}

	void Fire(const EventType& type)
	{
		for (const auto& subscriber : subscribers[type])
			subscriber();
	}
	
	void Clear()
	{
		subscribers.clear();
	}

private:
	EventSystem() = default;
	~EventSystem() = default;
	EventSystem(const EventSystem&) = delete;
	EventSystem& operator=(const EventSystem&) = delete;

private:
	std::map<EventType, std::vector<Subscriber>> subscribers;
};