#pragma once
#include "IWidget.h"

class Widget_ToolBar final : public IWidget
{
public:
	Widget_ToolBar(class Context* context);
	~Widget_ToolBar() = default;

	Widget_ToolBar(const Widget_ToolBar&) = delete;
	Widget_ToolBar& operator=(const Widget_ToolBar&) = delete;

	void Render() override;

private:

};