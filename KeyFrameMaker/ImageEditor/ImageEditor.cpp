#include "stdafx.h"
#include "ImageEditor.h"
#include "Util/FileSystem.h"
#include "FreeImage/ImageImporter.h"
#include "FreeImage/Texture.h"
#include "Core/Subsystem/Timer.h"

#include "FreeImage/FreeImage.h"
#include "FreeImage/Utilities.h"


ImageEditor::ImageEditor(Context* context)
	: context(context)
{
	actTypeFolderList = { "die\\", "hit\\", "jump\\", "walk\\", "run\\", "stand\\", "attack1\\", "attack2\\"};
	Clear();
}

ImageEditor::~ImageEditor()
{
}

void ImageEditor::Update()
{
	static float deltaTime = 0;
	deltaTime += context->GetSubsystem<Timer>()->GetDeltaTimeMs();
	if (deltaTime >= delay && delay >= 100)
	{
		deltaTime = 0;
		InvalidateRect(Setting::Get()->GetHWND(), nullptr, false);
		curFrameIndex += 1;
		if(curFrameIndex >= keyframes.size())
			curFrameIndex = 0;
	}
}

void ImageEditor::Clear()
{
	for (auto texture : textures)
		SAFE_DELETE(texture);
	textures.clear();
	textures.shrink_to_fit();
	delays.clear();
	delays.shrink_to_fit();
	
	texturesName = "";
	texturesPath = "";
	split_height = 0;
	split_width = 0;
	split_channel = 0;
	split_bpp = 0;
	split_bpc = 0;
	split_pitch = 0;
	repeatType = RepeatType::Loop;
	delay = 100;
}

void ImageEditor::LoadImages(const std::string& paths)
{
	std::string global_path = paths + "..\\";
	
	for (auto& actTypeFolder : actTypeFolderList)
	{
		Clear();

		if (!FileSystem::IsExist(global_path + actTypeFolder)) continue;
		std::vector<std::string> imagePaths = Sort(FileSystem::GetFilesInDirectory(global_path + actTypeFolder));

		for (auto path : imagePaths)
		{
			if (FileSystem::GetExtensionFromPath(path) == ".txt")
			{
				MakeInfo(path);
				continue;
			}
			else if (!FileSystem::IsSupportImageFile(path))
				continue;

			Texture* texture = new Texture(context);
			texture->LoadFromFile(path);
			textures.emplace_back(texture);

			split_height = texture->GetHeight() > split_height ? texture->GetHeight() : split_height;
			split_width = texture->GetWidth() > split_width ? texture->GetWidth() : split_width;

			delays.emplace_back(std::stoi(FileSystem::GetFileNameFromPath(path)));
		}

		if (textures.size() > 0)
		{
			split_channel = textures[0]->GetChannel();
			split_bpp = textures[0]->GetBPP();
			split_bpc = textures[0]->GetBPC();
			split_pitch = textures[0]->GetPitch();
		}

		if (FileSystem::GetExtensionFromPath(imagePaths[0]) == ".txt")
			CombineImages(imagePaths[1]);
		else CombineImages(imagePaths[0]);
	}
}

void ImageEditor::CombineImages(const std::string& path)
{
	std::string savePath;
	uint totalNum = textures.size();
	uint split_size = split_height * split_width * split_channel * (split_bpc / 8);
	
	if (imageFileSavePath == "N\A")
	{
		savePath = (FileSystem::GetDirectoryFromPath(path) + "../" + FileSystem::GetDirectoryEndNameFromPath(path) + ".png");
	}
	else
	{
		FileSystem::CreateFolder(imageFileSavePath + FileSystem::GetDirectoryFromPath(path, 4));
		savePath = (imageFileSavePath + FileSystem::GetDirectoryFromPath(path, 4) + "//" + FileSystem::GetDirectoryEndNameFromPath(path) + ".png");
	}

	std::vector<std::byte> data;
	data.reserve(split_size * totalNum);
	data.resize(split_size * totalNum);

	for (int i = 0; i < totalNum; i++)
		memcpy(&(data)[split_size * (totalNum - 1 - i)], &textures[i]->GetMipChain()[0][0], split_size);

	FIBITMAP* bitmap = FreeImage_ConvertFromRawBits((BYTE*)data.data(), split_width, split_height * totalNum, split_pitch, split_bpp, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
	bool result = FreeImage_Save(FIF_PNG, bitmap, savePath.c_str());
	
	if (!result)
		LOG_ERROR("Save %s Failed.", path.c_str());
	
	FreeImage_Unload(bitmap);
	Clear();
}

void ImageEditor::MakeInfo(const std::string& path)
{
	std::string savePath;

	if (infoFileSavePath == "N\A")
	{
		savePath = (FileSystem::GetDirectoryFromPath(path) + "../" + FileSystem::GetDirectoryEndNameFromPath(path) + "_info.txt");
	}
	else
	{
		FileSystem::CreateFolder(infoFileSavePath + FileSystem::GetDirectoryFromPath(path, 4));
		savePath = (infoFileSavePath + FileSystem::GetDirectoryFromPath(path, 4) + "//" + FileSystem::GetDirectoryEndNameFromPath(path) + "_info.txt");
	}

	std::ifstream input;
	{
		input.open(path);
		input >> delay;
		delays.emplace_back(delay);
	}
	input.close();

	FileStream w;
	w.Open(savePath.c_str(), StreamMode::Write);
	{
		texturesName = FileSystem::GetDirectoryFromPath(path, 4) + " " + FileSystem::GetDirectoryEndNameFromPath(path);
		texturesPath = "Characters\\" + FileSystem::GetDirectoryFromPath(path, 4) + "\\" + FileSystem::GetDirectoryEndNameFromPath(path) + ".png";
		w.Write(texturesName);
		w.Write(texturesPath);
		w.Write(static_cast<uint>(repeatType));
		w.Write(static_cast<int>(textures.size()));

		for (int i = 0 ; i < textures.size(); i++)
		{
			w.Write(D3DXVECTOR2(0, split_height*i));
			w.Write(D3DXVECTOR2(split_width, split_height));
			w.Write(static_cast<float>(delays[i+1] - delays[i]));
		}

	}
	w.Close();
}

void ImageEditor::LoadFrames(const std::string& path)
{
	ClearFrames();

	std::wstring wPath = FileSystem::ToWString(path);

	Gdiplus::GdiplusStartupInput gdiInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiInput, NULL);

	image = Gdiplus::Image::FromFile(wPath.c_str());

	std::string infoPath = FileSystem::GetDirectoryFromPath(path) + FileSystem::GetPureNameFromPath(path) + "_info.txt";
	FileStream r;
	r.Open(infoPath, StreamMode::Read);
	{
		uint repeat = 0;

		r.Read(resourceName);
		r.Read(resourcePath);
		r.Read(repeat);

		repeatType = static_cast<RepeatType>(repeat);

		uint count = r.ReadUInt();
		for (uint i = 0; i < count; i++)
		{
			D3DXVECTOR2 offset;
			D3DXVECTOR2 size;
			float time;

			r.Read(offset);
			r.Read(size);
			r.Read(time);

			AddKeyframe(offset, size, time);
		}
	}
	r.Close();
}

void ImageEditor::ShowFrames(HDC hdc)
{
	if (keyframes.empty())
		return;

	Gdiplus::Graphics g(hdc);
	Keyframe curFrame = keyframes[curFrameIndex];
	g.DrawImage(image, 10, 100, static_cast<int>(curFrame.offset.x), static_cast<int>(curFrame.offset.y),
		static_cast<int>(curFrame.size.x), static_cast<int>(curFrame.size.y), Gdiplus::Unit::UnitPixel);
}

void ImageEditor::ClearFrames()
{
	keyframes.clear();
	keyframes.shrink_to_fit();

	SAFE_DELETE(image);
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

std::vector<std::string> ImageEditor::Sort(const std::vector<std::string>& paths)
{
	std::vector<std::string> result;

	for (int n = 0; n < 10; n++)
	{
		for (auto& path : paths)
		{
			std::string fileName = FileSystem::GetFileNameFromPath(path);
			if (fileName.size() == n)
				result.emplace_back(path);
		}
	}

	return result;
}
