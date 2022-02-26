#pragma once
#include "Framework.h"

class UIWidgetFrame final
{
public:
	friend UI; friend IUIWidget; friend class Inventory; friend class ToolTip; friend class Evolution; friend class SaveLoad;  friend class VerticalList;
	friend class Engine;
private:
	UIWidgetFrame(class Context* context);
	~UIWidgetFrame();

public:
	void SaveToFile(FileStream& stream);
	void LoadFromFile(FileStream& stream);

	void Init_Default();
	void Update();
	void UpdateUIBuffer(Camera* camera = nullptr);

	Transform* GetTransform() { return transform; }
	void SetPosition(const Vector3& var) { transform->SetPosition(var); }
	Vector3 GetPosition() { return transform->GetPosition(); }
	void SetScale(const Vector3& var) { transform->SetScale(var); }
	Vector3 GetScale() { return transform->GetScale(); }

	Renderable* GetRenderable() { return renderable; }
	Scripter* GetScripter() { return scripter; }
	Animator* GetAnimator() { return animator; }

	const std::string& GetName() { return name; }
	void SetName(const std::string& name) { this->name = name; }
	
	class ConstantBuffer* GetUIBuffer() { return uiBuffer; }

	bool UseDefaultCover() { return useDefaultCovered; }
	void SetUseDefaultCover(const bool& var) { useDefaultCovered = var; }
	void SetClickLock(const bool& var) { lockClick = var; }
	bool IsCovered() { return isCovered; }
	bool IsClicked() { return isClicked; }
	void SetIsInstanced(const bool& var);
	bool IsVisible() { return isVisible; }
	void SetIsVisible(const bool& var) { isVisible = var; }

	const std::wstring& GetText() { return text; }
	void SetText(const std::wstring& var);
	void SetTextFromMultibyte(const std::string& var);

private:
	class Context* context;
	class ResourceManager* resourceManager;
	class MouseManager* mouseManager;
	class Transform* transform;
	class Renderable* renderable;
	class Animator* animator;
	class Scripter* scripter;

	std::string name;

	class ConstantBuffer* uiBuffer;
	bool useDefaultCovered = false;
	bool lockClick = false;
	bool isClicked = false;
	bool isCovered = false;
	bool isInstanced = false;
	bool isVisible = true;
	std::wstring text = L"N\A";
};