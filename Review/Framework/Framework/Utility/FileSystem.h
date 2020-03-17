#pragma once

class FileSystem final
{
public:
	static const char* EveryFilter;
	static const char* TextureFilter;

public:
	static void OpenFileDialog(std::function<void(std::string)>&& func, const char* filter, const char* directory = "");
	static void SaveFileDialog(std::function<void(std::string)>&& function, const char* filter, const char* directory = "");

	static const std::string GetFileNameFromPath(const std::string & path);
	static const std::string GetDirectoryFromPath(const std::string& path);
	static const std::string GetPathWithoutExtension(const std::string& path);
	static const std::string GetIntactFileNameFromPath(const std::string& path);
	static const std::string GetExtensionFromPath(const std::string& path);
	static const std::string GetDirectoryLeft(const std::string& path, const std::string& common);

	static const std::string ToUpper(const std::string& path);
	static const std::string GetParentDirectory(const std::string& path);
	static const std::string GetRelativeFilePath(const std::string& path);
	static const std::string GetWorkingDirectory();

	static const bool IsDirectory(const std::string& path);
	static const bool IsSupportImageFile(const std::string& path);
	static const bool IsFolder(const std::string& path);
	static const bool IsExist(const std::string& path);

	static const std::vector<std::string> GetFilesInDirectory(const std::string& path);
	static const std::vector<std::string> GetAllFilesInDirectory(const std::string& path);
	static const std::vector<std::string> GetFoldersInDirectory(const std::string& path);

	static const std::vector<std::string> GetSupportImageFormats() { return supportImageFormats; }
	static const std::vector<std::string> GetSupportAudioFormats() { return supportAudioFormats; }

	static const std::vector<std::string> GetPartOfName(const std::string& path);

	static const std::wstring ToWstring(const std::string& input);

	static const bool MakeDirectory(const std::string& path);
	
private:
	static std::vector<std::string> supportImageFormats;
	static std::vector<std::string> supportAudioFormats;
};