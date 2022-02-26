#include "Framework.h"
#include "IUIWidget.h"
#include "Component/UIWidgetFrame.h"

std::pair<class Renderable*, class Transform*> null_pair = std::pair<Renderable*, Transform*>(nullptr, nullptr);

IUIWidget::IUIWidget(Context* context)
	: context(context)
	, pos(Vector3(0, 0, 0))
	, scale(Vector3(10, 10, 10))
	, isVisible(false)
	, name("")
{
	resourceManager = context->GetSubsystem<ResourceManager>();

	id = GUIDGenerator::Generate();
}

IUIWidget::~IUIWidget()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);

	frames.clear();
}

void IUIWidget::Clear()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);

	frames.clear();
}

UIWidgetFrame* IUIWidget::GetFrame(const std::string& name)
{
	for (auto& frame : frames)
	{
		if (frame == nullptr) continue;
		if (frame->GetName() == name)
			return frame;
	}
	return nullptr;
}

UIWidgetFrame* IUIWidget::AddFrame(const std::string& name)
{
	UIWidgetFrame* frame = new UIWidgetFrame(context);
	frame->SetName(name);
	frame->Init_Default();
	frames.emplace_back(frame);

	return frame;
}

UIWidgetFrame* IUIWidget::DeleteFrame(const std::string& name)
{
	for (auto iter = frames.begin() ; iter != frames.end() ; iter++)
	{
		if ((*iter)->GetName() == name)
		{
			UIWidgetFrame* result = *iter;
			frames.erase(iter); 
			return result;
		}
	}
	return nullptr;
}

Vector3 IUIWidget::GetPosition()
{
	if (frames.empty())
		return Vector3(0, 0, 0);
	return frames[0]->GetPosition();
}

void IUIWidget::SetPosition(const Vector3& var)
{
	if (frames.empty())
		return;

	pos = var;
	Vector3 dist = var - frames[0]->GetPosition();
	for (auto& frame : frames) frame->GetTransform()->Translate(dist);
}

Vector3 IUIWidget::GetScale()
{
	if (frames.empty())
		return Vector3(0, 0, 0);
	return frames[0]->GetScale();
}

void IUIWidget::SetScale(const Vector3& var)
{
	if (frames.empty())

	scale = var;
	Vector3 dist = var - frames[0]->GetScale();

	for (auto& frame : frames)
		frame->GetTransform()->ScaleTranslate(dist);

	if (this->type == UIWidgetType::ProgressBar)
		static_cast<ProgressBar*>(this)->SetGaugeScale(GetFrame("Frame")->GetScale());
	
}

template<typename T>
inline constexpr UIWidgetType IUIWidget::DeduceComponentType()
{
	return UIWidgetType::Unknown;
}

#define REGISTER_COMPONENT_TYPE(T, enumT) template <> UIWidgetType IUIWidget::DeduceComponentType<T>() { return enumT; }
REGISTER_COMPONENT_TYPE(ProgressBar, UIWidgetType::ProgressBar)
REGISTER_COMPONENT_TYPE(Box, UIWidgetType::Box)
REGISTER_COMPONENT_TYPE(Inventory, UIWidgetType::Inventory)
REGISTER_COMPONENT_TYPE(ToolTip, UIWidgetType::ToolTip)
REGISTER_COMPONENT_TYPE(Evolution, UIWidgetType::Evolution)
REGISTER_COMPONENT_TYPE(SaveLoad, UIWidgetType::SaveLoad)
REGISTER_COMPONENT_TYPE(VerticalList, UIWidgetType::VerticalList)