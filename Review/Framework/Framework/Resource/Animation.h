#pragma once
#include "IResource.h"

enum class RepeatType : uint
{
	Once, Loop
};

struct Keyframe
{
	Keyframe
	(
		const Vector2& offset,
		const Vector2& size,
		const float& time
	)
		: offset(offset)
		, size(size)
		, time(time)
	{}

	Vector2 offset;
	Vector2 size;
	float time;
};

class Animation final : public IResource
{
private:
	friend class ResourceManager;

private:
	Animation(class Context* context);
	~Animation();

	void SaveToFile(const std::string & path) override;
	void LoadFromFile(const std::string & path) override;

public:
	const std::vector<Keyframe>& GetKeyframes() const { return keyframes; }
	Keyframe* GetKeyframeFromIndex(const uint& index);
	const uint GetKeyframeCount() const { return keyframes.size(); }

	void AddKeyframe(const Keyframe& keyframe);
	void AddKeyframe
	(
		const Vector2& offset, 
		const Vector2& size, 
		const float& time
	);
	
	const std::string& GetTexturePath() const { return texturePath; }
	void SetTexturePath(const std::string& path) { texturePath = path; }

	const RepeatType& GetRepeatType() const { return repeatType; }
	void SetRepeatType(const RepeatType& type) { this->repeatType = type; }

private:
	std::vector<Keyframe> keyframes;
	std::string texturePath;

	RepeatType repeatType;
};