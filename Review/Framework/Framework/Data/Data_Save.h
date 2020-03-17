#pragma once
#include "Framework.h"
#include "IData.h"

class Data_Save : public IData
{
private:
	friend class GameManager;

public:
	Data_Save(const std::string& name)
	{
		SetType(DataType::Save);
		SetName(name);
	}
	~Data_Save() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

public:
	int _slot = 1;
	std::string _mapName = "NaoZone";
	std::string _protagonist_mobData = "ThePepe";
	int _lv = 1;
	float _jumpFactor = 0;
	float _speedFactor = 0;
	std::vector<char> _npcs;
};