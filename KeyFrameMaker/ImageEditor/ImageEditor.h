#pragma once
enum class RepeatType : uint
{
	Once, Loop
};

struct Keyframe
{
	Keyframe
	(
		const D3DXVECTOR2& offset,
		const D3DXVECTOR2& size,
		const float& time
	)
		: offset(offset)
		, size(size)
		, time(time)
	{}

	D3DXVECTOR2 offset;
	D3DXVECTOR2 size;
	float time;
};


class ImageEditor final
{
public:
	ImageEditor(class Context* context);
	~ImageEditor();

	void Update();

	void Clear();

	void LoadImages(const std::string& path);
	void CombineImages(const std::string& path);
	void MakeInfo(const std::string& path);

	void LoadFrames(const std::string& path);
	void ShowFrames(HDC hdc);
	void ClearFrames();

	std::vector<std::string> Sort(const std::vector<std::string>& path);

	void AddKeyframe(const D3DXVECTOR2& offset, const D3DXVECTOR2& size, const float& time) 
	{
		keyframes.emplace_back(offset, size, time);
	}

	void SetImageFileSavePath(const std::string& path) { imageFileSavePath = path; }
	void SetInfoFileSavePath(const std::string& path) { infoFileSavePath = path; }

private:
	class Context* context;
	std::vector<class Texture*> textures;
	std::vector<float> delays;

	std::vector<std::string> actTypeFolderList;
	std::string imageFileSavePath = "N\A";
	std::string infoFileSavePath = "N\A";

	std::string texturesName;
	std::string texturesPath;
	RepeatType repeatType;

	uint split_height = 0;
	uint split_width = 0;
	uint split_channel = 0;
	uint split_bpp = 0;
	uint split_bpc = 0;
	uint split_pitch = 0;
	int delay;

private:
	std::vector<Keyframe> keyframes;
	std::string resourceName;
	std::string resourcePath;
	ULONG_PTR gdiplusToken;
	class Gdiplus::Image* image;

	int curFrameIndex = 0;
};
