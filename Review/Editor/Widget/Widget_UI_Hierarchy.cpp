#include "stdafx.h"
#include "Widget_UI_Hierarchy.h"

Widget_UI_Hierarchy::Widget_UI_Hierarchy(Context* context)
	: IWidget(context)
{
	title = "UI_Hierarchy";
	uiManager = context->GetSubsystem<UIManager>();
	renderer = context->GetSubsystem<Renderer>();

	ZeroMemory(&clicked_data, sizeof(clicked_data));
}

void Widget_UI_Hierarchy::Render()
{
	if (!bVisible)
		return;

	clicked_data.scope = UI_Hierarchy_ClickedScope::None;

	ShowHierarchy(); // 매번 돈다고 효율성 없지가 않은게.. 이게 곧 렌더링임

	UpdateClickedData(UI_Hierarchy_ClickedScope::Window);

	// Imgui가 Tree 같은 구조 내부에서 팝업 뜨게가 안됨
	if (ImGui::GetIO().MouseDown[1])
	{
		switch (clicked_data.scope)
		{
		case UI_Hierarchy_ClickedScope::UIComponent:
			ImGui::OpenPopup("UI Hierarchy UIComponent Popup");
			break;
		case UI_Hierarchy_ClickedScope::UI:
			ImGui::OpenPopup("UI Hierarchy UI Popup");
			break;
		case UI_Hierarchy_ClickedScope::Window:
			ImGui::OpenPopup("UI Hierarchy Window Popup");
			break;
		}
	}

	RightClickForUIComponent();
	RightClickForUI();
	RightClickForWindow();

	if (clicked_data.scope != UI_Hierarchy_ClickedScope::None)
		clicked_data.scope_before = clicked_data.scope;
}

void Widget_UI_Hierarchy::ShowHierarchy()
{
	auto uies = uiManager->GetUIes();

	for (auto& ui : uies)
		AddUIInHierarchy(ui.second);
}

void Widget_UI_Hierarchy::AddUIInHierarchy(UI* ui)
{
	if (!ui)
		return;


	if (ImGui::CollapsingHeader(ui->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		uiManager->SetCurrentUI(ui->GetName());

		UpdateClickedData(UI_Hierarchy_ClickedScope::UI);

		std::vector<IUIWidget*> uiComponents = ui->GetComponents();

		for (auto& uiComponent : uiComponents)
			AddUIComponentInHierarchy(uiComponent);
	}
}

void Widget_UI_Hierarchy::AddUIComponentInHierarchy(class IUIWidget* uiComponent)
{
	if (!uiComponent)
		return;

	if (ImGui::TreeNodeEx(uiComponent->GetName().c_str(), GetTreeNodeFlags(UI_Hierarchy_ClickedScope::UIComponent, uiComponent)))
	{
		EditorHelper::Get()->SelectUIComponent(uiComponent);

		UpdateClickedData(UI_Hierarchy_ClickedScope::UIComponent, uiComponent);

		ImGui::TreePop();
	}
}

void Widget_UI_Hierarchy::UpdateClickedData(const UI_Hierarchy_ClickedScope& scope, IUIWidget* uiComponent, const UIWidgetType& type)
{
	if (clicked_data.scope > scope)
		return;

	if (scope == UI_Hierarchy_ClickedScope::Window)
	{
		if (ImGui::IsWindowHovered())
			if (ImGui::GetIO().MouseDown[1])
			{
				clicked_data.scope = scope;
				clicked_data.uiComponent = uiComponent;
				clicked_data.type = type;
			}
	}
	else
	{
		if (ImGui::IsItemHovered())
			if (ImGui::GetIO().MouseDown[1] || ImGui::GetIO().MouseDown[0])
			{
				clicked_data.scope = scope;
				clicked_data.uiComponent = uiComponent;
				clicked_data.type = type;
			}
	}
}

const ImGuiTreeNodeFlags Widget_UI_Hierarchy::GetTreeNodeFlags(const UI_Hierarchy_ClickedScope& scope, IUIWidget* uiComponent, const UIWidgetType& type)
{
	ImGuiTreeNodeFlags flags = 0;

	//if (scope == UI_Hierarchy_ClickedScope::UIComponent)
	//	flags |= ImGuiTreeNodeFlags_Leaf;

	if (clicked_data.uiComponent && clicked_data.scope_before == scope && clicked_data.uiComponent->GetName() == uiComponent->GetName() && clicked_data.type == type)
		flags |= ImGuiTreeNodeFlags_Selected;

	return flags;
}

void Widget_UI_Hierarchy::RightClickForWindow()
{
	if (ImGui::BeginPopup("UI Hierarchy Window Popup"))
	{
		if (ImGui::MenuItem("Copy"))
		{
		}
		if (ImGui::MenuItem("Delete"))
		{

		}
		if (ImGui::MenuItem("Empty UI"))
		{
			CreateUI();
		}

		ImGui::EndPopup();
	}
}

void Widget_UI_Hierarchy::RightClickForUI()
{
	if (ImGui::BeginPopup("UI Hierarchy UI Popup"))
	{
		if (ImGui::MenuItem("Copy"))
		{

		}
		if (ImGui::MenuItem("Delete"))
		{

		}
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("ProgressBar"))
			{
				ProgressBar* component = uiManager->GetCurrentUI()->AddComponent<ProgressBar>();
				component->Init_Default();
				component->SetIsVisible(true);
				component->SetName("progressBar");
			}
			if (ImGui::MenuItem("Box"))
			{
				Box* component = uiManager->GetCurrentUI()->AddComponent<Box>();
				component->Init_Default();
				component->SetIsVisible(true);
				component->SetName("Box");
			}
			if (ImGui::MenuItem("Inventory"))
			{
				Inventory* component = uiManager->GetCurrentUI()->AddComponent<Inventory>();
				component->Init_Default();
				component->SetIsVisible(true);
				component->SetName("Inventory");
			}
			if (ImGui::MenuItem("ToolTip"))
			{
				ToolTip* component = uiManager->GetCurrentUI()->AddComponent<ToolTip>();
				component->Init_Default();
				component->SetIsVisible(true);
				component->SetName("ToolTip");
			}
			if (ImGui::MenuItem("Evolution"))
			{
				Evolution* component = uiManager->GetCurrentUI()->AddComponent<Evolution>();
				component->Init_Default();
				component->SetIsVisible(true);
				component->SetName("Evolution");
			}
			if (ImGui::MenuItem("SaveLoad"))
			{
				SaveLoad* component = uiManager->GetCurrentUI()->AddComponent<SaveLoad>();
				component->Init_Default();
				component->SetIsVisible(true);
				component->SetName("SaveLoad");
			}
			if (ImGui::MenuItem("VerticalList"))
			{
				VerticalList* component = uiManager->GetCurrentUI()->AddComponent<VerticalList>();
				component->Init_Default();
				component->SetIsVisible(true);
				component->SetName("VerticalList");
			}
			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}

void Widget_UI_Hierarchy::RightClickForUIComponent()
{
	if (ImGui::BeginPopup("UI Hierarchy UIComponent Popup"))
	{
		IUIWidget* component = clicked_data.uiComponent;
		if (ImGui::BeginMenu("Create"))
		{
			if (component)
			{
				if (ImGui::MenuItem("AddFrame"))
				{
					static int tmp = 0;
					component->AddFrame("Frame" + std::to_string(tmp++));
				}
				ImGui::EndMenu();
			}
		}

		if (ImGui::MenuItem("Delete"))
		{
			IUIWidget* uiComponent = clicked_data.uiComponent;
			if (uiComponent)
				uiManager->GetCurrentUI()->DeleteComponent(uiComponent);
			
		}

		ImGui::EndPopup();
	}
}

UI* Widget_UI_Hierarchy::CreateUI()
{
	context->GetSubsystem<Thread>()->AddTask([this]()
		{
			static int tmp = 0;
			uiManager->CreateUI("aaa" + std::to_string(tmp));
			uiManager->SetCurrentUI("aaa" + std::to_string(tmp));
		}
	);

	return uiManager->GetCurrentUI();
}
