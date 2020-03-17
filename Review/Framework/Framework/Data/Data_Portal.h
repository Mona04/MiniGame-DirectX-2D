#pragma once
#include "Framework.h"
#include "IData.h"

class Data_Portal : public IData
{
private:
	friend class DataManager;

public:
	Data_Portal(const std::string& name)
	{
		SetType(DataType::Portal);
		SetName(name);
	}
	~Data_Portal() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

public:
	std::string _destSceneName = "floor1";
	Vector3 _destPos = Vector3(0, 0, 0);
};