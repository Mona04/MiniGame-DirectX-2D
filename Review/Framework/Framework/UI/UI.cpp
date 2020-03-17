#include "Framework.h"
#include "UI.h"
#include "Component/IUIComponent.h"

UI::UI(Context* context)
	: context(context)
	, isVisible(true)
	, bInventory(false)
{
}

UI::~UI()
{
	for (auto& component : components)
		SAFE_DELETE(component);

	components.clear();
	components.shrink_to_fit();
}

void UI::Init()
{
	for (auto& component : components)
		component->Update();
}

void UI::Update()
{
	for (auto& component : components)
		component->Update();
}

void UI::LoadFromFile(const std::string& path)
{
	FileStream stream;
	std::string UIComponentFolder = FileSystem::GetDirectoryFromPath(path) + "UI " + FileSystem::GetIntactFileNameFromPath(path) + "/";

	stream.Open(path, StreamMode::Read);
	{
		UIComponentType componentType;
		bool isVisible;
		std::string comName;

		uint nComponent = stream.ReadUInt();

		for (uint i = 0; i < nComponent; i++)
		{
			componentType = static_cast<UIComponentType>(stream.ReadUInt());
			stream.Read(isVisible);
			stream.Read(comName);

			switch (componentType)
			{
			case UIComponentType::ProgressBar:
			{
				ProgressBar* component = AddComponent<ProgressBar>();
				component->SetIsVisible(isVisible);
				component->SetName(comName);
				component->LoadFromFile(UIComponentFolder + comName + ".uicom");
				break;
			}	
			case UIComponentType::Box:
			{
				Box* component = AddComponent<Box>();
				component->SetIsVisible(isVisible);
				component->SetName(comName);
				component->LoadFromFile(UIComponentFolder + comName + ".uicom");
				break;
			}
			case UIComponentType::Inventory:
			{
				Inventory* component = AddComponent<Inventory>();
				component->SetIsVisible(isVisible);
				component->SetName(comName);
				component->LoadFromFile(UIComponentFolder + comName + ".uicom");
				break;
			}
			case UIComponentType::ToolTip:
			{
				ToolTip* component = AddComponent<ToolTip>();
				component->SetIsVisible(isVisible);
				component->SetName(comName);
				component->LoadFromFile(UIComponentFolder + comName + ".uicom");
				break;
			}
			case UIComponentType::Evolution:
			{
				Evolution* component = AddComponent<Evolution>();
				component->SetIsVisible(isVisible);
				component->SetName(comName);
				component->LoadFromFile(UIComponentFolder + comName + ".uicom");
				break;
			}
			case UIComponentType::SaveLoad:
			{
				SaveLoad* component = AddComponent<SaveLoad>();
				component->SetIsVisible(isVisible);
				component->SetName(comName);
				component->LoadFromFile(UIComponentFolder + comName + ".uicom");
				break;
			}
			case UIComponentType::VerticalList:
			{
				VerticalList* component = AddComponent<VerticalList>();
				component->SetIsVisible(isVisible);
				component->SetName(comName);
				component->LoadFromFile(UIComponentFolder + comName + ".uicom");
				break;
			}
			}
		}
	}
	stream.Close();
}

void UI::SaveToFile(const std::string& path)
{
	FileStream stream;
	std::string UIComponentFolder = FileSystem::GetDirectoryFromPath(path) + "UI " + FileSystem::GetIntactFileNameFromPath(path) + "/";
	FileSystem::MakeDirectory(UIComponentFolder);

	stream.Open(path, StreamMode::Write);
	{
		stream.Write(components.size());

		for (auto& component : components)
		{
			stream.Write(static_cast<uint>(component->GetType()));
			stream.Write(component->GetIsVisible());
			stream.Write(component->GetName());
			component->SaveToFile(UIComponentFolder + component->GetName() + ".uicom");
		}
	}
	stream.Close();
}

void UI::DeleteComponent(IUIComponent* deleted)
{
	if (!deleted)
		return;

	for (auto iter = components.begin() ; iter != components.end() ; iter++)
	{
		if ((*iter)->GetID() == deleted->GetID())
		{
			auto result = *iter;
			components.erase(iter);
			SAFE_DELETE(result);
			return;
		}
	}
}

const bool UI::HasComponent(const UIComponentType& type)
{	
	for (const auto& component : components)
	{
		if (component->GetType() == type)
			return true;
	}
	return false;
}
