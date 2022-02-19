#include "stdafx.h"
#include "FileSystem.h"
#include <filesystem>
#include <ShlObj.h>

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

void FileSystem::OpenFilePathDialog(std::function<void(std::string)>&& function, const char* filter, const char* directory)
{
	ITEMIDLIST* pidlBrowse;
	char buffer[255];
	WCHAR displayName[255] = L"## Unicode Disable ##";
	WCHAR title[255] = L"Path Search";

	BROWSEINFO BrInfo;

	BrInfo.hwndOwner = Setting::Get()->GetHWND();
	BrInfo.pidlRoot = NULL;

	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = displayName;
	BrInfo.lpszTitle = title;
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	// 다이얼로그 띄우기
	pidlBrowse = SHBrowseForFolder(&BrInfo);

	if (pidlBrowse != NULL)
	{
		if (TRUE == ::SHGetPathFromIDListA(pidlBrowse, buffer))
		{
			std::string path = GetSlashPath(std::string(buffer));
			std::function<void(std::string)> func =
				std::forward<std::function<void(std::string)>>(function);

			if (!function)
				func(path);
		}
	}
}

void FileSystem::OpenFileDialog(std::function<void(std::string)>&& function, const char* filter, const char* directory)
{
	char buffer[255];
	ZeroMemory(buffer, 255);

	char initialPath[255];
	ZeroMemory(initialPath, 255);
	_fullpath(initialPath, directory, 255);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Setting::Get()->GetHWND();
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

void FileSystem::CreateFolder(const std::string& path)
{
	if (FALSE == CreateDirectoryA(path.c_str(), NULL))
	{
	}
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

const bool FileSystem::IsSupportImageFile(const std::string& path)
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

const std::string FileSystem::ToUpper(const std::string& path)
{
	std::string upper;
	for (const auto& character : path)
		upper += toupper(character);
	return upper;
}

const std::wstring FileSystem::ToWString(const std::string& path)
{
	wchar_t buffer[1024];

	DWORD minSize;
	minSize = MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, NULL, 0);

	if (1024 < minSize)
		return L"Size over";

	// Convert string from multi-byte to Unicode.
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, buffer, minSize);

	return std::wstring(buffer);
}

const std::string FileSystem::GetSlashPath(const std::string& path)
{
	char result[1024];
	std::string from = "\\";
	std::string to = "//";

	int i = 0;
	for (auto ch : path)
	{
		if (ch == '\\')
		{
			result[i++] = '/';
			result[i++] = '/';
		}
		else result[i++] = ch;
	}

	result[i++] = '\0';

	return std::string(result);
}

const std::string FileSystem::FindReplace(const std::string& path, const std::string& from, const std::string& to)
{
	std::string result = path;

	size_t offset = 0;
	while ((offset = path.find(from, offset)) != std::string::npos)
	{
		result.replace(offset, from.length(), to);
		offset += to.length();
	}
	return result;
}

const std::string FileSystem::GetWorkingDirectory()
{
	return std::filesystem::current_path().generic_string() + "/";
}

const std::string FileSystem::GetExtensionFromPath(const std::string& path)
{
	auto lastIndex = path.find_last_of('.');

	if (lastIndex != std::string::npos)
		return path.substr(lastIndex, path.length());

	return std::string();
}

const std::string FileSystem::GetDirectoryFromPath(const std::string& path)
{
	size_t lastIndex = path.find_last_of("\\/");
	std::string directory = path.substr(0, lastIndex + 1);

	return directory;
}

const std::string FileSystem::GetDirectoryFromPath(const std::string& path, const int& index)
{
	std::string cur = path;
	size_t lastIndex;
	size_t secondLastIndex;
	
	for (int i = 0; i < index; i++)
	{
		lastIndex = cur.find_last_of("\\/");
		secondLastIndex = cur.substr(0, lastIndex).find_last_of("\\/");
		cur = path.substr(0, lastIndex);
	}

	cur = cur.substr(secondLastIndex + 1, lastIndex - secondLastIndex - 1);

	return cur;
}

const std::string FileSystem::GetDirectoryEndNameFromPath(const std::string& path)
{
	size_t lastIndex = path.find_last_of("\\/");
	size_t secondLastIndex = path.substr(0, lastIndex).find_last_of("\\/");
	std::string directory = path.substr(secondLastIndex + 1, lastIndex - secondLastIndex - 1);

	return directory;
}

const std::string FileSystem::GetFileNameFromPath(const std::string& path)
{
	auto lastIndex = path.find_last_of("\\/");
	auto fileName = path.substr(lastIndex + 1, path.length());

	return fileName;
}

const std::string FileSystem::GetPureNameFromPath(const std::string& path)
{
	auto lastIndex = path.find_last_of("\\/");
	auto lastCommaIndex = path.find_last_of(".");
	auto fileName = path.substr(lastIndex + 1, lastCommaIndex - lastIndex - 1);

	return fileName;
}

const std::string FileSystem::GetIntactFileNameFromPath(const std::string& path)
{
	auto fileName = GetFileNameFromPath(path);
	auto lastIndex = fileName.find_last_of('.');
	auto intactFileName = fileName.substr(0, lastIndex);

	return intactFileName;
}

const std::string FileSystem::GetRelativeFilePath(const std::string& path)
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
