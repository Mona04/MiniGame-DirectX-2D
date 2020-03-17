#include "Framework.h"
#include "SamplerState.h"

Sampler::Sampler(Context* context)
	: state(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
}

Sampler::~Sampler()
{
	Clear();
}

void Sampler::Create(const D3D11_FILTER& filter, const D3D11_TEXTURE_ADDRESS_MODE& address_mode, const D3D11_COMPARISON_FUNC& comparision)
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Filter = filter;
	desc.AddressU = address_mode;
	desc.AddressV = address_mode;
	desc.AddressW = address_mode;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 16;
	desc.ComparisonFunc = comparision;
	desc.BorderColor[0] = 0.7f;
	desc.BorderColor[1] = 0.3f;
	desc.BorderColor[2] = 0.0f;
	desc.BorderColor[3] = 1.0f;
	desc.MinLOD = std::numeric_limits<float>::min();
	desc.MaxLOD = std::numeric_limits<float>::max();

	auto result = SUCCEEDED(graphics->GetDevice()->CreateSamplerState(&desc, &state));
	if (!result)
	{
		LOG_ERROR("Failed to create sampler state");
		return;
	}
}

void Sampler::Clear()
{
	SAFE_RELEASE(state);
}
