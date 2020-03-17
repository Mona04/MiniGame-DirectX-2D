#pragma once
#include "Framework.h"
#include "IData.h"

enum class Town_Parameter
{
	Tec_Basic,
	Tec_Food,
	Tec_Weapon,
	Tec_Traffic,
	Tec_Comunication,
	Cult_Build,
	Cult_religion,
	Cult_Intertainment,
	Cult_Education,
};

enum class Town_Indicator
{
	Social_Corruption,
	Social_CrimeRate,
	Social_LaborDivision,
	Social_Happiness,
	Economy_Develope,
	Economy_Population,
};

class Data_Town : public IData
{
private:
	friend class DataManager;

private:
	Data_Town(const std::string& name)
	{
		SetType(DataType::Town);
		SetName(name);
	}
	~Data_Town() = default;

	void SaveToFile(const std::string& path) {};
	void LoadFromFile(const std::string& path) {};

public:
	std::string _townName = NULL_STRING;
	
	int _tec_basic = 1;
	int _tec_food = 1;
	int _tec_weapon = 1;
	int _tec_traffic = 1;
	int _tec_comunication = 1;
	int _cult_build = 1;
	int _cult_religion = 1;
	int _cult_intertainment = 1;
	int _cult_education = 1;
	
	float _social_corruption = 0;
	float _social_crimeRate = 0;
	float _social_laborDivision = 0;
	float _social_happiness = 0;
	int _economy_develope = 1;
	int _economy_population = 1;

};