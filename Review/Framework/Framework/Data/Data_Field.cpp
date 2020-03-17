#include "Framework.h"
#include "Data_Field.h"

Data_Field::Data_Field(const std::string& name)
{
	SetType(DataType::Field);
	SetName(name);
}

void Data_Field::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(IData::GetName());
		stream.Write(_width);
		stream.Write(_height);
		stream.Write(_region);
		for (int i = 0; i < _width * _height; i++)
			stream.Write(_blocks_back[i]);
		for (int i = 0; i < _width * _height; i++)
			stream.Write(_blocks[i]);
		for (int i = 0; i < _width * _height; i++)
			stream.Write(_blocks_functional[i]);
		for (int i = 0; i < _width * _height; i++)
			stream.Write(_blocks_front[i]);
		stream.Write(_backGroundPath);
		stream.Write(_bgmPath);
	}
	stream.Close();
}

void Data_Field::LoadFromFile(const std::string& path)
{
	Clear();

	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name;
		stream.Read(name);
		SetName(name);

		stream.Read(_width);
		stream.Read(_height);
		stream.Read(_region);

		_blocks.reserve(_width * _height);
		_blocks_back.reserve(_width * _height);
		_blocks_front.reserve(_width * _height);
		_blocks_functional.reserve(_width * _height);

		BlockKind kind;
		for (int i = 0; i < _width * _height; i++)
		{
			stream.Read(kind);
			_blocks_back.emplace_back(kind);
		}
		for (int i = 0; i < _width * _height; i++)
		{
			stream.Read(kind);
			_blocks.emplace_back(kind);
		}
		for (int i = 0; i < _width * _height; i++)
		{
			stream.Read(kind);
			_blocks_functional.emplace_back(kind);
		}
		for (int i = 0; i < _width * _height; i++)
		{
			stream.Read(kind);
			_blocks_front.emplace_back(kind);
		}
		stream.Read(_backGroundPath);
		stream.Read(_bgmPath); 
	}
	stream.Close();
}

void Data_Field::Clear()
{
	_width = 0; _height = 0;
	_blocks.clear(); _blocks.shrink_to_fit();
	_blocks_back.clear();  _blocks_back.shrink_to_fit();
	_blocks_functional.clear(); _blocks_functional.shrink_to_fit();
	_blocks_front.clear(); _blocks_front.shrink_to_fit();
}

void Data_Field::Init_Region(const int& nFloor)
{
	_region = nFloor;

	switch (nFloor)
	{
	case  1: _backGroundPath = "Map/Back/Grassy.png"; _bgmPath = "Bgm/Grassy.mp3"; break;
	case  2: _backGroundPath = "Map/Back/CokeTown.png"; _bgmPath = "Bgm/CokeTown.mp3"; break;
	case  3: _backGroundPath = "Map/Back/Halloween.png"; _bgmPath = "Bgm/Halloween.mp3"; break;
	case  4: _backGroundPath = "Map/Back/Perion.png"; _bgmPath = "Bgm/Perion.mp3"; break;
	case  5: _backGroundPath = "Map/Back/MidForest.png"; _bgmPath = "Bgm/Grassy.mp3"; break;
	case  6: _backGroundPath = "Map/Back/ShineWood.png"; _bgmPath = "Bgm/ShineWood.mp3"; break;
	case  7: _backGroundPath = "Map/Back/Orbis.png"; _bgmPath = "Bgm/Orbis.mp3"; break;
	case  8: _backGroundPath = "Map/Back/Galaxy.png"; _bgmPath = "Bgm/Galaxy.mp3"; break;
	case  9: _backGroundPath = "Map/Back/ToyCastle_Low.png"; _bgmPath = "Bgm/ToyCastle_Low.mp3"; break;
	case 10: _backGroundPath = "Map/Back/KerningCity.png"; _bgmPath = "Bgm/KerningCity.mp3"; break;
	case 11: _backGroundPath = "Map/Back/SunsetCity.png"; _bgmPath = "Bgm/KerningCity.mp3"; break;
	case 12: _backGroundPath = "Map/Back/DragonValley.png"; _bgmPath = "Bgm/DragonValley.mp3"; break;
	case 13: _backGroundPath = "Map/Back/Ereb.png"; _bgmPath = "Bgm/CokeTown.mp3"; break;
	case 14: _backGroundPath = "Map/Back/FolkForest.png"; _bgmPath = "Bgm/ForkForest.mp3"; break;
	case 15: _backGroundPath = "Map/Back/TimeRoad.png"; _bgmPath = "Bgm/TimeRoad.mp3"; break;
	case 16: _backGroundPath = "Map/Back/ToyCastle_Lowest.png"; _bgmPath = "Bgm/ToyCastle_Lowest.mp3"; break;
	case 20: _backGroundPath = "Map/Back/NaoZone.png"; _bgmPath = "Bgm/CokeTown.mp3"; break;

	}
}
