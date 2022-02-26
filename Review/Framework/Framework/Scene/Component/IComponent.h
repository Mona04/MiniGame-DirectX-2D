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
	Camera
//	Light,
//	Particle
};

class IComponent
{
public:
	friend class Actor;
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
	class Actor* GetOwner() { return owner; }

protected:
	class Context* context;
	class Actor* owner;

	ComponentType type;
	bool bEnabled;

private:
	uint id;
};