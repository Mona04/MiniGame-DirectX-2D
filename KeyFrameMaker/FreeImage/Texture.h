#pragma once

class Texture final
{
private:
	friend class ResourceManager;
	friend class ImageImporter;
	friend class ImageEditor;

private:
	Texture(class Context* context);
	~Texture();

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

	const bool LoadByImporter(const std::string& path);

public:
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

	const uint& GetPitch() { return pitch; }
	void SetPitch(const uint& value) { pitch = value; }

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

	void Clear();

	const std::string& GetResourcePath() { return resourcePath; }
	const std::string& GetResourceName() { return resourceName; }

private:
	const bool Serialize(const std::string& path);
	const bool Deserialize(const std::string& path);

protected:
	class Context* context;
	std::string resourcePath;
	std::string resourceName;

	uint bpp; //byte per pixel
	uint bpc; //byte per channel
	uint width;
	uint height;
	uint channel;
	uint pitch;
	bool isGrayScaled;
	bool isTransparent;
	bool isMipChained;

	std::vector<std::vector<std::byte>> mipChain;
};