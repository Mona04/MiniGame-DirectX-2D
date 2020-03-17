#pragma once
#include "IWidget.h"

enum class UI_Hierarchy_ClickedScope : uint
{
	None, Window, UI, UIComponent
};

struct UI_Hierarchy_ClickedData
{
	UI_Hierarchy_ClickedScope scope;
	UI_Hierarchy_ClickedScope scope_before;
	UIComponentType type;
	IUIComponent* uiComponent;
};

class Widget_UI_Hierarchy final : public IWidget
{
public:
	Widget_UI_Hierarchy(class Context* context);
	~Widget_UI_Hierarchy() = default;

	Widget_UI_Hierarchy(const Widget_UI_Hierarchy&) = delete;
	Widget_UI_Hierarchy& operator=(const Widget_UI_Hierarchy&) = delete;

	void Render() override;

private:
	void ShowHierarchy();
	void AddUIInHierarchy(class UI* ui);
	void AddUIComponentInHierarchy(class IUIComponent* uiComponent);

private:
	void UpdateClickedData(const UI_Hierarchy_ClickedScope& scope, class IUIComponent* actor = nullptr, const enum class UIComponentType& type = UIComponentType::Unknown);
	const ImGuiTreeNodeFlags GetTreeNodeFlags(const UI_Hierarchy_ClickedScope& scope, class IUIComponent* uiComponent, const enum class UIComponentType& type = UIComponentType::Unknown);

	void RightClickForWindow();
	void RightClickForUI();
	void RightClickForUIComponent();

private:
	class UI* CreateUI();

private:
	class UIManager* uiManager;
	class Renderer* renderer;
	UI_Hierarchy_ClickedData clicked_data;
};