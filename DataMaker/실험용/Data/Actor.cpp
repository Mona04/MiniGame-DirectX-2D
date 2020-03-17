#include "pch.h"
#include "Actor.h"
#include "..//Data/Data_Mob.h"
#include "..//Data/Data_Skill.h"

void Actor::SaveToFile(const std::string& monsterName, const int& lv, const int& type)
{
	std::string path = "../../_Assets/Scene/Mobs/" + monsterName + ".actor";

	ComponentType componentType;
	
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(6);

		stream.Write(static_cast<uint>(ComponentType::Transform));
		stream.Write(D3DXVECTOR3(0, 0, 0));
		stream.Write(D3DXQUATERNION(0, 0, 0, 0));
		stream.Write(D3DXVECTOR3(50, 50, 0));
		
		stream.Write(static_cast<uint>(ComponentType::Renderable));
		stream.Write("QUAD.mesh");
		stream.Write("QUAD");
		stream.Write("Mobs/default.material");
		stream.Write("default");
		stream.Write(0u);

		stream.Write(static_cast<uint>(ComponentType::Animator));
		stream.Write("//characters//" + monsterName + "//stand_info.txt");
		stream.Write(monsterName + " stand");

		stream.Write(static_cast<uint>(ComponentType::RigidBody));
		stream.Write(static_cast<uint>(RigidBodyType::Character));
		stream.Write(0.00f);
		stream.Write(0.0f);
		stream.Write(D3DXVECTOR3(50, 50, 0));
		stream.Write(D3DXVECTOR3(0, 0, 0));

		std::string core = "";
		if (type == 0) core = "fire";
		if (type == 1) core = "water";
		if (type == 2) core = "light";
		if (type == 3) core = "dark";
		stream.Write(static_cast<uint>(ComponentType::Controller));
		stream.Write(monsterName);
		stream.Write("attack1_" + core + "_lv" + std::to_string(lv / 10 + 1));
		stream.Write("attack2_" + core + "_lv" + std::to_string(lv / 10 + 1));
		stream.Write("gaurd_lv" + std::to_string(lv / 10 + 1));
		stream.Write("N\A");
		stream.Write("N\A");

		stream.Write(static_cast<uint>(ComponentType::Scripter));
		stream.Write("Mobs/Mob_Normal_Actor.as");
		stream.Write("Mob_Normal_Actor.as");

	}
	stream.Close();
	std::cout << monsterName << " end\n";

}

void Actor::SaveToMobData(const std::string& name, const int& lvs)
{
	
	//한번만 다시 돌리자 이름 바뀐거 있음
	auto lv = lvs + rand() % 5;
	Data_Mob* data = new Data_Mob(name);
	data->_mobName = name;
	data->_sizeX = 50.0f;
	data->_sizeY = 50.0f;
	data->_defaultLv = lv;
	data->_maxHp = lv * lv * (lv / 10 + 1) + lv * (3 + rand() % 5) / 2;
	data->_maxMp = lv * lv * (lv / 10 + 1) + lv * (3 + rand() % 5) / 2;
	data->_maxSp = lv * lv * (lv / 10 + 1) + lv * (3 + rand() % 5) / 2;
	data->_maxExp = lv * 10;
	data->_def_fire = lv / 2 + rand() % lv;
	data->_def_water = lv / 2 + rand() % lv;
	data->_def_dark = lv / 2 + rand() % lv;
	data->_def_light = lv / 2 + rand() % lv;
	data->_speed = 6;
	data->_jump = 12;
	if (lv < 15)
	{
		data->_dropItemCode1 = 11;
		data->_dropItemCode2 = 12;
		data->_dropItemCode3 = 13;
		data->_dropItemCode4 = 14;
	}
	else if (lv < 55)
	{
		data->_dropItemCode1 = 21;
		data->_dropItemCode2 = 22;
		data->_dropItemCode3 = 23;
		data->_dropItemCode4 = 24;
	}
	else
	{
		data->_dropItemCode1 = 31;
		data->_dropItemCode2 = 32;
		data->_dropItemCode3 = 33;
		data->_dropItemCode4 = 34;
	}
	data->SaveToFile("../../_Assets/Data/Mob/" + name + ".data");
	SAFE_DELETE(data);
	std::cout << name << " end\n";
}

void Actor::SaveToMobSkill(const int& lvs)
{
	std::string core = "";
	int type = rand() % 4;
	if (type == 0) core = "fire";
	if (type == 1) core = "water";
	if (type == 2) core = "light";
	if (type == 3) core = "dark";
	std::vector<std::string> cores = { "fire", "water", "light", "dark" };
	std::vector<std::string> skillNames = { "attack1_", "attack2_" };
	for (auto& skillName : skillNames)
	{
		for (auto& core : cores)
		{
			std::string name = skillName + core + "_lv" + std::to_string(lvs / 5 + 1);

			//한번만 다시 돌리자 이름 바뀐거 있음
			auto lv = lvs + rand() % 5;
			Data_Skill* data = new Data_Skill(name);
			data->_skillName = name;
			data->_delay_actor = 500.0f;
			data->_delay_stand = 500.0f;
			data->_delay_hit = 500.0f;
			data->_damage_fire = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_damage_water = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_damage_light = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_damage_dark = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_hp_consumed = 0;
			if (data->_skillName.find("attack1") != std::string::npos)
			{
				data->_mp_consumed = 0;
				data->_sp_consumed = ((int)data->_damage_dark / 9) + 5;
			}
			else if (data->_skillName.find("attack2") != std::string::npos)
			{
				data->_sp_consumed = ((int)data->_damage_dark / 3) + 5;
				data->_sp_consumed = ((int)data->_damage_dark / 9) + 5;
			}
			else if (data->_skillName.find("gaurd") != std::string::npos)
			{
				data->_sp_consumed = ((int)data->_damage_dark / 3) + 5;
				data->_sp_consumed = ((int)data->_damage_dark / 9) + 5;
			}

			data->SaveToFile("../../_Assets/Data/Skill/" + name + ".data");
			SAFE_DELETE(data);
			std::cout << name << " end\n";

			std::string _skillName = "luckySeven";

			D3DXVECTOR3 _size_stand = D3DXVECTOR3(10, 10, 0);
			D3DXVECTOR3 _size_hit = D3DXVECTOR3(10, 10, 0);
			D3DXVECTOR3 _distance = D3DXVECTOR3(0, 0, 0);
			float _delay_actor; // delay for actor
			float _delay_stand; // delay for attack effect 
			float _delay_hit;  // delay for attacked effect
			float _damage_fire = 1;
			float _damage_water = 1;
			float _damage_light = 1;
			float _damage_dark = 1;
			float _hp_consumed = 0;
			float _mp_consumed = 0;
			float _sp_consumed = 0;

			D3DXVECTOR3 _knockBack = D3DXVECTOR3(10.0f, 7.0f, 0.0f);
		}
		{
			std::string name = "gaurd_lv" + std::to_string(lvs / 5 + 1);

			//한번만 다시 돌리자 이름 바뀐거 있음
			auto lv = lvs / 5 + 1;
			Data_Skill* data = new Data_Skill(name);
			data->_skillName = name;
			data->_delay_actor = 500.0f;
			data->_delay_stand = 500.0f;
			data->_delay_hit = 500.0f;
			data->_damage_fire = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_damage_water = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_damage_light = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_damage_dark = (lv * lv) / (rand() % (lv / 2 + 1) + 2) + 1;
			data->_hp_consumed = 0;
			data->_mp_consumed = (rand() % lv / 5) * 2 + 1;
			data->_sp_consumed = (rand() % lv / 5) * 2 + 1;

			data->SaveToFile("../../_Assets/Data/Skill/" + name + ".data");
			SAFE_DELETE(data);
		}
	}
}

void Actor::SaveToDialogData(const int& nFloor)
{
	Data_Dialog* data = new Data_Dialog("d");
	{
		std::vector<std::string> npcs = { "Morian", "Fleta", "Cichol", "Blony" };
		for (auto& npc : npcs)
		{
			std::string name = "Floor" + std::to_string(nFloor) + npc + "_Frame";
			data->_dialogScriptPath = "Dialog/" + name + ".as";
			data->SetName(name);
			data->SaveToFile("../../_Assets/Data/Dialog/" + name + ".data");
		}
	}
	SAFE_DELETE(data);
}
