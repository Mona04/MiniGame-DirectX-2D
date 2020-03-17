#pragma once
#include "Framework.h"
#include "IData.h"

class Data_Inventory : public IData
{
private:
	friend class DataManager;
	friend class GameManager;

private:
	Data_Inventory(const std::string& name) { SetName(name); SetType(DataType::Inventory); InitDefault(6, 10); }
	~Data_Inventory() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

	void Clear();


public:
	void InitDefault(const int& x, const int& y);

	std::pair<int, int> InsertItem(const int& x, const int& y, class Data_Item* item, const uint& amount);
	std::pair<int, int> DeleteItem(const int& x, const int& y, class Data_Item* item, const uint& amount);
	std::pair<int, int> DeleteItemAll(const int& x, const int& y, class Data_Item* item);
	uint GetItemStock(class Data_Item* item);
	std::vector<std::pair<int, int>> GetItemLoc(class Data_Item* item);

	std::string GetItemName(const int& x, const int& y);
	uint GetItemAmount(const int& x, const int& y);
	std::pair<uint, uint> Adjust_Loc(const int& x, const int& y);

public:
	int _maxX = 0;
	int _maxY = 0;
	std::vector<std::string> _itemNames;
	std::vector<uint> _itemAmount;
};