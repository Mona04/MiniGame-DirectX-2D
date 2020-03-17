#pragma once
#include "IResource.h"

enum class SamplerType : uint
{
	clamp_point,
	clamp_bilinear,
	wrap_bilinear,
	wrap_trilinear,
	wrap_anisotropic
};

class Material final : public IResource
{
private:
	friend class ResourceManager;

private:
	Material(class Context* context);
	~Material() = default;

	Material(const Material&) = delete;
	const Material& operator=(const Material&) = delete;

	void SaveToFile(const std::string& path) override;
	void LoadFromFile(const std::string& path) override;

public:
	const Color4& GetAlbedoColor() { return albedoColor; }
	void SetAlbedoColor(const Color4& color) { albedoColor = color; }

	const Vector2& GetUvTiling() const { return uvTiling; }
	void SetUvTiling(const Vector2& tiling) { uvTiling = tiling; }

	const Vector2& GetUvOffset() const { return uvOffset; }
	void SetUvOffset(const Vector2& offset) { uvOffset = offset; }

	const float& GetNormalStrength() const { return normalStrength; }
	void SetNormalStrength(const float& strength) { normalStrength = strength; }

	const SamplerType& GetSamplerType() const { return samplerType; }
	void SetSamplerType(const SamplerType& type) { samplerType = type; }

private:
	Color4 albedoColor;
	Vector2 uvTiling;
	Vector2 uvOffset;
	float normalStrength;

	SamplerType samplerType;
};