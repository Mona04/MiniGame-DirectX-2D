#include "Framework.h"
#include "Data_Portal.h"

void Data_Portal::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(_destSceneName);
		stream.Write(_destPos);
	}
	stream.Close();
}

void Data_Portal::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		stream.Read(_destSceneName);
		stream.Read(_destPos);
	}
	stream.Close();
}

