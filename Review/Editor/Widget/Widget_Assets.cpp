#include "stdafx.h"
#include "Widget_Assets.h"

Widget_Assets::Widget_Assets(Context * context)
	: IWidget(context)
	, itemSize(100.0f)
	, itemSizeMin(50.0f)
	, itemSizeMax(200.0f)
	, currentPath("../../_Assets/Texture/")
{
	title = "Assets";	
	
	resourceManager = context->GetSubsystem<ResourceManager>();

	UpdateItem(currentPath);
}

Widget_Assets::~Widget_Assets()
{
	items.clear();
	items.shrink_to_fit();
}

void Widget_Assets::Render()
{
	if (ImGui::Button("Directory"))
		ChangeCurDirectory(FileSystem::GetParentDirectory(currentPath));

	ImGui::SameLine();
	ImGui::TextUnformatted(currentPath.c_str());
	ImGui::SameLine(ImGui::GetWindowContentRegionWidth() * 0.8f);
	ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.233f);
	{
		//ImGui::SliderFloat("##ItemSize", &itemSize, itemSizeMin, itemSizeMax);
	    ImGui::DragFloat("##ItemSize", &itemSize, 1.0f, itemSizeMin, itemSizeMax);
	}
	ImGui::PopItemWidth();
	ImGui::Separator();

	ShowItem();
}

void Widget_Assets::ShowItem()
{
	ImVec2 contentSize = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();

	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0f, 18.0f));
	{
		ImGui::BeginChild("##Child", contentSize, false);
		{
			int columns = static_cast<int>(ImGui::GetWindowContentRegionWidth() / itemSize);
			columns = columns < 1 ? 1 : columns;
			ImGui::Columns(columns, nullptr, false);

			for (const auto& item : items)
			{
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				if (IconProvider::Get()->ImageButton(item.thumbnail, ImVec2(itemSize, itemSize - 23.0f)))
				{
					if (item.thumbnail.type == IconType::Thumbnail_Folder) {
						ChangeCurDirectory(item.path + "/");
						ImGui::PopStyleColor(2);   // break;, pop 의 중요성
						break;
					}

				}
				ImGui::PopStyleColor(2);
				
				if (FileSystem::IsSupportImageFile(item.path))
					DragAndDrop::SetDragAndDrop(ResourceType::Texture, FileSystem::GetDirectoryLeft(item.path, resourceManager->GetResourceDirectory<Texture>()));

				ImGui::SameLine();
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - itemSize);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSize - 13.0f);
				
				ImGui::PushItemWidth(itemSize + 8.5f);
				{
					ImGui::TextWrapped(item.label.c_str());
				}
				ImGui::PopItemWidth();

				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + itemSize);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - itemSize + 13.0f);
				ImGui::NextColumn();
			}
		}
		ImGui::EndChild();
	}
	ImGui::PopStyleVar(2);
}

void Widget_Assets::UpdateItem(const std::string & path)
{
	if (!FileSystem::IsDirectory(path))
		return;

	items.clear();
	items.shrink_to_fit();

	auto files = FileSystem::GetFilesInDirectory(path);
	for (const auto& file : files)
		items.emplace_back(file, *(IconProvider::Get()->Load(file)));

	files = FileSystem::GetFoldersInDirectory(path);
	for (const auto& file : files)
		items.emplace_back(file, *(IconProvider::Get()->Load(file)));
}

void Widget_Assets::ChangeCurDirectory(const std::string& path)
{
	if (!FileSystem::IsDirectory(path))
		return;

	currentPath = path;
	UpdateItem(currentPath);
}