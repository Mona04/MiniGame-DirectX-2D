#pragma once
#include "IUIComponent.h"

class ToolTip : public IUIComponent
{
private:
	friend UI;

private:
	ToolTip(class Context* context);
	~ToolTip() = default;

	void Clear();

	void Update() override;

	void UpdateTransform();

	void LoadFromFile(const std::string& path) override;
	void SaveToFile(const std::string& path) override;

public:
	void Init_Default();

	const Vector3& GetPosition() { return position; }
	void SetPosition(const Vector3& var) { position = var; UpdateTransform(); }

	const Vector2& GetTitleScale() { return titleScale; }
	void SetTitleScale(const Vector2& var) { titleScale = var; UpdateTransform(); }

	const Vector2& GetTitlePadding() { return titlePadding; }
	void SetTitlePadding(const Vector2& var) { titlePadding = var; UpdateTransform(); }

	const Vector2& GetTagScale() { return tagScale; }
	void SetTagScale(const Vector2& var) { tagScale = var; UpdateTransform(); }

	const Vector2& GetTagPadding() { return tagPadding; }
	void SetTagPadding(const Vector2& var) { tagPadding = var; UpdateTransform(); }

	const Vector2& GetInfoScale() { return infoScale; }
	void SetInfoScale(const Vector2& var) { infoScale = var; UpdateTransform(); }

	const Vector2& GetInfoPadding() { return infoPadding; }
	void SetInfoPadding(const Vector2& var) { infoPadding = var; UpdateTransform(); }

	const Vector2& GetSlotPadding() { return slotPadding; }
	void SetSlotPadding(const Vector2& var) { slotPadding = var; UpdateTransform(); }

	const float& GetWidth() { return width; }
	void SetWidth(const float& var) { width = var; }

	void ShowItemInfo(const float& x, const float& y, const class Data_Item* itemData);

	bool DoesStayEnough(const float& x, const float& y);

private:
	void UpdateWidthHeight();
	int GetNumEnter(const std::wstring& string);
	Vector3 GetSlotFramePosition(const int& i);
	Vector3 GetSlotFrameScale(const std::wstring& string);

private:
	class Input* input;
	class Timer* timer;

	Vector3 position;
	Vector2 titleScale;
	Vector2 titlePadding;
	Vector2 tagScale;
	Vector2 tagPadding;
	Vector2 infoScale;
	Vector2 infoPadding;
	Vector2 slotPadding;

	int nSlot;

	float width, height;

private:
	bool isToolTipOn = false;
};