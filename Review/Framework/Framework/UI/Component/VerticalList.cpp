#include "Framework.h"
#include "VerticalList.h"
#include "IUIComponent.h"

VerticalList::VerticalList(Context* context)
	: IUIComponent(context)
	, position(-0.511f, -0.590f, 0.0f)
	, itemPadding(0.003f, 0.015f), itemScale(0.094f, 0.100f)
	, infoScale(0.132f, -0.247f), infoPadding(0.022f, -0.073f)
	, nSlot(2)
{
	type = UIComponentType::VerticalList;
	mouseManager = context->GetSubsystem<MouseManager>();
	dataManager = context->GetSubsystem<DataManager>();
	gameManager = context->GetSubsystem<GameManager>();
	inventoryManager = context->GetSubsystem<InventoryManager>();
}

void VerticalList::Init_Default()
{
	Clear();

	UpdateWidthHeight();

	{
		auto frame = AddFrame("Window");
		frame->GetRenderable()->SetMaterial("UI/UI_VerticalList_Window.material", "UI_VerticalList_Window");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}

	for (int s = 0; s < nSlot; s++)
	{
		{
			auto frame = AddFrame("VerticalList Slot " + std::to_string(s));
			frame->GetRenderable()->SetMaterial("UI/UI_Transparent.material", "UI_Transparent");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
			frame->GetTransform()->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(s));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}

		{
			auto frame = AddFrame("VerticalList Info " + std::to_string(s));
			frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "SaveLoad Slot " + std::to_string(s) + std::to_string(this->id));
			frame->GetTransform()->SetScale(Vector3(infoScale.x, infoScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(s) + Vector3(0, -itemScale.y + -itemPadding.y, 0));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}
	}
}

void VerticalList::Clear()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);
}

void VerticalList::Update()
{
	if (isVisible)
	{
		for (const auto& frame : frames)
			frame->Update();
	}
}

void VerticalList::UpdateTransform()
{
	UpdateWidthHeight();

	{
		auto frame = GetFrame("Window");
		if(frame)
		{
			frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
			frame->GetTransform()->SetPosition(position);
		}
	}

	{
		for (uint s = 0; s < nSlot; s++)
		{
			auto frame = GetFrame("VerticalList Slot " + std::to_string(s));
			if (frame)
			{
				frame->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
				frame->SetPosition(GetBoxPosition(s));
			}
			auto frame2 = GetFrame("VerticalList Info " + std::to_string(s));
			if (frame2)
			{
				frame2->SetScale(Vector3(infoScale.x, infoScale.y, 1.0f));
				frame2->SetPosition(GetBoxPosition(s));
			}
		}
	}
}

void VerticalList::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		stream.Read(nSlot);

		stream.Read(position);  // setting 
		stream.Read(itemScale);
		stream.Read(itemPadding);
		stream.Read(infoScale);
		stream.Read(infoPadding);

		AddFrame("Window")->LoadFromFile(stream);

		for (uint s = 0; s < nSlot; s++)
		{
			AddFrame("VerticalList Slot " + std::to_string(s))->LoadFromFile(stream);
			AddFrame("VerticalList Info " + std::to_string(s))->LoadFromFile(stream);
		}
	}
	stream.Close();

	for (auto& frame : frames)
		frame->SetUseDefaultCover(false);

	UpdateTransform();
}

void VerticalList::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(nSlot);

		stream.Write(position);  // setting 
		stream.Write(itemScale);
		stream.Write(itemPadding);
		stream.Write(infoScale);
		stream.Write(infoPadding);

		GetFrame("Window")->SaveToFile(stream);

		for (uint s = 0; s < nSlot; s++)
		{
			GetFrame("VerticalList Slot " + std::to_string(s))->SaveToFile(stream);
			GetFrame("VerticalList Info " + std::to_string(s))->SaveToFile(stream);
		}
	}
	stream.Close();
}


int VerticalList::GetCoveredItemLoc()
{
	for (uint s = 0; s < nSlot; s++)
	{
		auto frame = GetFrame("VerticalList Slot " + std::to_string(s));
		if (frame->IsCovered())
			return s;
	}
	return -1;
}

void VerticalList::UpdateWidthHeight()
{
	width = itemScale.x + 2 * itemPadding.x;
	height = nSlot * (itemScale.y + itemPadding.y) + 2 * itemPadding.y;
}

const Vector3 VerticalList::GetBoxPosition(const int& slot)  // 이거 하면 되여
{
	return Vector3(
		position.x + itemPadding.x,
		position.y - slot * (itemScale.y + itemPadding.y) - itemPadding.y,
		1.0f);
}
