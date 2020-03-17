#include "Framework.h"
#include "ToolTip.h"
#include "IUIComponent.h"

ToolTip::ToolTip(Context* context)
	: IUIComponent(context)
	, position(0.0f, 0.0f, 0.0f), nSlot(3)
	, titleScale(0.1f, 0.2f), titlePadding(0, 0), tagScale(0.1f, 0.2f), tagPadding(0.03f, 0.00f)
	, infoScale(0.1f, 0.2f), infoPadding(0.05f, 0.05f), slotPadding(0.0f, 0.0f)
	, width(0.55)
{
	type = UIComponentType::ToolTip;
	input = context->GetSubsystem<Input>();
	timer = context->GetSubsystem<Timer>();
}

void ToolTip::Init_Default()
{
	Clear();

	{
		auto frame = AddFrame("ToolTip Window");
		frame->GetRenderable()->SetMaterial("UI/UI_ToolTip_Window.material", "UI_ToolTip_Window");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}

	{
		auto frame = AddFrame("ToolTip Title");
		frame->GetRenderable()->SetMaterial("UI/UI_ToolTip_Title.material", "UI_ToolTip_Title");
		frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "mesh" + std::to_string(this->id));
		frame->GetTransform()->SetScale(Vector3(titleScale.x, titleScale.y, 1.0f));
		frame->GetTransform()->SetPosition(Vector3(position.x + titlePadding.x, position.y + titlePadding.y, 1.0f));
		frame->SetText(L"아이템 이름");
	}

	for (uint i = 0; i < nSlot ; i++)
	{
		std::wstring info = L"슬롯 - " + std::to_wstring(i) + L" - 번째 테스트 \n 입니다.";
		Vector3 slotFramePosition = GetSlotFramePosition(i);
		{
			auto frame = AddFrame("ToolTip Slot Frame " + std::to_string(i));
			frame->GetRenderable()->SetMaterial("UI/UI_ToolTip_Frame.material", "UI_Inventory_Frame");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh");
			frame->GetRenderable()->SetTexture(TextureType::Albedo, "UI/ToolTip_Info_Frame.png", "UI/ToolTip_Info_Frame.png");
			frame->GetTransform()->SetScale(GetSlotFrameScale(info));
			frame->GetTransform()->SetPosition(GetSlotFramePosition(i));
			frame->SetIsVisible(true);
		}
		{
			auto frame = AddFrame("ToolTip Slot Tag " + std::to_string(i));
			frame->GetRenderable()->SetMaterial("UI/UI_ToolTip_Frame.material", "UI_ToolTip_Frame");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "mesh tooltip tag " + std::to_string(i) + "-" + std::to_string(this->id));
			frame->GetTransform()->SetScale(Vector3(tagScale.x, tagScale.y, 0.0f));
			frame->GetTransform()->SetPosition(GetSlotFramePosition(i) + Vector3(tagPadding.x, -tagPadding.y, 0));
			frame->SetIsVisible(true);
			frame->SetText(L"태그 이름");
		}
		{
			auto frame = AddFrame("ToolTip Slot Info " + std::to_string(i));
			frame->GetRenderable()->SetMaterial("UI/UI_ToolTip_Frame.material", "UI_ToolTip_Frame");
			frame->GetRenderable()->SetMesh("UI_QUAD.mesh", "mesh tooltip info " + std::to_string(i) + "-" + std::to_string(this->id));
			frame->GetTransform()->SetScale(Vector3(infoScale.x, infoScale.y, 0.0f));
			frame->GetTransform()->SetPosition(GetSlotFramePosition(i) + Vector3(infoPadding.x, -infoPadding.y, 0));
			frame->SetIsVisible(true);
			frame->SetText(info);
		}
	}

	UpdateWidthHeight();
	UpdateTransform();
}

void ToolTip::Clear()
{
	for (auto& frame : frames)
		SAFE_DELETE(frame);
}

void ToolTip::Update()
{
	if (isVisible)
	{
		for (const auto& frame : frames)
			frame->Update();
	}
}

void ToolTip::UpdateTransform()
{
	{
		auto frame = GetFrame("ToolTip Title");
		frame->GetTransform()->SetScale(Vector3(titleScale.x, titleScale.y, 1.0f));
		frame->GetTransform()->SetPosition(Vector3(position.x + titlePadding.x, position.y - titlePadding.y, 1.0f));
	}

	for (uint i = 0; i < nSlot; i++)
	{
		Vector3 slotFramePosition = GetSlotFramePosition(i);
		{
			auto frame = GetFrame("ToolTip Slot Frame " + std::to_string(i));
			//frame->GetTransform()->SetScale(GetSlotFrameScale(info));
			frame->GetTransform()->SetPosition(slotFramePosition);
		}
		{
			auto frame = GetFrame("ToolTip Slot Tag " + std::to_string(i));
			frame->GetTransform()->SetScale(Vector3(tagScale.x, tagScale.y, 0.0f));
			frame->GetTransform()->SetPosition(slotFramePosition + Vector3(tagPadding.x, -tagPadding.y, 0));
		}
		{
			auto frame = GetFrame("ToolTip Slot Info " + std::to_string(i));
			frame->GetTransform()->SetScale(Vector3(infoScale.x, infoScale.y, 0.0f));
			frame->GetTransform()->SetPosition(slotFramePosition + Vector3(infoPadding.x, -infoPadding.y, 0));
		}
	}

	UpdateWidthHeight();

	{
		auto frame = GetFrame("ToolTip Window");
		frame->GetTransform()->SetScale(Vector3(width, height, 1.0f));
		frame->GetTransform()->SetPosition(position);
	}
}

void ToolTip::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		stream.Read(position);
		stream.Read(titleScale);
		stream.Read(titlePadding);
		stream.Read(tagScale);
		stream.Read(tagPadding);
		stream.Read(infoScale);
		stream.Read(infoPadding);
		stream.Read(slotPadding);
		stream.Read(nSlot);
		stream.Read(width);

		AddFrame("ToolTip Window")->LoadFromFile(stream);
		AddFrame("ToolTip Title")->LoadFromFile(stream);

		for (uint i = 0; i < nSlot; i++)
		{
			AddFrame("ToolTip Slot Frame " + std::to_string(i))->LoadFromFile(stream);
			AddFrame("ToolTip Slot Tag " + std::to_string(i))->LoadFromFile(stream);
			AddFrame("ToolTip Slot Info " + std::to_string(i))->LoadFromFile(stream);
		}
	}
	stream.Close();

	UpdateWidthHeight();
	UpdateTransform();
}

void ToolTip::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(position);
		stream.Write(titleScale);
		stream.Write(titlePadding);
		stream.Write(tagScale);
		stream.Write(tagPadding);
		stream.Write(infoScale);
		stream.Write(infoPadding);
		stream.Write(slotPadding);
		stream.Write(nSlot);
		stream.Write(width);

		
		GetFrame("ToolTip Window")->SaveToFile(stream);
		GetFrame("ToolTip Title")->SaveToFile(stream);

		for (uint i = 0; i < nSlot; i++)
		{
			GetFrame("ToolTip Slot Frame " + std::to_string(i))->SaveToFile(stream);
			GetFrame("ToolTip Slot Tag " + std::to_string(i))->SaveToFile(stream);
			GetFrame("ToolTip Slot Info " + std::to_string(i))->SaveToFile(stream);
		}
	}
	stream.Close();
}


void ToolTip::ShowItemInfo(const float& x, const float& y, const Data_Item* itemData)
{
	if (!this->DoesStayEnough(x, y))
		return;
	
	for (auto& frame : frames)
		frame->SetIsVisible(false);

	auto window = GetFrame("ToolTip Window");
	window->SetIsVisible(true);

	auto title = GetFrame("ToolTip Title");
	title->SetText(itemData->_itemName);
	title->SetIsVisible(true);

	int i = 0;
	{
		auto slotFrame = GetFrame("ToolTip Slot Frame " + std::to_string(i));
		auto slotTag = GetFrame("ToolTip Slot Tag " + std::to_string(i));
		auto slotInfo = GetFrame("ToolTip Slot Info " + std::to_string(i));
		
		slotFrame->SetIsVisible(true);
		slotFrame->GetTransform()->SetScale(GetSlotFrameScale(itemData->_itemInfos));
		slotTag->SetIsVisible(true);
		slotTag->SetText(L"아이템 설명");
		slotInfo->SetIsVisible(true);
		slotInfo->SetText(itemData->_itemInfos);
	}
	i = 1;
	{
		auto slotFrame = GetFrame("ToolTip Slot Frame " + std::to_string(i));
		auto slotTag = GetFrame("ToolTip Slot Tag " + std::to_string(i));
		auto slotInfo = GetFrame("ToolTip Slot Info " + std::to_string(i));
		std::wstring info = L"불 에테르 " + std::to_wstring(itemData->_fire) + L"\n물 에테르 " + std::to_wstring(itemData->_water) +
			L"\n빛 에테르 " + std::to_wstring(itemData->_light) + L"\n어둠 에테르 " + std::to_wstring(itemData->_dark);
		slotFrame->SetIsVisible(true);
		slotFrame->GetTransform()->SetScale(GetSlotFrameScale(info));
		slotTag->SetIsVisible(true);
		slotTag->SetText(L"아이템 속성");
		slotInfo->SetIsVisible(true);
		slotInfo->SetText(info);
	}

	UpdateWidthHeight();
	UpdateTransform();
}

bool ToolTip::DoesStayEnough(const float& x, const float& y)
{
	static float _stayTime = 0.0f;
	if (position.x != x || position.y != y)
	{
		position = Vector3(x, y, 0.0f);
		_stayTime = 0.0f;
		this->SetIsVisible(false);

		return false;
	}
	else
	{
		_stayTime += timer->GetDeltaTimeMs();
		if (_stayTime > 1,500)
		{
			_stayTime = 0;
			this->SetIsVisible(true);

			return true;
		}
		else
			return false;
	}
	return false;
}

void ToolTip::UpdateWidthHeight()
{
	height = titleScale.y * 0.4f + titlePadding.y + slotPadding.y;
	for (int i = 0; i < nSlot; i++)
	{
		auto frame = GetFrame("ToolTip Slot Frame " + std::to_string(i));
		if (frame->IsVisible())
			height += frame->GetScale().y + slotPadding.y;
	}
}

int ToolTip::GetNumEnter(const std::wstring& string)
{
	int result = 0;
	for (int i = 0; i < string.length(); i++)
	{
		if (string[i] == L'\n')
			result += 1;
	}
	return result;
}

Vector3 ToolTip::GetSlotFramePosition(const int& i)
{
	float beforeYPosition = position.y - titlePadding.y - slotPadding.y - titleScale.y * 0.4f;

	if (i > 0)
	{
		auto beforeFrame = GetFrame("ToolTip Slot Frame " + std::to_string(i - 1));
		beforeYPosition = beforeFrame->GetPosition().y - beforeFrame->GetScale().y - slotPadding.y;
	}

	return Vector3(
		position.x + slotPadding.x,
		beforeYPosition,
		1.0f);
}

Vector3 ToolTip::GetSlotFrameScale(const std::wstring& string)
{
	;
	int nEnter = GetNumEnter(string);

	return Vector3(width - slotPadding.x * 2.0f, nEnter * infoScale.y * 0.5f + 0.25f, 0);
}
