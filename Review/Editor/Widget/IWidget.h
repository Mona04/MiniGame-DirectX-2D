#pragma once
#include "stdafx.h"
#undef max

class IWidget
{
public:
	IWidget(class Context* context)
		: context(context)
		, title("")
		, xMin(0.0f), xMax(std::numeric_limits<float>::max())
		, yMin(0.0f), yMax(std::numeric_limits<float>::max())
		, height(0.0f)
		, windowFlags(ImGuiWindowFlags_NoCollapse)
		, bVisible(true)
		, bStacked(false)
	{
	}
	virtual ~IWidget() = default;

	virtual void Begin()
	{
		if (!bVisible)
			return;

		ImGui::SetNextWindowSize(ImVec2(xMin, yMin), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSizeConstraints(ImVec2(xMin, yMin), ImVec2(xMax, yMax));
		ImGui::Begin(title.c_str(), &bVisible, windowFlags);
		bStacked = true;
	}

	virtual void Render() = 0;

	virtual void End()
	{
		if (!bVisible && !bStacked)
			return;

		height = ImGui::GetWindowHeight();
		ImGui::End();
		bStacked = false;
	}

	bool IsVisible() { return bVisible; }
	void SetIsVisible(const bool& var) { bVisible = var; }
	float GetHeight() { return height; }

protected:
	Context* context;
	std::string title;
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float height;
	int windowFlags;
	bool bVisible;
	bool bStacked;
};