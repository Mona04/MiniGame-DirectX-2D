#include "pch.h"
#include "Data_Dialog.h"

void Data_Dialog::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(IData::GetName());
		stream.Write(_dialogScriptPath);
		stream.Write(_state);
	}
	stream.Close();
}

void Data_Dialog::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string name;
		stream.Read(name);
		stream.Read(_dialogScriptPath);
		stream.Read(_state);

		IData::SetName(name);
	}
	stream.Close();
}