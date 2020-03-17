#pragma once
#include "Framework.h"

enum class UIComponentType : uint
{
	Unknown,
	ProgressBar,
	Box,
	Text,
	Inventory,
	ToolTip,
	Evolution,
	SaveLoad,
	VerticalList
};

class IUIComponent
{
public:
	template <typename T>
	static constexpr UIComponentType DeduceComponentType();

public:
	IUIComponent(class Context* context);
	virtual ~IUIComponent();

	void Clear();
	virtual void Update() = 0;
	virtual void LoadFromFile(const std::string& path) = 0;
	virtual void SaveToFile(const std::string& path) = 0;

public:
	std::vector<class UI_Component_Frame*>& GetFrames() { return frames; }
	UI_Component_Frame* GetFirstFrame() { if (frames.size() > 0) return frames[0]; else return nullptr; }
	UI_Component_Frame* GetFrame(const std::string& name);
	UI_Component_Frame* AddFrame(const std::string& name);
	UI_Component_Frame* DeleteFrame(const std::string& name);

	void Translate(const Vector3 var) { for (auto& frame : frames) frame->GetTransform()->Translate(var); pos += var; }
	Vector3 GetPosition();
	void SetPosition(const Vector3& var);
	
	Vector3 GetScale();
	void SetScale(const Vector3& var);

	const bool& GetIsVisible() { return isVisible; }
	void SetIsVisible(const bool var) { isVisible = var; }

	const uint& GetID() const { return id; }
	const UIComponentType& GetType() const { return type; }
	
	const std::string& GetName() const { return name; }
	void SetName(const std::string& var) { name = var; }

protected:
	class Context* context;
	class ResourceManager* resourceManager;

	std::vector<UI_Component_Frame*> frames;

	Vector3 pos;
	Vector3 scale;
	bool isVisible;

protected:
	uint id;
	std::string name;
	UIComponentType type;
};
