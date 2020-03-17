#pragma once
#include "IUIComponent.h"

class Box : public IUIComponent
{
private:
	friend UI;
	friend MonsterManager;

private:
	Box(class Context* context);
	~Box() = default;

public:
	void Init_Default();

	void SetVisible(const bool& var) { isVisible = var; }
	void SetPosition(const Vector3& var) { IUIComponent::SetPosition(var); }
	Vector3 GetPosition() { return IUIComponent::GetPosition(); }
	bool IsClicked() { if (frames.size() > 0) return frames[0]->IsClicked(); else return false; }

private:
	void Update() override;
	void LoadFromFile(const std::string& path) override;
	void SaveToFile(const std::string& path) override;
};