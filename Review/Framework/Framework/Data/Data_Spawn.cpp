#include "Framework.h"
#include "Data_Spawn.h"

void Data_Spawn::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(IData::GetName());
		
		stream.Write(_mobList.size());
		for (const auto& _mob : _mobList)
			stream.Write(_mob);

		stream.Write(_spawnInfoList.size());
		for (const auto& _info : _spawnInfoList)
		{
			stream.Write(_info.pos);
			stream.Write(_info.isAgressive);
		}

	}
	stream.Close();
}

void Data_Spawn::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name, mobName;
		Vector3 pos;
		bool isAgressive;
		int mobListSize, spawnInfoListSize;

		stream.Read(name);
		IData::SetName(name);

		stream.Read(mobListSize);
		for (int i = 0; i < mobListSize; i++)
		{
			stream.Read(mobName);
			_mobList.emplace_back(mobName);
		}

		stream.Read(spawnInfoListSize);
		for (int i = 0; i < spawnInfoListSize; i++)
		{
			stream.Read(pos);
			stream.Read(isAgressive);
			_spawnInfoList.emplace_back(SpawnInfo(pos, isAgressive));
		}
	}
	stream.Close();
}

void Data_Spawn::Init_MobList(const int& nFloor)
{
	if (nFloor < 1) return;

	_mobList.clear();
	_mobList.shrink_to_fit();

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
		grassy, cokeTown, halloween, perion, midForest,
		shineWood, orbis, galaxy, towCastle_low, kerningCity,
		SunsetCity, dragonValley, ereb, forkForest, timeRoad, toyCity_lowerest
	};

	for (auto& name : maps[nFloor - 1])
		_mobList.emplace_back(name);
}
