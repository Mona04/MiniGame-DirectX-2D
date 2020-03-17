#pragma once
#include "IWidget.h"

class Widget_MenuBar final : public IWidget
{
public:
	Widget_MenuBar(class Context* context);
	~Widget_MenuBar() = default;

	Widget_MenuBar(const Widget_MenuBar&) = delete;
	Widget_MenuBar& operator=(const Widget_MenuBar&) = delete;

	void Begin() override {}
	void Render() override;
	void End() override {};
	
private:
	bool bShowMetricsWindow;
	bool bShowStyleEditor;
	bool bShowDemoWindow;
	bool bShowScriptTool;
};