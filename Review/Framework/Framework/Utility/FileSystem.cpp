#include "Framework.h"
#include "FileSystem.h"
#include <filesystem>
#include <commdlg.h>

std::vector<std::string> FileSystem::supportImageFormats =
{
	".jpg", ".png", ".bmp", ".tga", ".dds",
	".exr", ".raw", ".gif", ".hdr", ".ico",
	".iff", ".jng", ".jpeg", ".koala", ".kodak",
	".mng", ".pcx", ".pbm", ".pgm", ".ppm",
	".pfm", ".pict", ".psd", ".raw", ".sgi",
	".targa", ".tiff", ".tif", ".wbmp", ".webp",
	".xbm", ".xpm"
};

std::vector<std::string> FileSystem::supportAudioFormats =
{
	".aiff", ".asf", ".asx", ".dls", ".flac",
	".fsb", ".it", ".m3u", ".midi", ".mod",
	".mp2", ".mp3", ".ogg", ".pls", ".s3m",
	".vag" /*ps2*/, ".wav", ".wax", ".wma",
	".xm", ".xma" // XBOX 360
};

const char* FileSystem::EveryFilter = "Every File(*.*)\0*.*;\0";
const char* FileSystem::TextureFilter = "Texture File(*.png, *.bmp, *.jpg)\0*.png;*.bmp;*.jpg;\0";

void FileSystem::OpenFileDialog(std::function<void(std::string)>&& function, const char * filter, const char * directory)
{
	char buffer[255];
	ZeroMemory(buffer, 255);

	char initialPath[255];
	ZeroMemory(initialPath, 255);
	_fullpath(initialPath, directory, 255);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Setting::Get()->GetWindowHandle();
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = buffer;
	ofn.lpstrInitialDir = initialPath;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE) {

		std::string path = std::string(buffer);
		std::function<void(std::string)> func =
			std::forward<std::function<void(std::string)>>(function);

		if (!function)
			func(path);
	}
}

void FileSystem::SaveFileDialog(std::function<void(std::string)>&& function, const char* filter, const char* directory)
{
	char buffer[255];
	ZeroMemory(buffer, 255);

	char initialPath[255];
	ZeroMemory(initialPath, 255);
	_fullpath(initialPath, directory, 255);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Setting::Get()->GetWindowHandle();
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = buffer;
	ofn.lpstrInitialDir = initialPath;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileNameA(&ofn) == TRUE) {

		std::string path = std::string(buffer);
		std::function<void(std::string)> func =
			std::forward<std::function<void(std::string)>>(function);

		if (!function)
			func(path);
	}
}

const std::string FileSystem::GetFileNameFromPath(const std::string & path)
{
	//../_Assets/Texture/Tree.png --------------> Tree.png
	auto lastIndex = path.find_last_of("\\/");
	auto fileName = path.substr(lastIndex + 1, path.length());

	return fileName;
}

const std::string FileSystem::GetDirectoryFromPath(const std::string& path)
{
	size_t lastIndex = path.find_last_of("\\/");
	std::string directory = path.substr(0, lastIndex + 1);

	return directory;
}

const std::string FileSystem::GetPathWithoutExtension(const std::string& path)
{
	std::string directory = GetDirectoryFromPath(path);
	std::string intact_name = GetIntactFileNameFromPath(path);

	return directory + intact_name;
}

const std::string FileSystem::GetIntactFileNameFromPath(const std::string & path)
{
	//../_Assets/Texture/Tree.png --------------> Tree
	auto fileName = GetFileNameFromPath(path);
	auto lastIndex = fileName.find_last_of('.');
	auto intactFileName = fileName.substr(0, lastIndex);

	return intactFileName;
}

const std::string FileSystem::GetExtensionFromPath(const std::string & path)
{
	auto lastIndex = path.find_last_of('.');

	if (lastIndex != std::string::npos)
		return path.substr(lastIndex, path.length());

	return std::string();
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

const std::string FileSystem::ToUpper(const std::string & path)
{
	std::string upper;
	for (const auto& character : path)
		upper += toupper(character);
	return upper;
}

const std::string FileSystem::GetParentDirectory(const std::string & path)
{
	auto found = path.find_last_of("\\/");
	auto result = path;

	if (found == std::string::npos)
		return result;

	if (found == path.length() - 1)
	{
		result = result.substr(0, found - 1);
		return GetParentDirectory(result);
	}

	return result.substr(0, found) + "/";
}

const std::string FileSystem::GetRelativeFilePath(const std::string & path)
{
	std::filesystem::path p = std::filesystem::absolute(path);
	std::filesystem::path r = std::filesystem::absolute(GetWorkingDirectory());

	if (p.root_path() != r.root_path())
		return p.generic_string();

	std::filesystem::path result;

	std::filesystem::path::const_iterator iter_p = p.begin();
	std::filesystem::path::const_iterator iter_r = r.begin();

	while (*iter_p == *iter_r && iter_p != p.end() && iter_r != r.end()) {
		iter_p++;
		iter_r++;
	}

	if (iter_r != r.end())
	{
		iter_r++;
		while (iter_r != r.end())
		{
			result /= "..";
			iter_r++;
		}
	}
	
	while (iter_p != p.end())
	{
		result /= *iter_p;
		iter_p++;
	}

	return result.generic_string();
}

const std::string FileSystem::GetWorkingDirectory()
{
	return std::filesystem::current_path().generic_string() + "/";
}

const bool FileSystem::IsDirectory(const std::string & path)

{	bool bResult = false;
	try {
		bResult = std::filesystem::is_directory(path);
	}
	catch (std::filesystem::filesystem_error error){
		MessageBoxA(nullptr, error.what(), "Error!!", MB_OK);
	}
	return bResult;
}

const bool FileSystem::IsSupportImageFile(const std::string & path)
{
	auto fileExtension = GetExtensionFromPath(path);
	auto supportFormats = GetSupportImageFormats();

	for (const auto& format : supportFormats)
	{
		if (fileExtension == format || fileExtension == ToUpper(format))
			return true;
	}
	return false;
}

const bool FileSystem::IsFolder(const std::string& path)
{
	auto slash = path.find_last_of("/");
	auto comma = path.find_last_of(".");

	if (path.find_last_of("/") > path.find_last_of("."))
		return true;

	return false;
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


const std::vector<std::string> FileSystem::GetFilesInDirectory(const std::string & path)
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

const std::vector<std::string> FileSystem::GetAllFilesInDirectory(const std::string& path)
{
	std::vector<std::string> files;

	std::filesystem::directory_iterator endIter;
	for (std::filesystem::directory_iterator iter(path); iter != endIter; iter++)
	{
		if (!std::filesystem::is_regular_file(iter->status()))
		{
			auto tmps = GetAllFilesInDirectory(iter->path().generic_string());
			for (auto tmp : tmps)
				files.emplace_back(tmp);
			continue;
		}
		files.emplace_back(iter->path().generic_string());
	}

	return files;
}

const std::vector<std::string> FileSystem::GetFoldersInDirectory(const std::string & path)
{
	std::vector<std::string> files;

	std::filesystem::directory_iterator endIter;
	for (std::filesystem::directory_iterator iter(path); iter != endIter; iter++)
	{
		if (!std::filesystem::is_directory(iter->status()))
			continue;
		files.emplace_back(iter->path().generic_string());
	}

	return files;
}

const std::vector<std::string> FileSystem::GetPartOfName(const std::string& path)
{
	std::vector<std::string> names;
	std::string pureName = GetIntactFileNameFromPath(path);

	size_t lastIndex = pureName.find_last_of("_");
	std::string name = pureName.substr(0, lastIndex);
	std::string arg = pureName.substr(lastIndex + 1, pureName.length());

	names.emplace_back(name); names.emplace_back(arg);

	return names;
}

const std::wstring FileSystem::ToWstring(const std::string& input)
{
	wchar_t buffer[1024];

	DWORD minSize;
	minSize = MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, NULL, 0);

	if (1024 < minSize)
		return L"Size over";

	// Convert string from multi-byte to Unicode.
	MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, buffer, minSize);

	return std::wstring(buffer);
}

const bool FileSystem::MakeDirectory(const std::string& path)
{
	bool bResult = false;
	try {
		bResult = std::filesystem::is_directory(path);
	}
	catch (std::filesystem::filesystem_error error) {
		MessageBoxA(nullptr, error.what(), "Error!!", MB_OK);
	}

	if (!bResult)
	{
		try {
			bResult = std::filesystem::create_directory(path);
		}
		catch (std::filesystem::filesystem_error error) {
			MessageBoxA(nullptr, error.what(), "Error!!", MB_OK);
		}
	}

	return bResult;
}

