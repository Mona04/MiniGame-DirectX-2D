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

const std::string FileSystem::GetDirectoryLeft(const std::string& path, const std::string& common)
{
	std::filesystem::path p = std::filesystem::absolute(path);
	std::filesystem::path r = std::filesystem::absolute(common);

	if (p.root_path() != r.root_path())
		return p.generic_string();

	std::filesystem::path result;

	std::filesystem::path::const_iterator iter_p = p.begin();
	std::filesystem::path::const_iterator iter_r = r.begin();

	while (*iter_p == *iter_r && iter_p != p.end() && iter_r != r.end()) {
		iter_p++;
		iter_r++;
	}

	while (iter_p != p.end())
	{
		result /= *iter_p;
		iter_p++;
	}

	return result.generic_string();
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

const bool FileSystem::IsExist(const std::string& path)
{
	bool result = false;

	try
	{
		result = std::filesystem::exists(path);
	}
	catch (std::filesystem::filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "ERROR!!!", MB_OK);
	}

	return result;
}