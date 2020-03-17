#pragma once
#include "Framework.h"
#include "IData.h"

class Data_Item : public IData
{
private:
	friend class DataManager;

private:
	Data_Item(const std::string& name)
	{
		SetType(DataType::item);
		SetName(name);
	}
	~Data_Item() = default;
	
	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

public:
	int _code = 1;
	std::string _imagePath = "N/A";
	std::wstring _itemName = L"°«°×";
	std::wstring _itemInfos = L"°«°×À» ¸¸µé±â À§ÇØ¼­ ÀÌÁö¶ö ÁßÀÌ´Ù";
	int _sizeX = 1;
	int _sizeY = 1;
	
	int _fire = 10;
	int _water = 10;
	int _light = 10;
	int _dark = 10;

};