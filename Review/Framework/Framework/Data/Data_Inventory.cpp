#include "Data_Inventory.h"
#include "Framework.h"

// slot type = [ itemName, positive ], [ N\A, 0], [ "Occupied", original loc (y * maxX + y)]
#define LOC loc.second * _maxX + loc.first
#define LOC_SIZE (loc.second + _sizeY) * _maxX + loc.first + _sizeX

void Data_Inventory::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(IData::GetName());
		stream.Write(_maxX);
		stream.Write(_maxY);

		for (auto& data : _itemNames)
			stream.Write(data);

		for (auto& data : _itemAmount)
			stream.Write(data);
	}
	stream.Close();
}

void Data_Inventory::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name, itemName;
		uint itemAmount;
		stream.Read(name);
		SetName(name);

		stream.Read(_maxX);
		stream.Read(_maxY);

		_itemNames.resize(_maxX * _maxY);
		_itemAmount.resize(_maxX * _maxY);

		for (int i = 0; i < _maxX * _maxY; i++)
		{
			stream.Read(itemName);
			_itemNames[i] = itemName;
		}

		for (int i = 0; i < _maxX * _maxY; i++)
		{
			stream.Read(itemAmount);
			_itemAmount[i] = itemAmount;
		}
	}
	stream.Close();
}

void Data_Inventory::Clear()
{
	_maxX = 1;
	_maxY = 1;
	_itemNames.clear();
	_itemNames.shrink_to_fit();
}

void Data_Inventory::InitDefault(const int& x, const int& y)
{
	Clear();

	_maxX = x;
	_maxY = y;
	for (int i = 0; i < _maxX * _maxY; i++)
		_itemNames.emplace_back("N\A");
	for (int i = 0; i < _maxX * _maxY; i++)
		_itemAmount.emplace_back(0u);
}

std::pair <int, int> Data_Inventory::InsertItem(const int& x, const int& y, Data_Item* item, const uint& amount)
{
	if (x > _maxX || y > _maxY || item == nullptr)
		return std::make_pair(-1, -1);

	if (x + item->_sizeX - 1 >= _maxX || y + item->_sizeY - 1 >= _maxY)  // out of inventory edge
		return std::make_pair(-1, -1);

	auto loc = Adjust_Loc(x, y);

	if (_itemNames[LOC] == item->GetName())  // already exist same one;
	{
		_itemAmount[LOC] += amount;
	}
	else  
	{
		for (int _sizeX = 0; _sizeX < item->_sizeX; _sizeX++) // check if required slot is null
		{
			for (int _sizeY = 0; _sizeY < item->_sizeY; _sizeY++)
			{
				if (_itemNames[(y + _sizeY) * _maxX + x + _sizeX] != "N\A")
					return std::make_pair(-1, -1);
			}
		}

		for (int _sizeX = 0; _sizeX < item->_sizeX; _sizeX++) // insert
		{
			for (int _sizeY = 0; _sizeY < item->_sizeY; _sizeY++)
			{
				if (_sizeX == 0 && _sizeY == 0)
				{
					_itemNames[(y + _sizeY) * _maxX + x + _sizeX] = item->GetName();
					_itemAmount[(y + _sizeY) * _maxX + x + _sizeX] = amount;
				}
				else
				{
					_itemNames[(y + _sizeY) * _maxX + x + _sizeX] = "Occupied";
					_itemAmount[(y + _sizeY) * _maxX + x + _sizeX] = y * _maxX + x;
				}
			}
		}
	}
	return loc;
}

std::pair<int, int> Data_Inventory::DeleteItem(const int& x, const int& y, Data_Item* item, const uint& amount)
{
	if (x > _maxX || y > _maxY)
		return std::make_pair(-1, -1);

	auto loc = Adjust_Loc(x, y);

	std::string result_str = _itemNames[LOC];
	uint result_amount = _itemAmount[LOC];

	if (_itemAmount[LOC] == amount)
	{
		for (int _sizeX = 0; _sizeX < item->_sizeX; _sizeX++) // insert
		{
			for (int _sizeY = 0; _sizeY < item->_sizeY; _sizeY++)
			{
				if (_sizeX == 0 && _sizeY == 0)
				{
					_itemNames[LOC_SIZE] = "N\A";
					_itemAmount[LOC_SIZE] = 0;
				}
				else
				{
					_itemNames[LOC_SIZE] = "N\A";
					_itemAmount[LOC_SIZE] = 0;
				}
			}
		}
	}
	else
	{
		_itemAmount[LOC] = _itemAmount[LOC] - amount;
	}

	return std::make_pair(loc.first, loc.second);
}

std::pair<int, int> Data_Inventory::DeleteItemAll(const int& x, const int& y, class Data_Item* item)
{
	if (x > _maxX || y > _maxY)
		return std::make_pair(-1, -1);
	
	auto loc = Adjust_Loc(x, y);

	std::string result_str = _itemNames[LOC];
	uint result_amount = _itemAmount[LOC];

	for (int _sizeX = 0; _sizeX < item->_sizeX; _sizeX++) // insert
	{
		for (int _sizeY = 0; _sizeY < item->_sizeY; _sizeY++)
		{
			if (_sizeX == 0 && _sizeY == 0)
			{
				_itemNames[LOC_SIZE] = "N\A";
				_itemAmount[LOC_SIZE] = 0;
			}
			else
			{
				_itemNames[LOC_SIZE] = "N\A";
				_itemAmount[LOC_SIZE] = 0;
			}
		}
	}

	return std::make_pair(loc.first, loc.second);
}

uint Data_Inventory::GetItemStock(Data_Item* item)
{
	if (!item)
		return 0;
	uint result = 0;

	for (int x = 0; x < _maxX; x++)
	{
		for (int y = 0; y < _maxY; y++)
		{
			if (_itemNames[y * _maxX + x] == item->GetName())
				result += _itemAmount[y * _maxX + x];
		}
	}
	return result;
}

std::vector<std::pair<int, int>> Data_Inventory::GetItemLoc(Data_Item* item)
{
	std::vector<std::pair<int, int>> result;
	for (int x = 0; x < _maxX; x++)
	{
		for (int y = 0; y < _maxY; y++)
		{
			if (_itemNames[y * _maxX + x] == item->GetName())
				result.emplace_back(std::make_pair(x, y));
		}
	}
	return result;
}

std::string Data_Inventory::GetItemName(const int& x, const int& y)
{
	if (x > _maxX || y > _maxY)
		return "N\A";

	auto loc = Adjust_Loc(x, y);

	return _itemNames[LOC];
}

uint Data_Inventory::GetItemAmount(const int& x, const int& y)
{
	if (x > _maxX || y > _maxY)
		return false;
	
	auto loc = Adjust_Loc(x, y);

	return _itemAmount[LOC];
}

std::pair<uint, uint> Data_Inventory::Adjust_Loc(const int& x, const int& y)
{
	std::string result_str = _itemNames[y * _maxX + x];
	uint _x, _y;

	if (result_str == "Occupied")   // adjust to original location
	{
		result_str = _itemNames[_itemAmount[y * _maxX + x]];
		_x = _itemAmount[y * _maxX + x] % _maxX;
		_y = _itemAmount[y * _maxX + x] / _maxX;
	}
	else
	{
		_x = x;
		_y = y;
	}

	return std::make_pair(_x, _y);
}
