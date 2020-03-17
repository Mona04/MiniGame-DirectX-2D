#include "Framework.h"
#include "Data_Item.h"

void Data_Item::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(GetName());

		stream.Write(_code);
		stream.Write(_imagePath);
		stream.Write(_itemName);
		stream.Write(_itemInfos);
		stream.Write(_sizeX);
		stream.Write(_sizeY);

		stream.Write(_fire);
		stream.Write(_water);
		stream.Write(_light);
		stream.Write(_dark);
	}
	stream.Close();
}

void Data_Item::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name, itemName;
		stream.Read(name);
		SetName(name);

		stream.Read(_code);
		stream.Read(_imagePath);
		stream.Read(_itemName);
		stream.Read(_itemInfos);
		stream.Read(_sizeX);
		stream.Read(_sizeY);

		stream.Read(_fire);
		stream.Read(_water);
		stream.Read(_light);
		stream.Read(_dark);
	}
	stream.Close();
}
