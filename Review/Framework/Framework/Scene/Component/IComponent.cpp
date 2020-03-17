#include "Framework.h"
#include "IComponent.h"

IComponent::IComponent(Context * context)
	: context(context)
	, bEnabled(false)
{
	id = GUIDGenerator::Generate();
}

template<typename T>
inline constexpr ComponentType IComponent::DeduceComponentType()
{
	return ComponentType::Unknown;
}

#define REGISTER_COMPONENT_TYPE(T, enumT) template <> ComponentType IComponent::DeduceComponentType<T>() { return enumT; }
REGISTER_COMPONENT_TYPE(Transform, ComponentType::Transform)
REGISTER_COMPONENT_TYPE(Renderable, ComponentType::Renderable)
REGISTER_COMPONENT_TYPE(Animator, ComponentType::Animator)
REGISTER_COMPONENT_TYPE(RigidBody, ComponentType::RigidBody)
REGISTER_COMPONENT_TYPE(AudioSource, ComponentType::AudioResource)
REGISTER_COMPONENT_TYPE(Scripter, ComponentType::Scripter)
REGISTER_COMPONENT_TYPE(Controller, ComponentType::Controller)
