#pragma once
#include "stdafx.h"

enum class ResourceType : uint;

class DragAndDrop final
{
public :
	static void SetDragAndDrop(const ResourceType& type, const std::string& data)
	{
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			ImGui::SetDragDropPayload(
				reinterpret_cast<const char*>(&type),
				data.c_str(),
				data.length() + 1);
			ImGui::TextUnformatted(data.c_str());
			ImGui::EndDragDropSource();
		}
	}

	static const std::string GetDragAndDrop(const ResourceType& type)
	{
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(
				reinterpret_cast<const char*>(&type)
			);

			ImGui::EndDragDropTarget();

			if (payload)
				return reinterpret_cast<const char*>(payload->Data);
		}
		return "";
	}
};