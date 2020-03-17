#include "Framework.h"
#include "Texture.h"
#include "Importer/ImageImporter.h"

Texture::Texture(Context * context)
	: IResource(context)
	, srv(nullptr)
	, format(DXGI_FORMAT_R8G8B8A8_UNORM)
	, bpp(0), bpc(8), width(0), height(0), channel(0)
	, isGrayScaled(false), isTransparent(false), isMipChained(false)
{
	graphics = context->GetSubsystem<Graphics>();
}

Texture::~Texture()
{
	Clear();
}

void Texture::SaveToFile(const std::string & path)
{
	Serialize(path);
}

void Texture::LoadFromFile(const std::string & path)
{
	this->LoadFromFileForThread(path);
	//context->GetSubsystem<Thread>()->AddTask([this, path]() { this->LoadFromFileForThread(path); });
}

void Texture::LoadFromFileForThread(const std::string& path)
{
	std::string texturePath = FileSystem::GetRelativeFilePath(path);
	if (!FileSystem::IsExist(texturePath))
	{
		LOG_ERROR("Path \"%s\" is invalid", texturePath.c_str());
		return;
	}

	ClearMipChain();

	bool isLoaded = false;
	if (FileSystem::GetExtensionFromPath(texturePath) == ".texture")
		isLoaded = Deserialize(texturePath);
	else if (FileSystem::IsSupportImageFile(texturePath))
		isLoaded = LoadByImporter(texturePath);

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

	isMipChained ?
		CreateShaderResourseView(width, height, channel, format, mipChain) :
		CreateShaderResourseView(width, height, channel, format, mipChain.front(), isMipChained);

	ClearMipChain();
}

const bool Texture::LoadByImporter(const std::string& path)
{
	if (!resourceManager->GetImageImporter()->Load(path, this))
	{
		LOG_ERROR("Failed Loading Texture");
		return false;
	}

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

const bool Texture::CreateShaderResourseView(const uint& width, const uint& height, const uint& channel, const DXGI_FORMAT& format, const std::vector<std::vector<std::byte>>& mipChain)
{
	if (width == 0 || height == 0 || mipChain.empty())
	{
		LOG_ERROR("Invalid Parameter");
		return false;
	}

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = mipChain.size();
	texDesc.ArraySize = 1;
	texDesc.Format = format;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_IMMUTABLE;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	std::vector<D3D11_SUBRESOURCE_DATA> subResourceData;
	uint mipWidth = width;
	uint mipHeight = height;

	for (uint i = 0; i < mipChain.size(); i++)
	{
		if (mipChain[i].empty())
		{
			LOG_ERROR("Mip levels %d has invalid data", i);
			continue;
		}

		D3D11_SUBRESOURCE_DATA& subData = subResourceData.emplace_back(D3D11_SUBRESOURCE_DATA{});
		subData.pSysMem = mipChain[i].data();
		subData.SysMemPitch = mipWidth * channel * (bpc / 8); // The distance (in bytes) from the beginning of one line of a texture to the next line.
		subData.SysMemSlicePitch = 0;

		mipWidth = Math::Max<uint>(mipWidth / 2, 1);
		mipHeight = Math::Max<uint>(mipHeight / 2, 1);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	ID3D11Texture2D* texture = nullptr;
	bool result = SUCCEEDED(graphics->GetDevice()->CreateTexture2D(&texDesc, subResourceData.data(), &texture));
	if(!result)
	{
		LOG_ERROR("Failed To Create ID3D11TEXTURE2D");
		return false;
	}

	result = SUCCEEDED(graphics->GetDevice()->CreateShaderResourceView(texture, &srvDesc, &srv));
	if(!result)
	{
		LOG_ERROR("Failed To Create ID3D11TEXTURE2D");
	}

	SAFE_RELEASE(texture);

	return result;
}

const bool Texture::CreateShaderResourseView(const uint& width, const uint& height, const uint& channel, const DXGI_FORMAT& format, const std::vector<std::byte>& mip, const bool& isMipChained)
{
	if (width == 0 || height == 0 || mip.empty())
	{
		LOG_ERROR("Invalid Parameter");
		return false;
	}

	if (isMipChained)
	{
		if (width < 4 || height < 4)
		{
			LOG_ERROR("MipChain won't be generated as dimension %dx%d is too small", width, height);
			return false;
		}
	}

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = format;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_IMMUTABLE;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	if (isMipChained)
	{
		texDesc.MipLevels = 7;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		texDesc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = mip.data();
	subResourceData.SysMemPitch = width * channel * (bpc / 8);
	subResourceData.SysMemSlicePitch = 0;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	ID3D11Texture2D* texture = nullptr;

	bool result = SUCCEEDED(graphics->GetDevice()->CreateTexture2D(&texDesc, &subResourceData, &texture));
	if (!result)
	{
		LOG_ERROR("Failed To Create ID3D11TEXTURE2D");
		return false;
	}

	result = SUCCEEDED(graphics->GetDevice()->CreateShaderResourceView(texture, &srvDesc, &srv));
	if (result)
	{
		if (isMipChained)
		{
			graphics->GetDeviceContext()->GenerateMips(srv);
		}
	}
	else
	{
		LOG_ERROR("Failed To Create ID3D11ShaderResourceView");
	}

	SAFE_RELEASE(texture);

	return result;
}

void Texture::Clear()
{
	SAFE_RELEASE(srv);
	format = DXGI_FORMAT_R8G8B8A8_UNORM;
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

void Texture::BindPipeline(const ShaderStage & stage, const uint & slot)
{
	switch (stage)
	{
	case ShaderStage::VS: graphics->GetDeviceContext()->VSSetShaderResources(slot, 1, &srv); break;
	case ShaderStage::PS: graphics->GetDeviceContext()->PSSetShaderResources(slot, 1, &srv); break;
	}
}

const bool Texture::Serialize(const std::string& path)
{
	LoadMipChain();

	FileStream w;
	if (!w.Open(path, StreamMode::Write)) return false;
	
	w.Write(mipChain.size());
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


/*
void Texture::Create(const std::string & path)
{
	this->resourcePath = path;
	HRESULT hr = D3DX11CreateShaderResourceViewFromFileA
	(
		graphics->GetDevice(),
		path.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* srcTexture = nullptr;
	srv->GetResource(reinterpret_cast<ID3D11Resource**>(&srcTexture));

	D3D11_TEXTURE2D_DESC desc;
	srcTexture->GetDesc(&desc);

	width = desc.Width;
	height = desc.Height;
	format = desc.Format;
}

void Texture::Create(const uint & width, const uint & height, const DXGI_FORMAT & format)
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Texture2D* texture = nullptr;
	HRESULT hr = graphics->GetDevice()->CreateTexture2D
	(
		&desc,
		nullptr,
		&texture
	);
	assert(SUCCEEDED(hr));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = graphics->GetDevice()->CreateShaderResourceView
	(
		texture,
		&srvDesc,
		&srv
	);
	assert(SUCCEEDED(hr));
}
*/