#pragma once
#include "IComponent.h"

enum class AnimationMode : uint
{
	Play,
	Stop,
	Pause,
};

class Animator final : public IComponent
{
public:
	Animator(class Context* context);
	~Animator();

	auto GetCurrentKeyframe()-> struct Keyframe*;
	void SetAnimation(const std::string& path, const std::string& name, class Renderable* material);
	void SetAnimation_Script(const std::string& path);
	void SetAnimation_OriginScale(const std::string& path, class Renderable* material);
	void SetRenderable(class Renderable* renderable) { this->actorRenderable = renderable; }
	class Animation* GetAnimation() { return animation; }
	
	void SetReversed(const bool& var) { isReversed = var; }
	bool IsReversed() { return isReversed; }

	void Play(const float& factor = 1.0f);
	void Stop();
	void Pause();
	void Play_Start() { Stop(); Play(); }

	const bool IsPlaying() const { return animationMode == AnimationMode::Play; }
	const bool IsStop() const { return animationMode == AnimationMode::Stop; }
	const bool IsPause() const { return animationMode == AnimationMode::Pause; }

	void Update() override;
	void Render() override;

	void UpdateBuffer();
	ConstantBuffer* GetAnimationBuffer() { return animationBuffer; }
	void ResetWeight() { weight = -1; }
	void ResetBuffer();

private:
	class ResourceManager* resourceMgr;
	class Timer* timer;

	ConstantBuffer* animationBuffer;
	class Animation* animation;
	class Renderable* actorRenderable;

	Vector2 textureSize;
	float weight;

	AnimationMode animationMode;
	uint curClipNum;
	float frameTimer;

	bool isReversed = true;
	float accelate_factor = 1.0f;
};