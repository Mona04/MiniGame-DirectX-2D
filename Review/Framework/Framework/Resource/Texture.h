#pragma once
#include "IResource.h"

enum class TextureType : uint
{
	Unknown,
	Albedo,
	Normal,
	Emissive
};

class Texture final : public IResource
{
private:
	friend class ResourceManager;
	friend class ImageImporter;

public:
	ID3D11ShaderResourceView* GetShaderResourceView() const { return srv; }

private:
	Texture(class Context* context);
	~Texture();

	void SaveToFile(const std::string & path) override;
	void LoadFromFile(const std::string & path) override;
	void LoadFromFileForThread(const std::string& path);

	const bool LoadByImporter(const std::string& path);

public:
	const DXGI_FORMAT& GetFormat() const { return format; }
	void SetFormat(const DXGI_FORMAT& value) { format = value; }

	const uint& GetBPP() { return bpp; }
	void SetBPP(const uint& value) { bpp = value; }
	
	const uint& GetBPC() { return bpc; }
	void SetBPC(const uint& value) { bpc = value; }
	
	const uint& GetWidth() const { return width; }
	void SetWidth(const uint& value) { width = value; }
	
	const uint& GetHeight() const { return height; }
	void SetHeight(const uint& value) { height = value; }
	
	const uint& GetChannel() { return channel; }
	void SetChannel(const uint& value) { channel = value; }
	
	const bool& IsGrayScaled() { return isGrayScaled; }
	void SetGrayScaled(const bool& value) { isGrayScaled = value; }

	const bool& IsTransparent() { return isTransparent; }
	void SetTransparent(const bool& value) { isTransparent = value; }

	const bool& IsMipChained() { return isMipChained; }
	void SetMipChained(const bool& value) { isMipChained = value; }
	
	std::vector<std::vector<std::byte>>& GetMipChain() { return mipChain; }
	void SetTextureBytes(const std::vector<std::vector<std::byte>>& texture_bytes) { this->mipChain = texture_bytes; }
	std::vector<std::byte>* AddMipData() { return &mipChain.emplace_back(std::vector<std::byte>()); }

	void LoadMipChain();
	void ClearMipChain();

	const bool CreateShaderResourseView   // importer 에서 만들어줌
	(
		const uint& width, const uint& height, const uint& channel,
		const DXGI_FORMAT& format, const std::vector<std::vector<std::byte>>& mipChain
	);
	const bool CreateShaderResourseView   // device context 에서 만들어줌
	(
		const uint& width, const uint& height, const uint& channel,
		const DXGI_FORMAT& format, const std::vector<std::byte>& mip, const bool& isMipChained = false
	);

	void Clear();
	void BindPipeline(const ShaderStage& stage, const uint& slot);

private:
	const bool Serialize(const std::string& path);
	const bool Deserialize(const std::string& path);

private:
	class Graphics* graphics;
	ID3D11ShaderResourceView* srv;
	DXGI_FORMAT format;
	uint bpp; //byte per pixel
	uint bpc; //byte per channel
	uint width; 
	uint height;
	uint channel;
	bool isGrayScaled;
	bool isTransparent;
	bool isMipChained;
	std::vector<std::vector<std::byte>> mipChain;
};