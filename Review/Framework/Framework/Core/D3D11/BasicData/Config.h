#pragma once
#include "Framework.h"

enum class ShaderStage : uint
{
	VS, PS, ALL
};

struct RenderOptionData
{
	int isInstanced;
	int isAnimated;
	int hasAlbedoTexture;
	int hasNormalTexture;
	int hasEmissiveTexture;
	int padding[3];
};

struct CameraData
{
	Matrix view;
	Matrix proj;
	Vector3 cameraPos;
	float camera_near;
	float camera_far;
	float padding[3];
};

struct TransformData
{
	Matrix World;
	Matrix WVP_Current;
	Matrix WVP_Previous;
};

struct AnimationData
{
	Vector2 TextureSize;
	Vector2 SpriteOffset;
	Vector2 SpriteSize;
	float isReversed;
	float weight;
};

struct MaterialData
{
	Color4 Material_albedo;
	Vector2 Material_tiling;
	Vector2 Material_offset;
	float Material_normal_strength;
	float padding[3];
};

struct PostProcessData
{
	Vector2 resolution;
	Vector2 blurDir;
	float blurSigma;
	float  bloomIntensity;
	float padding[2];
};

struct UIData
{
	float isCovered;
	float isClicked;
	float isInstanced;
	float padding;
};