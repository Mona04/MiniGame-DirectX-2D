#include "pch.h"
#include "Data_Spawn.h"

void Data_Spawn::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(GetName());

		stream.Write(_mobList.size());
		for (const auto& _mob : _mobList)
			stream.Write(_mob);

		stream.Write(_spawnPointList.size());
		for (const auto& _point : _spawnPointList)
			stream.Write(_point);
	}
	stream.Close();
}

void Data_Spawn::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name, mobName;
		D3DXVECTOR3 point;
		int mobListSize, spawnPointListSize;

		stream.Read(name);

		stream.Read(mobListSize);
		for (int i = 0; i < mobListSize; i++)
		{
			stream.Read(mobName);
			_mobList.emplace_back(mobName);
		}

		stream.Read(spawnPointListSize);
		for (int i = 0; i < spawnPointListSize; i++)
		{
			stream.Read(point);
			_spawnPointList.emplace_back(point);
		}
	}
	stream.Close();
}