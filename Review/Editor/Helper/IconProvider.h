#pragma once

enum class IconType : uint
{
	Custom,
	Thumbnail_Folder,
	Thumbnail_File,
	Button_Play,
	Button_Stop,
	Button_Pause,
	Button_Info,
	Button_Warning,
	Button_Error
};

struct Thumbnail
{
	Thumbnail()
		: type(IconType::Custom)
		, texture(nullptr)
		, path("")
	{}

	Thumbnail(const IconType& type, class Texture* texture, const std::string& path)
		: type(type), texture(texture), path(path)
	{}

	IconType type;
	Texture* texture;
	std::string path;
};

struct Item
{
	Item(const std::string& path, const Thumbnail& thumbnail)
		: path(path)
		, thumbnail(thumbnail)
	{
		label = FileSystem::GetFileNameFromPath(path);
	}

	Thumbnail thumbnail;
	std::string path;
	std::string label;
};


class IconProvider final
{
public:
	static IconProvider* Get()
	{
		static IconProvider instance;
		return &instance;
	}

	void Initialize(class Context* context);

	Thumbnail* Load(const std::string& path, const IconType& types = IconType::Custom);

	auto GetShaderResourceFromType(const IconType& type)->ID3D11ShaderResourceView*;
	auto GetShaderResourceFromPath(const std::string& path)->ID3D11ShaderResourceView*;

	auto ImageButton(const Thumbnail& thumbnail, const ImVec2& size)->const bool;
	auto ImageButton(const IconType& type, const ImVec2& size)->const bool;
	auto ImageButton(const std::string& path, const ImVec2& size)->const bool;

private:
	IconProvider() : context(nullptr), resourceManager(nullptr) {};
	~IconProvider() = default;

	IconProvider(const IconProvider&) = delete;
	IconProvider& operator=(const IconProvider&) = delete;

	auto GetThumbnailFromType(const IconType& type)->Thumbnail*;
	auto GetThumbnailFromPath(const std::string& path)->Thumbnail*;

private:
	Context* context;
	ResourceManager* resourceManager;
	std::vector<Thumbnail> thumbnails;
};