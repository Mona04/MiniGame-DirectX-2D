#include "stdafx.h"
#include "Widget_Log.h"

Widget_Log::Widget_Log(Context * context)
	: IWidget(context)
	, maxLogCount(999)
	, bShowInfo(true)
	, bShowWarning(true)
	, bShowError(true)
	, bScrolling(true)
{
	title = "Log";

	logger = new EngineLogger();
	logger->SetCallBack([this](const LogPair& logPair) { AddLog(logPair); });
	Log::SetLogger(logger);
}

Widget_Log::~Widget_Log()
{
	SAFE_DELETE(logger);
}

void Widget_Log::Render()
{
	static ImGuiTextFilter logFilter;
	static std::vector<ImVec4> logColor =
	{
		ImVec4(0.76f, 0.77f, 0.8f, 1.0f), // Info
		ImVec4(0.75f, 0.75f, 0.0f, 1.0f), // Warning
		ImVec4(0.75f, 0.0f,  0.0f, 1.0f), // Error
	};

	auto DisplayButton = [this](const IconType& type, bool* toggle)
	{
		ImGui::PushStyleColor(
			ImGuiCol_Button, 
			ImGui::GetStyle().Colors[*toggle ? ImGuiCol_ButtonActive : ImGuiCol_Button]
		);
		{
			if (IconProvider::Get()->ImageButton(type, ImVec2(15.0f, 15.0f)))
			{
				*toggle = !*(toggle);
				bScrolling = true;
			}
		}
		ImGui::PopStyleColor(1);
		ImGui::SameLine();
	};

	if (ImGui::Button("Clear"))
		Clear();

	ImGui::SameLine();

	DisplayButton(IconType::Button_Info, &bShowInfo);
	DisplayButton(IconType::Button_Warning, &bShowWarning);
	DisplayButton(IconType::Button_Error, &bShowError);

	logFilter.Draw("Filter", -100.0f);   // 내장 필터
	ImGui::Separator();

	ImGui::BeginChild("Logging", ImVec2(0.0f, 0.0f), false, ImGuiWindowFlags_HorizontalScrollbar);
	{
		for (const auto& log : logs)
		{
			if (!logFilter.PassFilter(log.text.c_str()))   // 필터 검사
				continue;

			if ((log.type == 0 && bShowInfo) ||
				(log.type == 1 && bShowWarning) ||
				(log.type == 2 && bShowError))
			{
				ImGui::PushStyleColor(ImGuiCol_Text, logColor[log.type]);
				{
					ImGui::TextUnformatted(log.text.c_str());
				}
				ImGui::PopStyleColor(1);
			}
		}

		if (bScrolling)
		{
			ImGui::SetScrollHereY();
			bScrolling = false;
		}
	}
	ImGui::EndChild();
}

void Widget_Log::AddLog(const LogPair & logPair)
{
	logs.push_back(logPair);

	if (logs.size() > maxLogCount)
		logs.pop_front();

	bScrolling = true;
}

void Widget_Log::Clear()
{
	logs.clear();
	logs.shrink_to_fit();
}
