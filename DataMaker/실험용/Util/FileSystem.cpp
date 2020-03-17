#include "pch.h"
#include "FileSystem.h"
#include <filesystem>

const std::string FileSystem::GetFileNameFromPath(const std::string& path)
{
	uint lastIndex = static_cast<uint>(path.find_last_of("\\/"));
	std::string fileName = path.substr(lastIndex + 1, path.length());

	return fileName;
}

const std::string FileSystem::GetIntactFileNameFromPath(const std::string& path)
{
	std::string fileName = GetFileNameFromPath(path);
	uint lastIndex = static_cast<uint>(fileName.find_last_of("."));

	return fileName.substr(0, lastIndex);
}

const std::vector<std::string> FileSystem::GetFilesInDirectory(const std::string& path)
{
	std::vector<std::string> files;

	std::filesystem::directory_iterator endIter;
	for (std::filesystem::directory_iterator iter(path); iter != endIter; iter++)
	{
		if (!std::filesystem::is_regular_file(iter->status()))
			continue;
		files.emplace_back(iter->path().generic_string());
	}

	return files;
}