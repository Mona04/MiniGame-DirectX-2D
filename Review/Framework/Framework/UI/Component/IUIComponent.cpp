#include "Framework.h"
#include "IUIComponent.h"
#include "Component/UI_Component_Frame.h"

std::pair<class Renderable*, class Transform*> null_pair = std::pair<Renderable*, Transform*>(nullptr, nullptr);

IUIComponent::IUIComponent(Context* context)
	: context(context)
	, pos(Vector3(0, 0, 0))
	, scale(Vector3(10, 10, 10))
	, isVisible(false)
	, name("")
{
	resourceManager = context->GetSubsystem<ResourceManager>();

	id = GUIDGenerator::Generate();
}

IUIComponent::~IUIComponent()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);

	frames.clear();
}

void IUIComponent::Clear()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);

	frames.clear();
}

UI_Component_Frame* IUIComponent::GetFrame(const std::string& name)
{
	for (auto& frame : frames)
	{
		if (frame == nullptr) continue;
		if (frame->GetName() == name)
			return frame;
	}
	return nullptr;
}

UI_Component_Frame* IUIComponent::AddFrame(const std::string& name)
{
	UI_Component_Frame* frame = new UI_Component_Frame(context);
	frame->SetName(name);
	frame->Init_Default();
	frames.emplace_back(frame);

	return frame;
}

UI_Component_Frame* IUIComponent::DeleteFrame(const std::string& name)
{
	for (auto iter = frames.begin() ; iter != frames.end() ; iter++)
	{
		if ((*iter)->GetName() == name)
		{
			UI_Component_Frame* result = *iter;
			frames.erase(iter); 
			return result;
		}
	}
	return nullptr;
}

Vector3 IUIComponent::GetPosition()
{
	if (frames.empty())
		return Vector3(0, 0, 0);
	return frames[0]->GetPosition();
}

void IUIComponent::SetPosition(const Vector3& var)
{
	if (frames.empty())
		return;

	pos = var;
	Vector3 dist = var - frames[0]->GetPosition();
	for (auto& frame : frames) frame->GetTransform()->Translate(dist);
}

Vector3 IUIComponent::GetScale()
{
	if (frames.empty())
		return Vector3(0, 0, 0);
	return frames[0]->GetScale();
}

void IUIComponent::SetScale(const Vector3& var)
{
	if (frames.empty())

	scale = var;
	Vector3 dist = var - frames[0]->GetScale();

	for (auto& frame : frames)
		frame->GetTransform()->ScaleTranslate(dist);

	if (this->type == UIComponentType::ProgressBar)
		static_cast<ProgressBar*>(this)->SetGaugeScale(GetFrame("Frame")->GetScale());
	
}

template<typename T>
inline constexpr UIComponentType IUIComponent::DeduceComponentType()
{
	return UIComponentType::Unknown;
}

#define REGISTER_COMPONENT_TYPE(T, enumT) template <> UIComponentType IUIComponent::DeduceComponentType<T>() { return enumT; }
REGISTER_COMPONENT_TYPE(ProgressBar, UIComponentType::ProgressBar)
REGISTER_COMPONENT_TYPE(Box, UIComponentType::Box)
REGISTER_COMPONENT_TYPE(Inventory, UIComponentType::Inventory)
REGISTER_COMPONENT_TYPE(ToolTip, UIComponentType::ToolTip)
REGISTER_COMPONENT_TYPE(Evolution, UIComponentType::Evolution)
REGISTER_COMPONENT_TYPE(SaveLoad, UIComponentType::SaveLoad)
REGISTER_COMPONENT_TYPE(VerticalList, UIComponentType::VerticalList)