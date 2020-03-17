#pragma once
#include "pch.h"
#include "IData.h"

class Data_Spawn : public IData
{
private:
	friend class DataManager;

public:
	Data_Spawn(const std::string& name)
	{
		SetType(DataType::Spawn);
		SetName(name);
	}
	~Data_Spawn() = default;

	void SaveToFile(const std::string& path) ;
	void LoadFromFile(const std::string& path) ;

public:
	std::vector<std::string> _mobList;
	std::vector<D3DXVECTOR2> _spawnPointList;
};