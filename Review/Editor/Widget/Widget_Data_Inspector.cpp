#include "stdafx.h"
#include "Widget_Data_Inspector.h"
#include "./ImGui/Source/imgui.h"

Widget_Data_Inspector::Widget_Data_Inspector(Context* context)
	: IWidget(context)
{
	title = "Data_Inspector";
	dataManager = context->GetSubsystem<DataManager>();
	stringsForDataType = {"Unknown", "Mob", "Skill", "Field", "Portal", "Dialog","Spawn", "Town", "Item", "Inventory" };
}

void Widget_Data_Inspector::Render()
{
	if (!bVisible)
		return;
	

	if (ImGui::Button("ReInitialize DataManager"))
		dataManager->Initialize();

	if (ImGui::Button("Create Tmp"))
		dataManager->CreateDefault(currentDataType);

	if (ImGui::Button("Save Current Data"))
		dataManager->SaveDatas();

	SelectDataType();
	SelectData();

	ShowData();
}


void Widget_Data_Inspector::SelectDataType()
{
	if (static_cast<int>(currentDataType) > stringsForDataType.size() || static_cast<int>(currentDataType) < 0)
		currentDataType = DataType::Mob;

	static const char* item_current = stringsForDataType[static_cast<int>(currentDataType)].c_str();
	if (ImGui::BeginCombo("Data Type", item_current))
	{
		for (uint n = 0; n < static_cast<uint>(stringsForDataType.size()); n++)
		{
			bool is_selected = (item_current == stringsForDataType[n]);
			if (ImGui::Selectable(stringsForDataType[n].c_str(), is_selected))
			{
				item_current = stringsForDataType[n].c_str();
				currentDataType = static_cast<DataType>(n);
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void Widget_Data_Inspector::SelectData()
{
	if (ImGui::Button("Load Data"))
	{
		FileSystem::OpenFileDialog
		(
			[this](std::string str) {
				auto datas = dataManager->GetDatasMap()[currentDataType];
				if(datas.find(FileSystem::GetIntactFileNameFromPath(str)) != datas.end())
					currentData = dataManager->GetDatasMap()[currentDataType][FileSystem::GetIntactFileNameFromPath(str)];
			},
			".data",
			"../../_Assets/Data/"
		);
	}
}

void Widget_Data_Inspector::ShowData()
{
	if (currentData == nullptr)
		return; 
	if (ImGui::CollapsingHeader(currentData->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		DataType type = currentData->GetType();

		ImGui::InputText("DataName", &currentData->GetName());

		switch (type)
		{
		case DataType::Mob:
		{
			Data_Mob* _data = static_cast<Data_Mob*>(currentData);
			ImGui::InputText("MobName", &_data->_mobName);
			ImGui::InputFloat("sizeX", &_data->_sizeX, 0.0f, 100000.0f);
			ImGui::InputFloat("sizeY", &_data->_sizeY, 0.0f, 100000.0f);
			ImGui::InputInt("lv", &_data->_defaultLv, 0.0f, 100000.0f);
			ImGui::InputInt("maxhp", &_data->_maxHp, 0.0f, 100000.0f);
			ImGui::InputInt("maxMp", &_data->_maxMp, 0.0f, 100000.0f);
			ImGui::InputInt("maxSp", &_data->_maxSp, 0.0f, 100000.0f);
			ImGui::InputInt("maxExp", &_data->_maxExp, 0.0f, 100000.0f);
			ImGui::InputInt("Def Fire", &_data->_def_fire, 0.0f, 100000.0f);
			ImGui::InputInt("Def Water", &_data->_def_water, 0.0f, 100000.0f);
			ImGui::InputInt("Def Light", &_data->_def_light, 0.0f, 100000.0f);
			ImGui::InputInt("Def Dark", &_data->_def_dark, 0.0f, 100000.0f);
			ImGui::InputInt("speed", &_data->_speed, 0.0f, 100000.0f);
			ImGui::InputInt("jump", &_data->_jump, 0.0f, 100000.0f);
			ImGui::InputInt("obb", &_data->_obb, 0.0f, 100000.0f);
			ImGui::InputInt("debuff", &_data->_debuff, 0.0f, 100000.0f);
			ImGui::InputInt("dropItem1", &_data->_dropItemCode1, 0.0f, 100000.0f);
			ImGui::InputInt("dropItem2", &_data->_dropItemCode2, 0.0f, 100000.0f);
			ImGui::InputInt("dropItem3", &_data->_dropItemCode3, 0.0f, 100000.0f);
			ImGui::InputInt("dropItem4", &_data->_dropItemCode4, 0.0f, 100000.0f);
			break;
		}
		case DataType::Skill:
		{
			Data_Skill* _data = static_cast<Data_Skill*>(currentData);
			ImGui::InputText("skillName", &_data->_skillName);
			ImGui::InputFloat3("size_stand", &_data->_size_stand[0], "%.3f", ImGuiInputTextFlags_CharsDecimal);
			ImGui::InputFloat3("size_hit", &_data->_size_hit[0], "%.3f", ImGuiInputTextFlags_CharsDecimal);
			ImGui::InputFloat3("distance", &_data->_distance[0], "%.3f", ImGuiInputTextFlags_CharsDecimal);
			ImGui::InputFloat("delay_actor", &_data->_delay_actor, 0.0f, 100000.0f);
			ImGui::InputFloat("delay_stand", &_data->_delay_stand, 0.0f, 100000.0f);
			ImGui::InputFloat("delay_hit", &_data->_delay_hit, 0.0f, 100000.0f);
			ImGui::InputFloat("damage_fire", &_data->_damage_fire, 0.0f, 100000.0f);
			ImGui::InputFloat("damage_water", &_data->_damage_water, 0.0f, 100000.0f);
			ImGui::InputFloat("damage_light", &_data->_damage_light, 0.0f, 100000.0f);
			ImGui::InputFloat("damage_dark", &_data->_damage_dark, 0.0f, 100000.0f);
			ImGui::InputFloat3("knockBack", &_data->_knockBack[0]);
			ImGui::InputFloat("hp_consumed", &_data->_hp_consumed);
			ImGui::InputFloat("mp_consumed", &_data->_mp_consumed);
			ImGui::InputFloat("sp_consumed", &_data->_sp_consumed);
			break;
		}
		case DataType::Field:
		{
			Data_Field* _data = static_cast<Data_Field*>(currentData);
			ImGui::InputInt("width", &_data->_width, 0.0f, 100000.0f);
			ImGui::InputInt("height", &_data->_width, 0.0f, 100000.0f);
			ImGui::InputText("backGround", &_data->_backGroundPath);
			ImGui::InputText("bgm", &_data->_bgmPath);

			break;
		}
		case DataType::Portal:
		{
			Data_Portal* _data = static_cast<Data_Portal*>(currentData);
			ImGui::InputText("destSceneName", &_data->_destSceneName);
			ImGui::InputFloat3("destPos", &_data->_destPos[0], "%.3f", ImGuiInputTextFlags_CharsDecimal);
			break;
		}
		case DataType::Dialog:
		{
			Data_Dialog* _data = static_cast<Data_Dialog*>(currentData);
			ImGui::InputText("dialogScriptPath", &_data->_dialogScriptPath);
			ImGui::InputInt("dialogState", &_data->_state, 0.0f, 100000.0f);
			break;
		}
		case DataType::item:
		{
			Data_Item* _data = static_cast<Data_Item*>(currentData);
			ImGui::InputInt("Code", &_data->_code);
			ImGui::InputText("dialogScriptPath", &_data->_imagePath);
			ImGui::InputInt("SizeX", &_data->_sizeX);
			ImGui::InputInt("SizeY", &_data->_sizeY);
			break;
		}
		case DataType::Inventory:
		{
			Data_Inventory* _data = static_cast<Data_Inventory*>(currentData);
			std::string _name;
			for (int y = 0; y < _data->_maxY; y++)
			{
				for (int x = 0; x < _data->_maxX; x++)
				{
					if (_data->_itemNames.size() > (y * _data->_maxX + x))
					{
						_name = "slot" + std::to_string(y * _data->_maxX + x);
						ImGui::InputText(_name.c_str(), &_data->_itemNames[y * _data->_maxX + x]);
					}
				}
			}
			break;
		}
		}
	}
}