#include "pch.h"
#include "../FreeImage/FreeImage.h"
#include "../FreeImage/Utilities.h"

D3DXVECTOR2 GetResolution(const std::string& path)
{
	if (!FileSystem::IsExist(path))
	{
		std::string result = "Path " + path + " is invalid";
		MessageBoxA(nullptr, result.c_str(), nullptr, MB_OK);
		return D3DXVECTOR2(0, 0);
	}

	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);
	format = (format == FIF_UNKNOWN) ? FreeImage_GetFIFFromFilename(path.c_str()) : format; // 모르는 형식은 파일 이름에서 가져옴

	FIBITMAP* bitmap = FreeImage_Load(format, path.c_str()); // 1 Load
	bitmap = FreeImage_ConvertTo32Bits(bitmap);
	if (!bitmap)
	{
		std::string result = "Failed to Create Bitmap";
		MessageBoxA(nullptr, result.c_str(), nullptr, MB_OK);
		return D3DXVECTOR2(0, 0);
	}

	//이미지 속성 추정
	const uint imageWidth = FreeImage_GetWidth(bitmap);
	const uint imageHeight = FreeImage_GetHeight(bitmap);

	FreeImage_Unload(bitmap);

	return D3DXVECTOR2(imageWidth, imageHeight);
}

void SaveToFile(const std::string& path, const std::string& imgPath, const bool& isBlock)
{
	D3DXVECTOR2 resolution = GetResolution(imgPath);

	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(3u);
		stream.Write(static_cast<uint>(ComponentType::Transform));
		{
			if(isBlock) stream.Write(D3DXVECTOR3(0, 0, 0));
			else stream.Write(D3DXVECTOR3(0, resolution.y / 2.0f - 20.0f, 0));  // 기본 블럭이 있으니까 15 빼는데 넉넉하게 18 뱀 은 그냥 블럭에서 하면 안됨
			stream.Write(D3DXQUATERNION(0, 0, 0, 0));
			if (isBlock) stream.Write(D3DXVECTOR3(30, 30, 0));
			else stream.Write(D3DXVECTOR3(+resolution.x, +resolution.y, 0.0f));
		}
		stream.Write(static_cast<uint>(ComponentType::Renderable));
		{		
			stream.Write("QUAD.mesh");
			stream.Write("QUAD");
			stream.Write("Material/Block_Glass.material");
			stream.Write("Material/Block_Glass");
			stream.Write(1u);
			stream.Write(static_cast<uint>(TextureType::Albedo));
			stream.Write(FileSystem::GetDirectoryLeft(imgPath, "../../_Assets/Texture/"));
			stream.Write(FileSystem::GetIntactFileNameFromPath(imgPath));
		}
		stream.Write(static_cast<uint>(ComponentType::RigidBody));
		{
			stream.Write(static_cast<uint>(RigidBodyType::Effect));
			stream.Write(10.0f);
			stream.Write(1.0f);
			stream.Write(D3DXVECTOR3(+15, +15, 0));
			stream.Write(D3DXVECTOR3(-15, -15, 0));
		}
	}
	stream.Close();
}

std::string GetString(const int& n, const int& digit)
{
	int m = 1;
	for (int i = 0; i < digit; i++)
		m *= 10;
	return std::to_string((n / m) % 10);
}

std::string GetCodeString(const int& code)
{
	return GetString(code, 4) + GetString(code, 3) + GetString(code, 2) + GetString(code, 1) + GetString(code, 0);
}

void main()
{
	std::vector<std::string> mapNames{ "Grassy", "CokeTown", "Halloween","Perion", "MidForest" , "ShineWood", "Orbis",
		"Galaxy", "ToyCastle_Low", "KerningCity", "SunsetCity", "DragonValley", "Ereb", "ForkForest", "TimeRoad", "ToyCastle_Lowest"};
	std::vector<std::string> folders = { "Tile", "Nature" };
	
	int region = 1;	
	for (const auto& mapName : mapNames)
	{
		int type = 0;

		for (const auto& folder : folders)
		{
			int code = region * 1000 + type * 100;
			auto files = FileSystem::GetFilesInDirectory("../../_Assets/Texture/Blocks/" + mapName + "/" + folder + "/");
			for (auto& file : files)
			{
				SaveToFile("../../_Assets/Scene/Blocks/" + GetCodeString(code++) + ".actor", file, type == 0);
				std::cout << file << " is " << code - 1 << std::endl;
			}
			type++;
		}
		region++;
	}
}


