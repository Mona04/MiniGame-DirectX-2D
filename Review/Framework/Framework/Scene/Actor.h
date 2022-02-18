#pragma once

class Actor
{
public:
    Actor(class Context* context);
    virtual ~Actor();

	void LoadFromFile(const std::string& path);
	void SaveToFile(const std::string& path);

	void Clear();

	const std::string& GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	const bool& IsActive() { return bActive;}
	void SetActive(const bool& var) { bActive = var; }

	const bool& IsCameraAttached() { return isCameraAttacted; }
	void SetIsCameraAttached(const bool& var) { isCameraAttacted = var; }

	void SetTimeLimit(const float& timeLimit) { this->timeLimit = timeLimit; timeFlowed = 0; }

    void Update();
    void Render();

	template <typename T> T* AddComponent();
	template <typename T> void EraseComponent();
	template <typename T> T* GetComponent();
	template <typename T> const std::vector<T*> GetComponents();
	template <typename T> const bool HasComponent();
	const bool HasComponent(const ComponentType& type);

private:
    class Context* context;
	class Timer* timer;

	std::string name;
	bool bActive;
	float timeLimit;
	float timeFlowed;

	std::vector<IComponent*> components;
	bool isCameraAttacted;
};

template<typename T>
inline T * Actor::AddComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provided type does not implement IComponent");
	ComponentType type = IComponent::DeduceComponentType<T>();

	if (HasComponent(type) && type != ComponentType::Scripter)
		return GetComponent<T>();

	T* newComponent =  static_cast<T*>(components.emplace_back(new T(context)));
	newComponent->owner = this;

	return newComponent;
}

template<typename T>
inline void Actor::EraseComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provided type does not implement IComponent");
	ComponentType type = IComponent::DeduceComponentType<T>();

	for (auto iter = components.begin(); iter != components.end(); ) {
		if ((*iter)->GetType() == type)
		{
			SAFE_DELETE(*iter);
			iter = components.erase(iter);
		}
		else iter++;
	}
}

template<typename T>
inline T * Actor::GetComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provided type does not implement IComponent");
	ComponentType type = IComponent::DeduceComponentType<T>();

	for (auto& component : components) {
		if (component->GetType() == type)
			return static_cast<T*>(component);
	}
	return nullptr;
}

template<typename T>
inline const std::vector<T*> Actor::GetComponents()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provided type does not implement IComponent");
	ComponentType type = IComponent::DeduceComponentType<T>();
	std::vector<T*> tmp;
	for (auto& component : components) {
		if (component->GetType() == type)
			tmp.emplace_back(static_cast<T*>(component));
	}

	return tmp;
}

template<typename T>
inline const bool Actor::HasComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Provided type does not implement IComponent");
	return HasComponent(IComponent::DeduceComponentType<T>());
}

