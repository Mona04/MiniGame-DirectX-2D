#include "pch.h"
#include "Data/Data_Mob.h"
#include "Data/Data_Skill.h"
#include "Data/Data_Item.h"
#include "Data/Actor.h"

void main()
{
	std::vector<std::string> grassy = {
		"snail", "snail_blue",  "snail_red",
		"slime", "mushroom_orange",  "stump"
	};

	std::vector<std::string> cokeTown = {
		"slime_buble", "slime_coke",  "sill_coke",
		"mushroom_blue",  "pig", "pig_ribon",
		"mushroom_coke",  "stump_dark",  "mask_wood",
	};

	std::vector<std::string> halloween = {
		"slime_cube",  "mushroom_zombie",  "pig_wild",
		"pig_fire",  "eye_evil",  "eye_cuz",
		"mushroom_horn",  "lace_junior",  "octopus",
		"stump_axe",  "stump_darkaxe",  "mask_stone",
		"stoneball"
	};

	std::vector<std::string> perion = {
		"sandrabbit",  "blockpus",
		"blockpus_king",  "sandrabbit_brown",  "mushroom_green",
		"raccoon_fire",  "eye_cold",  "catus_junior",
		"lace",  "matian",  "matian_pla",
		"catus",  "stoneball_fire",  "stoneball_ice",
	};

	std::vector<std::string> midForest = {
		"cow",  "cow_bull",  "lantern",
		"sheep",  "sheep_black",  "cronos",
		"cronos_platoon",  "cronos_master",  "catus_loyal",
	};

	std::vector<std::string> shineWood = {
		"hobbyhorse",  "robo",  "boogie_junior",
		"boogie",  "mute_iron",  "mute_mithril",
		"treelord",  "treelord_big",
	};

	std::vector<std::string> orbis = {
		 "robo_master",
		"pixie_star",  "pixie_lunar",  "pixie_ghost",
		"firebomb",  "mute_enhanced_mithril",
	};

	std::vector<std::string> galaxy = {
		 "pixie_lust",
		"gray_banad",  "gray_ultra",  "gruffin_junior",
		"sallion_junior", "lioner_junior",  "bigeup",
	};

	std::vector<std::string> towCastle_low = {
		"buffy",  "buffy_razy",  "gruffin",
		"sallion",  "lioner",  "teddy_soul",
		"teddy_mastersoul",
	};

	std::vector<std::string> kerningCity = {
	  "poonco",  "poosco",
		"luinel_junior",  "luinel",  "drake_capa",
		"drake",  "saity",  "skeleton",
		"skeleton_officer",
	};

	std::vector<std::string> SunsetCity = {
	  "tiktok", "drake_ice",
		"drake_red",  "drake_dark",  "skeleton_horse",
		"priest_oblivion",
	};

	std::vector<std::string> dragonValley = {
		 "cago_wild",  "centaur_dark",
		"centaur_blue",  "wyvern_blue",  "wyvern_red",
		"wyvern_dark", "priest_regret",
	};

	std::vector<std::string> ereb = {
		 "half_blood",	"tauromasis",  "taurospear",  "priest_recollection",
	};

	std::vector<std::string> forkForest = {
		"rich",
	};

	std::vector<std::string> timeRoad = {
	 "clock",  "clock_dark",	"skelegon",  "skelos",
	};
	std::vector<std::string> toyCity_lowerest = {
		 "pantomwatch", "viking",  "tanatos",
	};

	std::vector<std::vector<std::string>> maps = {
		orbis, galaxy, towCastle_low, kerningCity,
		SunsetCity, dragonValley, ereb, forkForest, timeRoad, toyCity_lowerest
	};


	int lvs = 31;
	for (const auto& names : maps)
	{
		for (const auto& name : names)
		{
			//Actor::SaveToMobData(name, lvs);
			//Actor::SaveToFile(name, lvs, rand() % 4);
			//std::cout << name << std::endl;
		}
		//Actor::SaveToMobSkill(lvs);
		lvs += 5;
	};

	for (int i = 1; i < 17; i++)
	{
	//	Actor::SaveToDialogData(i);
	}

	for (auto& file : FileSystem::GetFilesInDirectory("../../_Assets/Data/Skill/"))
	{
		continue;
		
		std::string fileName = FileSystem::GetIntactFileNameFromPath(file);
		int lv = -1;
		for (int i = 5; i < 9; i++)
		{
			if (fileName.find("lv" + std::to_string(i)) != std::string::npos)
				lv = i * 10 - 9;
		}
		if (lv == -1)
		{
			int fuct;
			continue;
		}
		Data_Skill* data = new Data_Skill("a");
		data->LoadFromFile(file);
		if (data->_skillName.find("attack1") != std::string::npos)
		{
			data->_damage_dark = (lv * lv * (lv / 10 + 1)) / 17 + lv * (1 + rand() % 3);
			data->_damage_fire = (lv * lv * (lv / 10 + 1)) / 17 + lv * (1 + rand() % 3);
			data->_damage_light = (lv * lv * (lv / 10 + 1)) / 17 + lv * (1 + rand() % 3);
			data->_damage_fire = (lv * lv * (lv / 10 + 1)) / 17 + lv * (1 + rand() % 3);
			data->_mp_consumed = 0;
			data->_sp_consumed = 1.0f * (((int)data->_damage_dark + (int)data->_damage_fire  + (int)data->_damage_light  + (int)data->_damage_water)) + 1;
		}
		else if (data->_skillName.find("attack2") != std::string::npos)
		{
			data->_damage_dark = (lv * lv * (lv / 10 + 1)) / 9 + lv * (1 + rand() % 3) * 2;
			data->_damage_fire = lv * lv * (lv / 10 + 1)  / 9 + lv * (1 + rand() % 3) * 2;
			data->_damage_light = lv * lv * (lv / 10 + 1) / 9 + lv * (1 + rand() % 3) * 2;
			data->_damage_fire = lv * lv * (lv / 10 + 1) / 9 + lv * (1 + rand() % 3) * 2;
			data->_mp_consumed = 1.3f * ((int)data->_damage_dark + (int)data->_damage_fire + (int)data->_damage_light + (int)data->_damage_water) + 1;
			data->_sp_consumed = 1.3f * ((int)data->_damage_dark + (int)data->_damage_fire + (int)data->_damage_light + (int)data->_damage_water) + 1;
		}
		else if (data->_skillName.find("gaurd") != std::string::npos)
		{
			data->_mp_consumed = 2 * (lv * lv * (lv / 10 + 1)) / 40 + lv * (5 + rand() % 5);
			data->_sp_consumed = 2 * (lv * lv * (lv / 10 + 1)) / 40 + lv * (5 + rand() % 5);
		}
		data->SaveToFile(file);
	}
	

	 // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	std::string name = "Necklace";  // ##
	Data_Item* itemData = new Data_Item(name); 
	itemData->_code = 56; // ##
	itemData->_imagePath = "Item/Consume/" + name +  ".png";
	itemData->_itemName = L"금속 목걸이"; // ##
	itemData->_itemInfos = L"개가 불편해 하지 않아서\n인기 만점이라는 금속제\n목걸이이다."; // ##
	itemData->_sizeX = 2;  //##
	itemData->_sizeY = 1;  // ##
	itemData->_fire = 0;   //##
	itemData->_water = 0;   //##
	itemData->_light = 0;   //##
	itemData->_dark = 0;    //##
	
	itemData->SaveToFile("../../_Assets/Data/Item/" + name + ".data");

}


