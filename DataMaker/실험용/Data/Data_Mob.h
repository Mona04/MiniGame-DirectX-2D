#pragma once
#include "pch.h"
#include "IData.h"

enum class MobType : uint
{
	Air = 10000,
	Glass_Up = 11001,
};

class Data_Mob : public IData
{
private:
	friend class DataManager;

public:
	Data_Mob(const std::string& name)
	{
		SetType(DataType::Mob);
		SetName(name);
	}
	~Data_Mob() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);


public:
	std::string _mobName = "slime";
	float _sizeX = 50;
	float _sizeY = 50;

	int _defaultLv = 1;
	int _maxHp = 100;
	int _maxMp = 100;
	int _maxSp = 100;
	int _maxExp = 100;

	int _str = 5;
	int _int = 5;
	int _dex = 5;
	int _will = 5;
	int _luck = 5;
	int _def_fire = 1;
	int _def_water = 1;
	int _def_light = 1;
	int _def_dark = 1;
	int _speed = 4;
	int _jump = 5;

	int _obb = 5;
	int _debuff = 0;
	int _act = 0;

	int _dropItemCode1 = -1;
	int _dropItemCode2 = -1;
	int _dropItemCode3 = -1;
	int _dropItemCode4 = -1;
};