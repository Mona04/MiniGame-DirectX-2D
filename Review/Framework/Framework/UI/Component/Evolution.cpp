#include "Framework.h"
#include "Evolution.h"
#include "IUIWidget.h"

Evolution::Evolution(Context* context)
	: IUIWidget(context)
	, position(0.19f, 0.91f, 0.0f), itemScale(0.221f, 0.416f)
	, itemPadding(0.081f, 0.061f), tagScale(0.116f, 0.104f)
	, infoScale(0.1f, 0.1f), infoPadding(0.0f, 0.365f)
	, tipPosition(0.5f, -0.9f, 0), tipScale(0.077, 0.091)
	, nSlot(3)
{
	type = UIWidgetType::Evolution;
	mouseManager = context->GetSubsystem<MouseManager>();
	dataManager = context->GetSubsystem<DataManager>();
	gameManager = context->GetSubsystem<GameManager>();
	inventoryManager = context->GetSubsystem<InventoryManager>();
}

void Evolution::Init_Default()
{
	Clear();

	UpdateWidthHeight();

	{
		auto frame = AddFrame("Window");
		frame->GetRenderable()->SetMaterial("UI/UI_Evolution_Window.material", "UI_Evolution_Window");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}

	{
		auto frame = AddFrame("Evolution Tag");
		frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "Evolution Tag " + std::to_string(this->id));
		frame->GetTransform()->SetScale(Vector3(tagScale.x, tagScale.y, 1.0f));
		frame->GetTransform()->SetPosition(Vector3(position.x + itemPadding.x, position.y, 1.0f));
	}

	for (uint s = 0; s < nSlot; s++)
	{
		{
			auto frame = AddFrame("Evolution Slot " + std::to_string(s));
			frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
			frame->GetTransform()->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(s));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}

		{
			auto frame = AddFrame("Evolution Info " + std::to_string(s));
			frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "Evolution Slot " + std::to_string(s) + std::to_string(this->id));
			frame->GetTransform()->SetScale(Vector3(infoScale.x, infoScale.y, 1.0f));
			frame->GetTransform()->SetPosition(GetBoxPosition(s) + Vector3(0, - itemScale.y +-itemPadding.y, 0));
			frame->SetUseDefaultCover(true);
			frame->SetIsVisible(true);
		}
	}

	{
		auto frame = AddFrame("Evolution Tip");
		frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "Evolution Tip " + std::to_string(this->id));
		frame->GetTransform()->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
		frame->GetTransform()->SetPosition(position + tipPosition);
		frame->SetText(tipText);
		frame->SetUseDefaultCover(true);
		frame->SetIsVisible(true);
	}
}

void Evolution::Drag(Camera* camera)
{
	Vector3 worldRay = mouseManager->GetMousePos();
	BoundBox boundBox;
	Vector3 point = GetFrame("Evolution Tag")->GetPosition();
	Vector3 scale = GetFrame("Evolution Tag")->GetScale();
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

void Evolution::Clear()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);
}

void Evolution::Update()
{
	if (isVisible)
	{
		for (const auto& frame : frames)
			frame->Update();
		Drag();
		UpdateEvolve();
	}
}

void Evolution::UpdateTransform()
{
	UpdateWidthHeight();

	{
		auto frame = GetFrame("Window");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}
	{
		auto frame = GetFrame("Evolution Tag");
		frame->SetScale(Vector3(tagScale.x, tagScale.y * 2.5f, 1.0f));
		frame->SetPosition(Vector3(position.x + itemPadding.x, position.y, 1.0f));
	}
	{
		auto frame = GetFrame("Evolution Tip");
		frame->SetScale(Vector3(tipScale.x, tipScale.y * 2.5f, 1.0f));
		frame->SetPosition(position + tipPosition);
	}

	{
		for (uint s = 0; s < nSlot; s++)
		{
			auto frame = GetFrame("Evolution Slot " + std::to_string(s));
			if (frame)
			{
				frame->SetScale(Vector3(itemScale.x, itemScale.y, 1.0f));
				frame->SetPosition(GetBoxPosition(s));
			}
			auto frame2 = GetFrame("Evolution Info " + std::to_string(s));
			if (frame2)
			{
				frame2->SetScale(Vector3(infoScale.x, infoScale.y, 1.0f));
				frame2->SetPosition(GetBoxPosition(s) + Vector3(0, - itemScale.y - itemPadding.y, 0));
			}
		}
	}
}

void Evolution::LoadFromFile(const std::string& path)
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
		stream.Read(tipPosition);
		stream.Read(tipScale);

		AddFrame("Window")->LoadFromFile(stream);
		AddFrame("Evolution Tag")->LoadFromFile(stream);

		for (uint s = 0; s < nSlot; s++)
		{
			AddFrame("Evolution Slot " + std::to_string(s))->LoadFromFile(stream);
			AddFrame("Evolution Info " + std::to_string(s))->LoadFromFile(stream);
		}

		AddFrame("Evolution Tip")->LoadFromFile(stream);
		GetFrame("Evolution Tip")->SetText(tipText);
	}
	stream.Close();

	for (auto& frame : frames)
		frame->SetUseDefaultCover(false);

	UpdateTransform();
}

void Evolution::SaveToFile(const std::string& path)
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
		stream.Write(tipPosition);
		stream.Write(tipScale);

		GetFrame("Window")->SaveToFile(stream);
		GetFrame("Evolution Tag")->SaveToFile(stream);

		for (uint s = 0; s < nSlot; s++)
		{
			GetFrame("Evolution Slot " + std::to_string(s))->SaveToFile(stream);
			GetFrame("Evolution Info " + std::to_string(s))->SaveToFile(stream);
		}

		GetFrame("Evolution Tip")->SaveToFile(stream);

	}
	stream.Close();
}


int Evolution::GetCoveredItemLoc()
{
	for (uint s = 0; s < nSlot; s++)
	{
		auto frame = GetFrame("Evolution Slot " + std::to_string(s));
		if (frame->IsCovered())
			return s;
	}
	return -1;
}

void Evolution::UpdateWidthHeight()
{
	width = nSlot * (itemScale.x + itemPadding.x) + itemPadding.x;
	height = (itemScale.y + itemPadding.y) + (infoScale.y + infoPadding.y) + itemPadding.y + tagScale.y;
}

const Vector3 Evolution::GetBoxPosition(const int& x)  // 이거 하면 되여
{
	return Vector3(
		position.x + x * (itemScale.x + itemPadding.x) + itemPadding.x,
		position.y - itemPadding.y - tagScale.y,
		1.0f);
}

void Evolution::UpdateEvolve()
{
	if (auto protagonist = gameManager->GetProtagonist())
	{
		auto datas = dataManager->GetEvolutionTree()->GetAdjacentDatas(protagonist->GetComponent<Controller>()->GetMobData());

		for (int s = 0; s < datas.size(); s++)
		{
			auto slot = GetFrame("Evolution Slot " + std::to_string(s));
			if (slot->IsClicked())
			{
				int n_herb_blue = inventoryManager->GetItemStock("Herb_Blue");   // as various items can make up a required score 
				int n_herb_red = inventoryManager->GetItemStock("Herb_Red");
				int n_herb_white = inventoryManager->GetItemStock("Herb_Light");
				int n_herb_dark = inventoryManager->GetItemStock("Herb_Dark");
				Data_Mob* mob_data = datas[s];

				inventoryManager->DeleteItem_Auto("Herb_Blue", mob_data->_def_water);
				inventoryManager->DeleteItem_Auto("Herb_Red", mob_data->_def_fire);
				inventoryManager->DeleteItem_Auto("Herb_Light", mob_data->_def_light);
				inventoryManager->DeleteItem_Auto("Herb_Dark", mob_data->_def_dark);
				protagonist->GetComponent<Controller>()->Evolution(mob_data->_mobName);
				this->UpdateSlots();
			}
			
		}
	}
}

void Evolution::UpdateSlots()
{
	std::string path = "../../_Assets/Texture/UI/noviceCard.png";
	std::wstring info_text;
	std::vector<Data_Mob*> datas;

	if(auto protagonist = gameManager->GetProtagonist())
		datas = dataManager->GetEvolutionTree()->GetAdjacentDatas(protagonist->GetComponent<Controller>()->GetMobData());

	for (int s = 0; s < nSlot; s++)
	{
		auto slot = GetFrame("Evolution Slot " + std::to_string(s));
		auto info = GetFrame("Evolution Info " + std::to_string(s));

		if (s < datas.size())
		{
			Data_Mob* data = datas[s];
			bool bEvolve = IsAbleEvolution(data);
			info_text = L"요구 Lv : " + std::to_wstring(data->_defaultLv) + L"\n불    에테르 : " + std::to_wstring(data->_def_fire)
				+ L"\n물    에테르 : " + std::to_wstring(data->_def_water) + L"\n빛    에테르 : " + std::to_wstring(data->_def_light)
				+ L"\n어둠 에테르 : " + std::to_wstring(data->_def_dark);			
			path = "//characters//" + datas[s]->_mobName + "//stand_info.txt";

			slot->GetAnimator()->SetAnimation_OriginScale(path, slot->GetRenderable());
			slot->GetAnimator()->Play();
			slot->SetClickLock(!bEvolve);
			slot->SetUseDefaultCover(bEvolve);
			info->SetText(info_text);
		}
		else
		{
			info_text = L"\n요구 Lv : " + std::to_wstring(0) + L"\n불    에테르 : " + std::to_wstring(0)
				+ L"\n물    에테르 : " + std::to_wstring(0) + L"\n빛    에테르 : " + std::to_wstring(0)
				+ L"\n어둠 에테르 : " + std::to_wstring(0);
			path = "../../_Assets/Texture/UI/noviceCard.png";

			slot->GetRenderable()->SetTexture(TextureType::Albedo, path, path);
			slot->GetAnimator()->ResetBuffer();
			slot->GetAnimator()->Stop();
			slot->SetClickLock(true);
			slot->SetUseDefaultCover(false);
			info->SetText(info_text);
		}
	}
}

bool Evolution::IsAbleEvolution(Data_Mob* obj)
{
	uint e_water = 0; uint e_fire = 0; uint e_dark = 0; uint e_light = 0;
	e_water += inventoryManager->GetItemStock("Herb_Blue");
	e_fire += inventoryManager->GetItemStock("Herb_Red");
	e_light += inventoryManager->GetItemStock("Herb_Light");
	e_dark += inventoryManager->GetItemStock("Herb_Dark");

	if (obj->_defaultLv <= gameManager->GetProtagonist()->GetComponent<Controller>()->GetLv())
	{
		if (obj->_def_water <= e_water && obj->_def_fire <= e_fire &&
			obj->_def_dark <= e_dark && obj->_def_light <= e_light)
			return true;
	}
	return false;
}
