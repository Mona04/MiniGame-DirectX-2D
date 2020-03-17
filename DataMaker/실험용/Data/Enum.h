#pragma once
#include "pch.h"

enum class UIComponentType : uint
{
	Unknown,
	ProgressBar,
	Box,
	Text
};

enum class SamplerType : uint
{
	clamp_point,
	clamp_bilinear,
	wrap_bilinear,
	wrap_trilinear,
	wrap_anisotropic
};

enum class TextureType : uint
{
	Unknown,
	Albedo,
	Normal,
	Emissive
};

enum class MeshType : uint
{
	Unknown,
	Quad,
	ScreenQuad,
	UIQuad,
	Custom
};
