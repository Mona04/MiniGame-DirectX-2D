#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class Sampler final : public IPipeline
{
public:
	Sampler(class Context* context);
	~Sampler();

	Sampler(const Sampler&) = default;
	Sampler& operator=(const Sampler&) = delete;

	ID3D11SamplerState* GetState() const { return state; }

	void Create
	(
		const D3D11_FILTER& filter = D3D11_FILTER_ANISOTROPIC,
		const D3D11_TEXTURE_ADDRESS_MODE& address_mode = D3D11_TEXTURE_ADDRESS_WRAP,
		const D3D11_COMPARISON_FUNC& comparision = D3D11_COMPARISON_ALWAYS
	);
	void Clear();

private:
	class Graphics* graphics;
	ID3D11SamplerState* state;
};