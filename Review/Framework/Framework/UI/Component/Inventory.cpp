#include "Framework.h"
#include "Inventory.h"
#include "IUIWidget.h"


Inventory::Inventory(Context* context)
	: IUIWidget(context)
	, position(0.19f, 0.91f, 0.0f), itemScale(0.063f, 0.123f)
	, itemPadding(0.013f, 0.011f), tagScale(0.116f, 0.104f)
	, amountScale(0.1f, 0.1f), amountPadding(0.0f, 0.0f)
	, maxX(6), maxY(10)
{
	type = UIWidgetType::Inventory;
	mouseManager = context->GetSubsystem<MouseManager>();
}

void Inventory::Init_Default()
{	
	Clear();

	UpdateWidthHeight();
	
	{
		auto frame = AddFrame("Window");
		frame->GetRenderable()->SetMaterial("UI/UI_Inventory_Window.material", "UI_Inventory_Window");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}

	{
		auto frame = AddFrame("Inventory Tag");
		frame->GetRenderable()->SetMaterial("UI/UI_Inventory_Tag.material", "UI_Inventory_Tag");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "mesh" + std::to_string(this->id));
		frame->GetTransform()->SetScale(Vector3(tagScale.x, tagScale.y, 1.0f));
		frame->GetTransform()->SetPosition(Vector3(position.x + itemPadding.x, position.y, 1.0f));
	}

	for (int x = 0; x < maxX; x++)
	{
		for (int y = 0; y < maxY; y++)
		{			
			auto frame = AddFrame("Inventory Slot " + std::to_string(x) + "-" + std::to_string(y));
			frame->GetRenderable()->SetMaterial("UI/UI_Inventory_Slot.material", "UI_Inventory_Slot	");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
			frame->GetTransform()->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(x, y));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}
	}

	for (int x = 0; x < maxX; x++)
	{
		for (int y = 0; y < maxY; y++)
		{
			auto frame = AddFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y));
			frame->GetRenderable()->SetMaterial("UI/UI_Inventory_Slot.material", "UI_Inventory_Slot	");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
			frame->GetTransform()->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(x, y));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(false);
		}
	}

	for (uint x = 0; x < maxX; x++)
	{
		for (uint y = 0; y < maxY; y++)
		{
			auto frame = AddFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y));
			frame->GetRenderable()->SetMaterial("UI/UI_Inventory_Amount.material", "UI_Inventory_Amount ");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "mesh" + std::to_string(this->id) + std::to_string(x) + std::to_string(y));
			frame->GetTransform()->SetScale(Vector3(amountScale.x, amountScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(x, y) + Vector3(amountPadding.x, amountPadding.y, 0.0f));
			frame->SetText(L"11");
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}
	}

}

void Inventory::Clear_Items()
{
	for(int x = 0 ; x < this->maxX ; x++)
		for(int y = 0 ; y < this->maxY; y++)
			DeleteItemAll(x, y);
}

void Inventory::Drag(Camera* camera)
{
	Vector3 worldRay = mouseManager->GetMousePos();
	BoundBox boundBox;
	Vector3 point = GetFrame("Inventory Tag")->GetPosition();
	Vector3 scale = GetFrame("Inventory Tag")->GetScale();
	boundBox.minPoint = Vector3(point.x, point.y - scale.y * 0.4f, 0.0f);
	boundBox.maxPoint = Vector3(point.x + scale.x * 2.0f, point.y, 0.0f);

	static bool isDragging = false;
	static Vector3 start_pos = Vector3(0, 0, 0);
	static Vector3 start_window_pos = Vector3(0, 0, 0);
	if (Intersection::Inside == boundBox.IsInside(worldRay) || isDragging == true)
	{
		if (mouseManager->IsDragged())
		{
			if (isDragging == false)
			{
				start_pos = mouseManager->GetMousePos();
				start_window_pos = position;
			}
			auto _moveVector = mouseManager->GetMousePos() - start_pos;
			this->SetPosition(start_window_pos + _moveVector);
			IUIWidget::pos = position;
			isDragging = true;
		}
		else
		{
			start_pos = Vector3(0, 0, 0);
			isDragging = false;
		}
	}
}

void Inventory::Clear()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);
}

void Inventory::Update()
{
	if (isVisible)
	{
		for (const auto& frame : frames)
			frame->Update();
		Drag();
	}
}

void Inventory::UpdateTransform()
{
	UpdateWidthHeight();

	{
		auto frame = GetFrame("Window");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}
	{
		{
			auto frame = GetFrame("Inventory Tag");
			frame->SetScale(Vector3(tagScale.x, tagScale.y * 2.5f, 1.0f));
			frame->SetPosition(Vector3(position.x + itemPadding.x, position.y, 1.0f));
		}
		for (uint x = 0; x < maxX; x++)
		{
			for (uint y = 0; y < maxY; y++)
			{
				auto frame = GetFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y));
				if (frame)
				{
					frame->SetScale(Vector3(amountScale.x, amountScale.y, 1.0f));
					frame->SetPosition(GetBoxPosition(x, y) + Vector3(amountPadding.x, amountPadding.y, 0.0f));
				}
				auto frame2 = GetFrame("Inventory Slot " + std::to_string(x) + "-" + std::to_string(y));
				if (frame2)
				{
					//frame2->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
					frame2->SetPosition(GetBoxPosition(x, y));
				}
				auto frame3 = GetFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y));
				if (frame3)
				{
					//frame3->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
					frame3->SetPosition(GetBoxPosition(x, y));
				}
			}
		}
	}
}

void Inventory::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		stream.Read(maxX);
		stream.Read(maxY);

		stream.Read(position);  // setting 
		stream.Read(itemScale);
		stream.Read(itemPadding);
		stream.Read(tagScale);
		stream.Read(amountScale);
		stream.Read(amountPadding);

		AddFrame("Window")->LoadFromFile(stream);
		AddFrame("Inventory Tag")->LoadFromFile(stream);

		for (uint x = 0; x < maxX; x++)
		{
			for (uint y = 0; y < maxY; y++)
			{
				AddFrame("Inventory Slot " + std::to_string(x) + "-" + std::to_string(y))->LoadFromFile(stream);
			}
		}
		for (uint x = 0; x < maxX; x++)
		{
			for (uint y = 0; y < maxY; y++)
			{
				AddFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y))->LoadFromFile(stream);
				auto frame = GetFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y));
				if(frame) frame->SetIsVisible(false);
			}
		}
		for (uint x = 0; x < maxX; x++)
		{
			for (uint y = 0; y < maxY; y++)
			{
				AddFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y))->LoadFromFile(stream);
				auto frame = GetFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y));
				if (frame) frame->SetIsVisible(false);
			}
		}
	}
	stream.Close();

	UpdateTransform();
}

void Inventory::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(maxX);
		stream.Write(maxY);

		stream.Write(position);  // setting 
		stream.Write(itemScale);
		stream.Write(itemPadding);
		stream.Write(tagScale);
		stream.Write(amountScale);
		stream.Write(amountPadding);

		GetFrame("Window")->SaveToFile(stream);
		GetFrame("Inventory Tag")->SaveToFile(stream);

		for (uint x = 0; x < maxX; x++)
		{
			for (uint y = 0; y < maxY; y++)
			{
				GetFrame("Inventory Slot " + std::to_string(x) + "-" + std::to_string(y))->SaveToFile(stream);
			}
		}
		for (uint x = 0; x < maxX; x++)
		{
			for (uint y = 0; y < maxY; y++)
			{
				GetFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y))->SaveToFile(stream);
			}
		}
		for (uint x = 0; x < maxX; x++)
		{
			for (uint y = 0; y < maxY; y++)
			{
				GetFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y))->SaveToFile(stream);
			}
		}

	}
	stream.Close();
}

bool Inventory::InsertItem(const int& x, const int& y, const class Data_Item* itemData, const uint& leftAmount)
{
	auto _frame = GetFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y));
	auto _frame_amount = GetFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y));
	if (!_frame || !_frame_amount)
	{
		return false;
	}
	else {
		_frame->GetRenderable()->SetMaterial("UI_Default.material");
		_frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "N\A");
		_frame->GetRenderable()->SetTexture(TextureType::Albedo, itemData->_imagePath, itemData->_imagePath);
		_frame->GetTransform()->SetScale(Vector3(
			(itemScale.x + itemPadding.x) * itemData->_sizeX - itemPadding.x,
			(itemScale.y + itemPadding.y) * itemData->_sizeY - itemPadding.y,
			1.0f));
		_frame->GetTransform()->SetPosition(GetBoxPosition(x, y));
		_frame->SetIsVisible(true);

		_frame_amount->SetText(std::to_wstring(leftAmount));
		_frame_amount->SetIsVisible(true);

		return true;
	}
}

void Inventory::DeleteItem(const int& x, const int& y, const uint& leftAmount)
{
	auto _frame = GetFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y));
	auto _frame_amount = GetFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y));
	if (!_frame)
	{
		return;
	}
	else {
		if (leftAmount == 0u)
		{
			_frame->SetIsVisible(false);
			_frame_amount->SetIsVisible(false);
		}
		else
			_frame_amount->SetText(std::to_wstring(leftAmount));
		return;
	}
}

void Inventory::DeleteItemAll(const int& x, const int& y)
{
	auto _frame = GetFrame("Inventory Item " + std::to_string(x) + "-" + std::to_string(y));
	auto _frame_amount = GetFrame("Inventory Amount " + std::to_string(x) + "-" + std::to_string(y));
	if (!_frame)
	{
		return;
	}
	else {
		_frame_amount->SetIsVisible(false);
		return;
	}
}

int2 Inventory::GetCoveredItemLoc()
{
	for (uint x = 0; x < maxX; x++)
	{
		for (uint y = 0; y < maxY; y++)
		{
			auto frame = GetFrame("Inventory Slot " + std::to_string(x) + "-" + std::to_string(y));
			if (frame && frame->IsCovered())
				return int2(x, y);
		}
	}
	return int2(-1, -1);
}

void Inventory::UpdateWidthHeight()
{
	width = maxX * (itemScale.x + itemPadding.x) + itemPadding.x;
	height = maxY * (itemScale.y + itemPadding.y) + itemPadding.y + tagScale.y;
}

const Vector3 Inventory::GetBoxPosition(const int& x, const int& y)
{
	return Vector3(
		position.x + x * (itemScale.x + itemPadding.x) + itemPadding.x,
		position.y - y * (itemScale.y + itemPadding.y) - itemPadding.y - tagScale.y,
		1.0f);
}
