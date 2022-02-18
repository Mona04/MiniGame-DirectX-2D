#include "stdafx.h"
#include "Widget_ToolBar.h"
#include "Framework/Core/Engine.h"

Widget_ToolBar::Widget_ToolBar(Context* context)
	: IWidget(context)
{
	title = "ToolBar";
}

void Widget_ToolBar::Render()
{
	if (IconProvider::Get()->ImageButton(IconType::Button_Play, ImVec2(15.0f, 15.0f)))
	{
		context->GetEngine()->ToggleEngineFlags(EngineFlags::ENGINEFLAGS_PLAY);
	}
}
