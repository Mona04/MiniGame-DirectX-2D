#pragma once
#include "IWidget.h"

enum class Hierarchy_ClickedScope : uint
{
	None, Window, Scene, Actor, Component,
};

struct Hierarchy_ClickedData
{
	Hierarchy_ClickedScope scope;
	Hierarchy_ClickedScope scope_before;
	ComponentType type;
	bool isSelectedScene;
	Actor* actor;
};

class Widget_Hierarchy final : public IWidget
{
public:
	Widget_Hierarchy(class Context* context);
	~Widget_Hierarchy() = default;

	Widget_Hierarchy(const Widget_Hierarchy&) = delete;
	Widget_Hierarchy& operator=(const Widget_Hierarchy&) = delete;

	void Render() override;
	
private:
	void ShowHierarchy();
	void AddSceneInHierarchy(class Scene* scene);
	void AddActorInHierarchy(class Actor* actor);

private:
	void UpdateClickedData(const Hierarchy_ClickedScope& scope, class Actor* actor = nullptr, const enum class ComponentType& type = ComponentType::Unknown);
	const ImGuiTreeNodeFlags GetTreeNodeFlags(const Hierarchy_ClickedScope& scope, class Actor* actor, const enum class ComponentType& type = ComponentType::Unknown);

	void RightClickForWindow();
	void RightClickForScene();
	void RightClickForActor();
	void RightClickForComponent();

private:
	class Scene* CreateScene();

	class Actor* CreateEmptyActor();
	void AddComponentToActor(const std::string& name);
	void SetComponentOfActor(const std::string& name);

private:
	class SceneManager* sceneManager;
	class DataManager* dataManager;
	class Renderer* renderer;
	Hierarchy_ClickedData clicked_data;

};