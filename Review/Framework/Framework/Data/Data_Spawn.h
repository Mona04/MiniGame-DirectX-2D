#pragma once
#include "Framework.h"
#include "IData.h"

struct SpawnInfo
{
	SpawnInfo(const Vector3& pos, const bool& isAgressive) : pos(pos), isAgressive(isAgressive) {};
	~SpawnInfo() {  }

	Vector3 pos;
	bool isAgressive;
};

class Data_Spawn : public IData
{
private:
	friend class DataManager;
	friend class GameManager;

private:
	Data_Spawn(const std::string& name)
	{
		SetType(DataType::Spawn);
		SetName(name);
	}
	~Data_Spawn() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

public:
	void Init_MobList(const int& nFloor);

public:
	std::vector<std::string> _mobList;
	std::vector<SpawnInfo> _spawnInfoList;
};