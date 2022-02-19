#pragma once

class FileSystem final
{
public:
	FileSystem() = default;
	~FileSystem() = default;

	static void OpenFilePathDialog(std::function<void(std::string)>&& function, const char* filter, const char* directory);
	static void OpenFileDialog(std::function<void(std::string)>&& function, const char* filter, const char* directory);

	static void CreateFolder(const std::string& path);

	static const bool IsExist(const std::string& path);
	static const bool IsSupportImageFile(const std::string& path);

	static const std::string ToUpper(const std::string& path);
	static const std::wstring ToWString(const std::string& path);
	static const std::string GetSlashPath(const std::string& path);
	static const std::string FindReplace(const std::string& path, const std::string& from, const std::string& to);

	static const std::string GetWorkingDirectory();
	static const std::string GetExtensionFromPath(const std::string& path);
	static const std::string GetDirectoryFromPath(const std::string& path);
	static const std::string GetDirectoryFromPath(const std::string& path, const int& index);
	static const std::string GetDirectoryEndNameFromPath(const std::string& path);
	static const std::string GetFileNameFromPath(const std::string& path);
	static const std::string GetPureNameFromPath(const std::string& path);
	static const std::string GetIntactFileNameFromPath(const std::string& path);
	static const std::string GetRelativeFilePath(const std::string& path);

	static const std::vector<std::string> GetFilesInDirectory(const std::string& path);
	static const std::vector<std::string> GetSupportImageFormats() { return supportImageFormats; }

private:
	static std::vector<std::string> supportImageFormats;
};