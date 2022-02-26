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
	UIWidgetType type;
	IUIWidget* uiComponent;
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
	void AddUIComponentInHierarchy(class IUIWidget* uiComponent);

private:
	void UpdateClickedData(const UI_Hierarchy_ClickedScope& scope, class IUIWidget* actor = nullptr, const enum class UIWidgetType& type = UIWidgetType::Unknown);
	const ImGuiTreeNodeFlags GetTreeNodeFlags(const UI_Hierarchy_ClickedScope& scope, class IUIWidget* uiComponent, const enum class UIWidgetType& type = UIWidgetType::Unknown);

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