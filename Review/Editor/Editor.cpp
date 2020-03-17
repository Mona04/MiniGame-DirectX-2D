#include "stdafx.h"
#include "Editor.h"
#include "Framework/Core/Engine.h"

#include "Widget/IWidget.h"
#include "Widget/Widget_MenuBar.h"
#include "Widget/Widget_ToolBar.h"
#include "Widget/Widget_Assets.h"
#include "Widget/Widget_Hierarchy.h"
#include "Widget/Widget_Inspector.h"
#include "Widget/Widget_UI_Inspector.h"
#include "Widget/Widget_UI_Hierarchy.h"
#include "Widget/Widget_Data_Inspector.h"
#include "Widget/Widget_Log.h"
#include "Widget/Widget_Scene.h"

Editor::Editor()
	:bUseDockspace(true)
{
	widgets.emplace_back(new Widget_Log(context));

	engine = Engine::Get();
	engine->SetEngineFlags(EngineFlags::ENGINEFLAGS_RENDER | EngineFlags::ENGINEFLAGS_UPDATE | EngineFlags::ENGINEFLAGS_EDITOR);
	context = engine->GetContext();
	graphics = context->GetSubsystem<Graphics>();
	
	IconProvider::Get()->Initialize(context);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcon;
	io.ConfigResizeWindowsFromEdges = true;

	ImGui_ImplWin32_Init(Setting::Get()->GetWindowHandle());
	ImGui_ImplDX11_Init(graphics->GetDevice(), graphics->GetDeviceContext());
	ApplyStyle();

	widgets.emplace_back(new Widget_MenuBar(context));
	widgets.emplace_back(new Widget_ToolBar(context));
	widgets.emplace_back(new Widget_Assets(context));
	widgets.emplace_back(new Widget_Hierarchy(context));
	widgets.emplace_back(new Widget_Inspector(context));
	widgets.emplace_back(new Widget_UI_Inspector(context));
	widgets.emplace_back(new Widget_UI_Hierarchy(context));
	widgets.emplace_back(new Widget_Data_Inspector(context));
	widgets.emplace_back(new Widget_Scene(context));

	ToolScript::Get()->Initialize(context);
}

Editor::~Editor()
{
	for (auto& widget : widgets)
		SAFE_DELETE(widget);

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Editor::Resize(const uint & width, const uint & height)
{
}

void Editor::Update()
{
	engine->Update();
}

void Editor::Render()
{
	if (engine->IsDestroy())
		return;

	graphics->BeginScene();
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			BeginDockspace();
			{
				for (auto& widget : widgets)
				{
					widget->Begin();
					widget->Render();
					widget->End();
				}

				ToolScript::Get()->Render();
			}
			EndDockspace();
		}

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
	graphics->EndScene();
	
	//engine->Render();
}

void Editor::BeginDockspace()
{
	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	{
		ImGui::Begin("DockingPannel", &bUseDockspace, windowFlags);
	}
	ImGui::PopStyleVar(3);  // 3개 잘 맞춰라

	ImGuiID id = ImGui::GetID("MyEditor");  // My Editor 은 default;
	if (!ImGui::DockBuilderGetNode(id))
	{
		ImGui::DockBuilderRemoveNode(id);
		ImGui::DockBuilderAddNode(id, ImGui::GetMainViewport()->Size);

		ImGuiID main = id;
		ImGuiID up = ImGui::DockBuilderSplitNode(main, ImGuiDir_Up, 0.1f, nullptr, &main);
		ImGuiID right = ImGui::DockBuilderSplitNode(main, ImGuiDir_Right, 0.3f, nullptr, &main);
		ImGuiID down = ImGui::DockBuilderSplitNode(main, ImGuiDir_Down, 0.3f, nullptr, &main);
		ImGuiID right_right = ImGui::DockBuilderSplitNode(right, ImGuiDir_Right, 0.5f, nullptr, &right);
		ImGuiID down_right = ImGui::DockBuilderSplitNode(down, ImGuiDir_Right, 0.5f, nullptr, &down);

		ImGui::DockBuilderDockWindow("Scene", main);
		ImGui::DockBuilderDockWindow("ToolBar", up);
		ImGui::DockBuilderDockWindow("Hierarchy", right);
		ImGui::DockBuilderDockWindow("Inspector", right_right);
		ImGui::DockBuilderDockWindow("UI_Hierarchy", right_right);
		ImGui::DockBuilderDockWindow("UI_Inspector", right_right);
		ImGui::DockBuilderDockWindow("Data_Inspector", right_right);
		ImGui::DockBuilderDockWindow("Assets", down);
		ImGui::DockBuilderDockWindow("Log", down_right);
		ImGui::DockBuilderFinish(id);
	}

	ImGui::DockSpace(id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruDockspace);
}

void Editor::EndDockspace()
{
	ImGui::End();
}

void Editor::ApplyStyle()
{
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	float fontSize = 15.0f;
	float roundness = 2.0f;
	ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 text = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
	ImVec4 black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 backgroundVeryDark = ImVec4(0.08f, 0.086f, 0.094f, 1.00f);
	ImVec4 backgroundDark = ImVec4(0.117f, 0.121f, 0.145f, 1.00f);
	ImVec4 backgroundMedium = ImVec4(0.26f, 0.26f, 0.27f, 1.0f);
	ImVec4 backgroundLight = ImVec4(0.37f, 0.38f, 0.39f, 1.0f);
	ImVec4 highlightBlue = ImVec4(0.172f, 0.239f, 0.341f, 1.0f);
	ImVec4 highlightBlueHovered = ImVec4(0.202f, 0.269f, 0.391f, 1.0f);
	ImVec4 highlightBlueActive = ImVec4(0.382f, 0.449f, 0.561f, 1.0f);
	ImVec4 barBackground = ImVec4(0.078f, 0.082f, 0.09f, 1.0f);
	ImVec4 bar = ImVec4(0.164f, 0.180f, 0.231f, 1.0f);
	ImVec4 barHovered = ImVec4(0.411f, 0.411f, 0.411f, 1.0f);
	ImVec4 barActive = ImVec4(0.337f, 0.337f, 0.368f, 1.0f);

	// Spatial
	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.FramePadding = ImVec2(5, 5);
	style.ItemSpacing = ImVec2(6, 5);
	style.Alpha = 1.0f;
	style.WindowRounding = roundness;
	style.FrameRounding = roundness;
	style.PopupRounding = roundness;
	style.GrabRounding = roundness;
	style.ScrollbarSize = 20.0f;
	style.ScrollbarRounding = roundness;

	// Colors
	style.Colors[ImGuiCol_Text] = text;
	style.Colors[ImGuiCol_WindowBg] = backgroundDark;
	style.Colors[ImGuiCol_Border] = black;
	style.Colors[ImGuiCol_FrameBg] = bar;
	style.Colors[ImGuiCol_FrameBgHovered] = highlightBlue;
	style.Colors[ImGuiCol_FrameBgActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_TitleBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_TitleBgActive] = bar;
	style.Colors[ImGuiCol_MenuBarBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_ScrollbarBg] = barBackground;
	style.Colors[ImGuiCol_ScrollbarGrab] = bar;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = barHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = barActive;
	style.Colors[ImGuiCol_CheckMark] = white;
	style.Colors[ImGuiCol_SliderGrab] = bar;
	style.Colors[ImGuiCol_SliderGrabActive] = barActive;
	style.Colors[ImGuiCol_Button] = barActive;
	style.Colors[ImGuiCol_ButtonHovered] = highlightBlue;
	style.Colors[ImGuiCol_ButtonActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Header] = highlightBlue; // selected items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderHovered] = highlightBlueHovered; // hovered items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Separator] = backgroundLight;
	style.Colors[ImGuiCol_ResizeGrip] = backgroundMedium;
	style.Colors[ImGuiCol_ResizeGripHovered] = highlightBlue;
	style.Colors[ImGuiCol_ResizeGripActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.7f, 0.77f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = highlightBlue; // Also used for progress bar
	style.Colors[ImGuiCol_PlotHistogramHovered] = highlightBlueHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = highlightBlue;
	style.Colors[ImGuiCol_PopupBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_DragDropTarget] = backgroundLight;
}
