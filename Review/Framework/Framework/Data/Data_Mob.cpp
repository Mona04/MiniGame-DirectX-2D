#include "Framework.h"
#include "Data_Mob.h"

void Data_Mob::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(IData::GetName());
		stream.Write(_mobName);
		stream.Write(_sizeX);
		stream.Write(_sizeY);

		stream.Write(_defaultLv);
		stream.Write(_maxHp);
		stream.Write(_maxMp);
		stream.Write(_maxSp);
		stream.Write(_maxExp);

		stream.Write(_def_fire);
		stream.Write(_def_water);
		stream.Write(_def_light);
		stream.Write(_def_dark);
		stream.Write(_speed);
		stream.Write(_jump);

		stream.Write(_obb);
		stream.Write(_debuff);
		stream.Write(_act);

		stream.Write(_dropItemCode1);
		stream.Write(_dropItemCode2);
		stream.Write(_dropItemCode3);
		stream.Write(_dropItemCode4);
	}
	stream.Close();
}

void Data_Mob::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name;
		stream.Read(name);
		stream.Read(_mobName);
		stream.Read(_sizeX);
		stream.Read(_sizeY);

		IData::SetName(name);

		stream.Read(_defaultLv);
		stream.Read(_maxHp);
		stream.Read(_maxMp);
		stream.Read(_maxSp);
		stream.Read(_maxExp);

		stream.Read(_def_fire);
		stream.Read(_def_water);
		stream.Read(_def_light);
		stream.Read(_def_dark);
		stream.Read(_speed);
		stream.Read(_jump);

		stream.Read(_obb);
		stream.Read(_debuff);
		stream.Read(_act);

		stream.Read(_dropItemCode1);
		stream.Read(_dropItemCode2);
		stream.Read(_dropItemCode3);
		stream.Read(_dropItemCode4);
	}
	stream.Close();
}