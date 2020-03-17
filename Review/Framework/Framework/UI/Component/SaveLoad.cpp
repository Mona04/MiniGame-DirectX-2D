#include "Framework.h"
#include "SaveLoad.h"
#include "IUIComponent.h"

SaveLoad::SaveLoad(Context* context)
	: IUIComponent(context)
	, position(-0.498f, 0.664f, 0.0f), tagScale(0.116f, 0.104f)
	, itemPadding(0.038f, 0.015f), itemScale(0.279f, 0.696f)
	, infoScale(0.132f, -0.247f), infoPadding(0.022f, -0.073f)
	, nSlot(3)
{
	type = UIComponentType::SaveLoad;
	mouseManager = context->GetSubsystem<MouseManager>();
	dataManager = context->GetSubsystem<DataManager>();
	gameManager = context->GetSubsystem<GameManager>();
	inventoryManager = context->GetSubsystem<InventoryManager>();
}

void SaveLoad::Init_Default()
{
	Clear();

	UpdateWidthHeight();

	{
		auto frame = AddFrame("Window");
		frame->GetRenderable()->SetMaterial("UI/UI_SaveLoad_Window.material", "UI_SaveLoad_Window");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}

	{
		auto frame = AddFrame("SaveLoad Tag");
		frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "Saveload Tag " + std::to_string(this->id));
		frame->GetTransform()->SetScale(Vector3(tagScale.x, tagScale.y, 1.0f));
		frame->GetTransform()->SetPosition(Vector3(position.x + itemPadding.x, position.y, 1.0f));
	}

	for (uint s = 0; s < nSlot; s++)
	{
		{
			auto frame = AddFrame("SaveLoad Slot " + std::to_string(s));
			frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
			frame->GetTransform()->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(s));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}

		{
			auto frame = AddFrame("SaveLoad Info " + std::to_string(s));
			frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "SaveLoad Slot " + std::to_string(s) + std::to_string(this->id));
			frame->GetTransform()->SetScale(Vector3(infoScale.x, infoScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(s) + Vector3(0, -itemScale.y + -itemPadding.y, 0));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}
	}
}

void SaveLoad::Drag(Camera* camera)
{
	Vector3 worldRay = mouseManager->GetMousePos();
	BoundBox boundBox;
	Vector3 point = GetFrame("SaveLoad Tag")->GetPosition();
	Vector3 scale = GetFrame("SaveLoad Tag")->GetScale();
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
			IUIComponent::pos = position;
			isDragging = true;
		}
		else
		{
			start_pos = Vector3(0, 0, 0);
			isDragging = false;
		}
	}
}

void SaveLoad::Clear()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);
}

void SaveLoad::Update()
{
	if (isVisible)
	{
		if (mouseManager->IsClicked())
		{
			int bCovered = false;
			for (auto& frame : frames)
			{
				if (frame->IsCovered())
					bCovered = true;
			}
			if (bCovered == false)
				this->SetIsVisible(false);
		}

		for (const auto& frame : frames)
			frame->Update();
		Drag();
	}
}

void SaveLoad::UpdateTransform()
{
	UpdateWidthHeight();

	{
		auto frame = GetFrame("Window");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}
	{
		auto frame = GetFrame("SaveLoad Tag");
		frame->SetScale(Vector3(tagScale.x, tagScale.y * 2.5f, 1.0f));
		frame->SetPosition(Vector3(position.x + itemPadding.x, position.y, 1.0f));
	}

	{
		for (uint s = 0; s < nSlot; s++)
		{
			auto frame = GetFrame("SaveLoad Slot " + std::to_string(s));
			if (frame)
			{
				frame->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
				frame->SetPosition(GetBoxPosition(s));
			}
			auto frame2 = GetFrame("SaveLoad Info " + std::to_string(s));
			if (frame2)
			{
				frame2->SetScale(Vector3(infoScale.x, infoScale.y, 1.0f));
				frame2->SetPosition(GetBoxPosition(s) + Vector3(0, -itemScale.y - itemPadding.y, 0));
			}
		}
	}
}

void SaveLoad::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		stream.Read(nSlot);

		stream.Read(position);  // setting 
		stream.Read(itemScale);
		stream.Read(itemPadding);
		stream.Read(tagScale);
		stream.Read(infoScale);
		stream.Read(infoPadding);

		AddFrame("Window")->LoadFromFile(stream);
		AddFrame("SaveLoad Tag")->LoadFromFile(stream);

		for (uint s = 0; s < nSlot; s++)
		{
			AddFrame("SaveLoad Slot " + std::to_string(s))->LoadFromFile(stream);
			AddFrame("SaveLoad Info " + std::to_string(s))->LoadFromFile(stream);
		}
	}
	stream.Close();

	for (auto& frame : frames)
		frame->SetUseDefaultCover(false);

	UpdateTransform();
}

void SaveLoad::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(nSlot);

		stream.Write(position);  // setting 
		stream.Write(itemScale);
		stream.Write(itemPadding);
		stream.Write(tagScale);
		stream.Write(infoScale);
		stream.Write(infoPadding);

		GetFrame("Window")->SaveToFile(stream);
		GetFrame("SaveLoad Tag")->SaveToFile(stream);

		for (uint s = 0; s < nSlot; s++)
		{
			GetFrame("SaveLoad Slot " + std::to_string(s))->SaveToFile(stream);
			GetFrame("SaveLoad Info " + std::to_string(s))->SaveToFile(stream);
		}
	}
	stream.Close();
}


int SaveLoad::GetCoveredItemLoc()
{
	for (uint s = 0; s < nSlot; s++)
	{
		auto frame = GetFrame("SaveLoad Slot " + std::to_string(s));
		if (frame->IsCovered())
			return s;
	}
	return -1;
}

void SaveLoad::UpdateWidthHeight()
{
	width = nSlot * (itemScale.x + itemPadding.x) + itemPadding.x;
	height = (itemScale.y + itemPadding.y) + (infoScale.y + infoPadding.y) + itemPadding.y + tagScale.y;
}

const Vector3 SaveLoad::GetBoxPosition(const int& x)  // 이거 하면 되여
{
	return Vector3(
		position.x + x * (itemScale.x + itemPadding.x) + itemPadding.x,
		position.y - itemPadding.y - tagScale.y,
		1.0f);
}

void SaveLoad::UpdateSlots()
{
	std::string path = "../../_Assets/Texture/UI/noviceCard.png";
	std::wstring info_text;
	std::vector<Data_Mob_Cap> datas;

	if (auto protagonist = gameManager->GetProtagonist())
		datas = dataManager->GetEvolutionTree()->GetAdjacentDatas(Data_Mob_Cap(protagonist->GetComponent<Controller>()->GetMobData()));

	for (int s = 0; s < nSlot; s++)
	{
		auto slot = GetFrame("SaveLoad Slot " + std::to_string(s));
		auto info = GetFrame("SaveLoad Info " + std::to_string(s));

		info->SetText(L"Slot " + std::to_wstring(s + 1));
		Data_Save* saveData = gameManager->GetSaveData(s);

		if (saveData)
		{
			std::string path = "//characters//" + saveData->_protagonist_mobData + "//stand_info.txt";
			slot->GetAnimator()->SetAnimation_OriginScale(path, slot->GetRenderable());
			slot->GetAnimator()->Play();
		}
		else
		{
			path = "../../_Assets/Texture/UI/noviceCard.png";
			slot->GetRenderable()->SetTexture(TextureType::Albedo, path, path);
			slot->GetAnimator()->ResetBuffer();
			slot->GetAnimator()->Stop();
		}
	}
}
