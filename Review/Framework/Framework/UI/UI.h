#pragma once

class UI
{
private:
	friend UIManager;

private:
	UI(class Context* context);
	~UI();

	void Init();
	void Update();

	void LoadFromFile(const std::string& path);
	void SaveToFile(const std::string& path);

public:
	const bool& IsVisible() { return isVisible; }
	void SetIsVisible(const bool& var) { isVisible = var; }

	const std::string& GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	template <typename T> T* AddComponent();
	template <typename T> T* EraseComponent(const std::string& name);
	void DeleteComponent(IUIComponent* component);
	template <typename T> T* GetComponent();
	template <typename T> T* GetComponent(const std::string& name);
	template <typename T> std::vector<T*> GetComponents();
	template <typename T> const bool HasComponent();
	const bool HasComponent(const UIComponentType& type);
	std::vector<IUIComponent*>& GetComponents() { return components; }

protected:
	class Context* context;
	class Renderer* renderer;

	std::vector<class IUIComponent*> components;

	std::string name;
	bool isVisible;

	bool bInventory;
};

template<typename T>
inline T* UI::AddComponent()
{
	static_assert(std::is_base_of<IUIComponent, T>::value, "Provided type is not implied by IUIComponent");
	UIComponentType type = IUIComponent::DeduceComponentType<T>();

	T* newComponent = static_cast<T*>(components.emplace_back(new T(context)));

	return newComponent;
}

template<typename T>
inline T* UI::EraseComponent(const std::string& name)
{
	static_assert(std::is_base_of<IUIComponent, T>::value, "Provided type is not implied bt IUIComponent");
	UIComponentType type = IUIComponent::DeduceComponentType<T>();

	for (auto iter = components.begin(); iter != components.end();)
	{
		if ((*iter)->GetType() == type && (*iter)->GetName() == name)
		{
			auto result = *iter;
			iter = components.erase(iter);
			return static_cast<T*>(result);
		}
		else iter++;
	}
	return nullptr;
}

template<typename T>
inline T* UI::GetComponent()
{
	static_assert(std::is_base_of<IUIComponent, T>::value, "Provided type is not implied by IUIComponet");
	UIComponentType type = IUIComponent::DeduceComponentType<T>();

	for (auto& component : components) {
		if (component->GetType() == type)
			return static_cast<T*>(component);
	}
	return nullptr;
}

template<typename T>
inline T* UI::GetComponent(const std::string& name)
{
	static_assert(std::is_base_of<IUIComponent, T>::value, "Provided type is not implied by IUIComponet");
	UIComponentType type = IUIComponent::DeduceComponentType<T>();

	for (auto& component : components) {
		if (component->GetType() == type && component->GetName() == name)
			return static_cast<T*>(component);
	}
	return nullptr;
}

template<typename T>
inline std::vector<T*> UI::GetComponents()
{
	static_assert(std::is_base_of<IUIComponent, T>::value, "Provided type is not implied by IUIComponet");
	UIComponentType type = IUIComponent::DeduceComponentType<T>();

	std::vector<T*> result;
	for (auto& component : components) {
		if (component->GetType() == type)
			result.emplace_back(static_cast<T*>(component));
	}
	return result;
}

template<typename T>
inline const bool UI::HasComponent()
{
	static_assert(std::is_base_of<IUIComponent, T>::value, "Provided type does not implement IComponent");
	return HasComponent(IUIComponent::DeduceComponentType<T>());
}
