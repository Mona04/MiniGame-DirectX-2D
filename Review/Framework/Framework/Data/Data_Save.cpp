#include "Framework.h"
#include "Data_Save.h"

void Data_Save::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(IData::GetName());
		stream.Write(_slot);
		stream.Write(_mapName);
		stream.Write(_protagonist_mobData);
		stream.Write(_lv);
		stream.Write(_jumpFactor);
		stream.Write(_speedFactor);

		stream.Write(_npcs.size());
		for (const auto& npc : _npcs)
			stream.Write(npc);
	}
	stream.Close();
}

void Data_Save::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name;
		stream.Read(name);
		stream.Read(_slot);
		stream.Read(_mapName);
		stream.Read(_protagonist_mobData);
		stream.Read(_lv);
		stream.Read(_jumpFactor);
		stream.Read(_speedFactor);

		int numNpcs = 0;
		stream.Read(numNpcs);
		_npcs.resize(numNpcs);
		for (auto& npc : _npcs)
			stream.Read(npc);

		IData::SetName(name);
	}
	stream.Close();
}