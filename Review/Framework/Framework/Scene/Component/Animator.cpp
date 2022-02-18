#include "Framework.h"
#include "Animator.h"

Animator::Animator(Context * context)
	: IComponent(context)
	, animationMode(AnimationMode::Stop)
	, curClipNum(0)
	, frameTimer(0.0f)
	, actorRenderable(nullptr)
	, animation(nullptr)
	, weight(-1)
{
	timer = context->GetSubsystem<Timer>();
	resourceMgr = context->GetSubsystem<ResourceManager>();
	IComponent::type = ComponentType::Animator;

	animationBuffer = new ConstantBuffer(context);
	animationBuffer->Create<AnimationData>();
}

Animator::~Animator()
{
	SAFE_DELETE(animationBuffer);
}

auto Animator::GetCurrentKeyframe() -> Keyframe*
{
	if (!animation)
		return nullptr;

	return animation->GetKeyframeFromIndex(curClipNum);
}

void Animator::SetAnimation(const std::string& path, const std::string& name, class Renderable* renderable)
{
	if(actorRenderable == nullptr)
		actorRenderable = renderable;

	animation = resourceMgr->Load<Animation>(path, name);  // as we use animator immediately, Animation should not be loaded by thread

	actorRenderable->SetTexture(TextureType::Albedo, animation->GetTexturePath(), animation->GetTexturePath());
	Texture* animationTexture = actorRenderable->GetTexture(TextureType::Albedo);

	animationMode = AnimationMode::Stop;

	textureSize.x = static_cast<float>(animationTexture->GetWidth());
	textureSize.y = static_cast<float>(animationTexture->GetHeight());

	weight = textureSize.x;

	animationMode = AnimationMode::Play;
	frameTimer = 0.0f;
	curClipNum = 0;

	UpdateBuffer();
}

void Animator::SetAnimation_Script(const std::string& path)
{
	if(!animation)
		animation = resourceMgr->Load<Animation>(path, path);
	else if (animation->GetResourcePath() == path)
	{
		Play();
		curClipNum = 0;
	}
	else
		animation = resourceMgr->Load<Animation>(path, path);

	actorRenderable->SetTexture(TextureType::Albedo, animation->GetTexturePath(), animation->GetTexturePath());
	Texture* animationTexture = actorRenderable->GetTexture(TextureType::Albedo);

	textureSize.x = static_cast<float>(animationTexture->GetWidth());
	textureSize.y = static_cast<float>(animationTexture->GetHeight());

	animationMode = AnimationMode::Play;
	frameTimer = 0.0f;
	curClipNum = 0;

	UpdateBuffer();
}

void Animator::SetAnimation_OriginScale(const std::string& path, Renderable* renderable)
{
	actorRenderable = renderable;

	if (!animation)
		animation = resourceMgr->Load<Animation>(path, path);
	else if (animation->GetResourcePath() == path)
	{
		Play();
		curClipNum = 0;
	}
	else
		animation = resourceMgr->Load<Animation>(path, path);

	actorRenderable->SetTexture(TextureType::Albedo, animation->GetTexturePath(), animation->GetTexturePath());
	Texture* animationTexture = actorRenderable->GetTexture(TextureType::Albedo);

	textureSize.x = static_cast<float>(animationTexture->GetWidth());
	textureSize.y = static_cast<float>(animationTexture->GetHeight());

	weight = 1;

	animationMode = AnimationMode::Play;
	frameTimer = 0.0f;
	curClipNum = 0;

	UpdateBuffer();
}

void Animator::Play(const float& factor)
{
	animationMode = AnimationMode::Play;
	this->accelate_factor = factor;
}

void Animator::Stop()
{
	animationMode = AnimationMode::Stop;
	frameTimer = 0.0f;
	curClipNum = 0;
}

void Animator::Pause()
{
	animationMode = AnimationMode::Pause;
}

void Animator::Update()
{
	if (textureSize.x < 1 && actorRenderable)
	{
		Texture* animationTexture = actorRenderable->GetTexture(TextureType::Albedo);
		textureSize.x = static_cast<float>(animationTexture->GetWidth());
		textureSize.y = static_cast<float>(animationTexture->GetHeight());
		weight = textureSize.x;
	}

	if (animation && animationMode == AnimationMode::Play)
	{
		frameTimer += timer->GetDeltaTimeMs() * accelate_factor;
		Keyframe* keyframe = animation->GetKeyframeFromIndex(curClipNum);
		float time = 0;
		if(keyframe)
			 time = animation->GetKeyframeFromIndex(curClipNum)->time;
		
		if (frameTimer > time)
		{
			curClipNum++;

			switch (animation->GetRepeatType())
			{
			case RepeatType::Once:
				if (curClipNum >= animation->GetKeyframeCount())
				{
					curClipNum = animation->GetKeyframeCount() - 1;
					Pause();
				}
				break;

			case RepeatType::Loop:
				curClipNum %= animation->GetKeyframeCount();
				break;
			}

			frameTimer = 0;
		}
	}

	UpdateBuffer();
}

void Animator::Render()
{
	animationBuffer->BindPipeline(ShaderStage::VS, 1);
}

void Animator::UpdateBuffer()
{
	auto aniData = animationBuffer->Map<AnimationData>();
	{
		auto keyframe = GetCurrentKeyframe();
		if (!keyframe)
		{
			animationBuffer->Unmap();
			return;
		}
		aniData->SpriteOffset = keyframe->offset;
		aniData->SpriteSize = keyframe->size;
		aniData->TextureSize = Vector2(textureSize.x, textureSize.y);
		aniData->isReversed = isReversed ? 1.f : 0.f;
		aniData->weight = weight;
	}
	animationBuffer->Unmap();
}

void Animator::ResetBuffer()
{
	auto aniData = animationBuffer->Map<AnimationData>();
	{
		aniData->SpriteOffset = Vector2(0, 0);
		aniData->SpriteSize = Vector2(1, 1);
		aniData->TextureSize = Vector2(1, 1);
		aniData->isReversed = 0;
		aniData->weight = 1;
	}
	animationBuffer->Unmap();
}
