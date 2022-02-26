#pragma once
#include "Framework.h"

enum class UIWidgetType : uint
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

class IUIWidget
{
public:
	template <typename T>
	static constexpr UIWidgetType DeduceComponentType();

public:
	IUIWidget(class Context* context);
	virtual ~IUIWidget();

	void Clear();
	virtual void Update() = 0;
	virtual void LoadFromFile(const std::string& path) = 0;
	virtual void SaveToFile(const std::string& path) = 0;

public:
	std::vector<class UIWidgetFrame*>& GetFrames() { return frames; }
	UIWidgetFrame* GetFirstFrame() { if (frames.size() > 0) return frames[0]; else return nullptr; }
	UIWidgetFrame* GetFrame(const std::string& name);
	UIWidgetFrame* AddFrame(const std::string& name);
	UIWidgetFrame* DeleteFrame(const std::string& name);

	void Translate(const Vector3 var) { for (auto& frame : frames) frame->GetTransform()->Translate(var); pos += var; }
	Vector3 GetPosition();
	void SetPosition(const Vector3& var);
	
	Vector3 GetScale();
	void SetScale(const Vector3& var);

	const bool& GetIsVisible() { return isVisible; }
	void SetIsVisible(const bool var) { isVisible = var; }

	const uint& GetID() const { return id; }
	const UIWidgetType& GetType() const { return type; }
	
	const std::string& GetName() const { return name; }
	void SetName(const std::string& var) { name = var; }

protected:
	class Context* context;
	class ResourceManager* resourceManager;

	std::vector<UIWidgetFrame*> frames;

	Vector3 pos;
	Vector3 scale;
	bool isVisible;

protected:
	uint id;
	std::string name;
	UIWidgetType type;
};
