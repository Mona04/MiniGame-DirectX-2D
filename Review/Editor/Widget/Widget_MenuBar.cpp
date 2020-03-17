#include "stdafx.h"
#include "Widget_MenuBar.h"

Widget_MenuBar::Widget_MenuBar(Context * context)
	: IWidget(context)
	, bShowStyleEditor(false)
	, bShowMetricsWindow(false)
	, bShowDemoWindow(false)
	, bShowScriptTool(false)
{
	//title = "MenuBar";
}

void Widget_MenuBar::Render()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Scene"))
			{
				const auto& sceneManager = context->GetSubsystem<SceneManager>();
				FileSystem::OpenFileDialog
				(
					[sceneManager](std::string str){ sceneManager->LoadScene(FileSystem::GetDirectoryLeft(str, Scene::defaultDir)); },
					".scene",
					"../../_Assets/Scene/"
				);
			}

			if (ImGui::MenuItem("Save this Scene")) 
			{
				const auto& sceneManager = context->GetSubsystem<SceneManager>();
				FileSystem::SaveFileDialog
				(
					[sceneManager](std::string str) { sceneManager->SaveScene(FileSystem::GetDirectoryLeft(str, Scene::defaultDir), sceneManager->GetCurrentScene()->GetName()); },
					".scene",
					"../../_Assets/Scene/"
				);
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Open UI"))
			{
				const auto& uiManager = context->GetSubsystem<UIManager>();
				FileSystem::OpenFileDialog
				(
					[uiManager](std::string str) {
						uiManager->LoadUI(FileSystem::GetDirectoryLeft(str, UIManager::defaultDir));
						uiManager->SetCurrentUI(FileSystem::GetIntactFileNameFromPath(str));
					},
					FileSystem::EveryFilter,//".ui",
					"../../_Assets/UI/"
				);
			}

			if (ImGui::MenuItem("Save this UI"))
			{
				const auto& uiManager = context->GetSubsystem<UIManager>();
				FileSystem::SaveFileDialog
				(
					[uiManager](std::string str) { uiManager->SaveUI(FileSystem::GetDirectoryLeft(str, UIManager::defaultDir), uiManager->GetCurrentUI()->GetName()); },
					FileSystem::EveryFilter,
					"../../_Assets/UI/"
				);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::MenuItem("Metrics", nullptr, &bShowMetricsWindow);
			ImGui::MenuItem("Sytle", nullptr, &bShowStyleEditor);
			ImGui::MenuItem("Demo", nullptr, &bShowDemoWindow);
			ImGui::MenuItem("Script", nullptr, &bShowScriptTool);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	auto StyleEdition = []()
	{
		ImGui::Begin("StyleEditor"); // Begin은 정해진거임
		ImGui::ShowStyleEditor();
		ImGui::End();
	};

	if (bShowMetricsWindow) ImGui::ShowMetricsWindow();
	if (bShowStyleEditor) StyleEdition();
	if (bShowDemoWindow) ImGui::ShowDemoWindow();
	
	ToolScript::Get()->SetIsVisible(bShowScriptTool);
}
