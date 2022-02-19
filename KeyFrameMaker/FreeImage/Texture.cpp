#include "stdafx.h"
#include "Texture.h"
#include "ImageImporter.h"
#include <iostream>

Texture::Texture(Context* context)
	: bpp(0), bpc(8), width(0), height(0), channel(0)
	, isGrayScaled(false), isTransparent(false), isMipChained(false)
{
	this->context = context;
}

Texture::~Texture()
{
	Clear();
}

void Texture::SaveToFile(const std::string& path)
{
	Serialize(path);
}

void Texture::LoadFromFile(const std::string& path)
{
	std::string texturePath = FileSystem::GetRelativeFilePath(path);
	if (!FileSystem::IsExist(texturePath) || !FileSystem::IsSupportImageFile(texturePath))
	{
		LOG_ERROR("Path \"%s\" is invalid", texturePath.c_str());
		return;
	}

	ClearMipChain();

	bool isLoaded = LoadByImporter(texturePath);

	if (!isLoaded)
	{
		LOG_ERROR("Failed to load \"%s\"", texturePath.c_str());
		return;
	}

	if (width == 0 || height == 0 || channel == 0 || mipChain.empty() || mipChain.front().empty())
	{
		LOG_ERROR("Invalid parameter");
		return;
	}

}

const bool Texture::LoadByImporter(const std::string& path)
{
	ResourceManager* resourceManager = context->GetSubsystem<ResourceManager>();
	if (!resourceManager->GetImageImporter()->Load(path, this))
	{
		LOG_ERROR("Failed Loading Texture");
		return false;
	}
	this->resourcePath = path;
	this->resourceName = FileSystem::GetIntactFileNameFromPath(path);

	return true;
}

void Texture::LoadMipChain()
{
	FileStream r;
	if (!r.Open(resourcePath, StreamMode::Read)) return;

	mipChain.resize(r.ReadUInt());
	for (auto& mip : mipChain)
		r.Read(mip);
}

void Texture::ClearMipChain()
{
	for (auto& mip : mipChain)
	{
		mip.clear();
		mip.shrink_to_fit();
	}

	mipChain.clear();
	mipChain.shrink_to_fit();
}

void Texture::Clear()
{
	bpp = 0;
	bpc = 8;
	width = 0;
	height = 0;
	channel = 0;
	isGrayScaled = false;
	isTransparent = false;
	isMipChained = true;

	ClearMipChain();
}

const bool Texture::Serialize(const std::string& path)
{
	LoadMipChain();

	FileStream w;
	if (!w.Open(path, StreamMode::Write)) return false;

	w.Write(static_cast<_int32>(mipChain.size()));
	for (auto& mip : mipChain)
		w.Write(mip);

	w.Write(bpp);
	w.Write(bpc);
	w.Write(width);
	w.Write(height);
	w.Write(channel);
	w.Write(isGrayScaled);
	w.Write(isTransparent);
	w.Write(isMipChained);
	w.Write(resourceName);
	w.Write(resourcePath);

	ClearMipChain();

	return true;
}

const bool Texture::Deserialize(const std::string& path)
{
	FileStream r;
	if (!r.Open(path, StreamMode::Read)) return false;

	ClearMipChain();

	mipChain.resize(r.ReadUInt());
	for (auto& mip : mipChain)
		r.Read(mip);

	r.Read(bpp);
	r.Read(bpc);
	r.Read(width);
	r.Read(height);
	r.Read(channel);
	r.Read(isGrayScaled);
	r.Read(isTransparent);
	r.Read(isMipChained);
	r.Read(resourceName);
	r.Read(resourcePath);

	return true;
}