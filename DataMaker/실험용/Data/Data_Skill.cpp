#include "pch.h"
#include "Data_Skill.h"

void Data_Skill::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(IData::GetName());
		stream.Write(_skillName);

		stream.Write(_size_stand);
		stream.Write(_size_hit);
		stream.Write(_distance);
		stream.Write(_delay_actor);
		stream.Write(_delay_stand);
		stream.Write(_delay_hit);
		stream.Write(_damage_fire);
		stream.Write(_damage_water);
		stream.Write(_damage_light);
		stream.Write(_damage_dark);
		stream.Write(_knockBack);
		stream.Write(_hp_consumed);
		stream.Write(_mp_consumed);
		stream.Write(_sp_consumed);
	}
	stream.Close();
}

void Data_Skill::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name;
		stream.Read(name);
		stream.Read(_skillName);

		IData::SetName(name);

		stream.Read(_size_stand);
		stream.Read(_size_hit);
		stream.Read(_distance);
		stream.Read(_delay_actor);
		stream.Read(_delay_stand);
		stream.Read(_delay_hit);
		stream.Read(_damage_fire);
		stream.Read(_damage_water);
		stream.Read(_damage_light);
		stream.Read(_damage_dark);
		stream.Read(_knockBack);
		stream.Read(_hp_consumed);
		stream.Read(_mp_consumed);
		stream.Read(_sp_consumed);
	}
	stream.Close();
}