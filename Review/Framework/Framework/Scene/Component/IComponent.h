#pragma once
#include "Framework.h"

enum class ComponentType : uint
{
	Unknown,
	Transform,
	Renderable,
	Animator,
	RigidBody,
	AudioResource,
	Scripter,
	Controller,
//	Light,
//	Particle
};

class IComponent
{
public:
	template <typename T>
	static constexpr ComponentType DeduceComponentType();

public:
	IComponent(class Context* context);
	virtual ~IComponent() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

	const ComponentType& GetType() const { return type; }

	const bool& IsEnabled() { return bEnabled; }
	void setEnabled(const bool var) { bEnabled = var; }

	const uint& GetID() const { return id; }

protected:
	class Context* context;

	ComponentType type;
	bool bEnabled;

private:
	uint id;
};