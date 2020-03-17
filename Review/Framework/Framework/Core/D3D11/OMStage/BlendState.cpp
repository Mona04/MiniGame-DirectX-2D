#include "Framework.h"
#include "BlendState.h"

BlendState::BlendState(Context * context)
	: state(nullptr)
	, backState(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
}

BlendState::~BlendState()
{
	Clear();
}

void BlendState::Create(const bool & blendEnable, const D3D11_BLEND & srcBlend, const D3D11_BLEND & destBlend, const D3D11_BLEND_OP & blendOp, const D3D11_BLEND & srcBlendAlpha, const D3D11_BLEND & destBlendAlpha, const D3D11_BLEND_OP & blendOpAlpha, const D3D11_COLOR_WRITE_ENABLE & renderTargetWriteMask)
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
	desc.AlphaToCoverageEnable = true;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable			= blendEnable;
	desc.RenderTarget[0].SrcBlend				= srcBlend;
	desc.RenderTarget[0].DestBlend				= destBlend;
	desc.RenderTarget[0].BlendOp				= blendOp;
	desc.RenderTarget[0].SrcBlendAlpha			= srcBlendAlpha;
	desc.RenderTarget[0].DestBlendAlpha			= destBlendAlpha;
	desc.RenderTarget[0].BlendOpAlpha			= blendOpAlpha;
	desc.RenderTarget[0].RenderTargetWriteMask	= renderTargetWriteMask;
	
	HRESULT hr = graphics->GetDevice()->CreateBlendState
	(
		&desc,
		&state
	);
	
	assert(SUCCEEDED(hr));
}

void BlendState::Clear()
{
	SAFE_RELEASE(backState);
	SAFE_RELEASE(state);
}

void BlendState::BindPipeline()
{
	graphics->GetDeviceContext()->OMGetBlendState(&backState, nullptr, nullptr);
	graphics->GetDeviceContext()->OMSetBlendState(state, nullptr, 0xffffffff);
}

void BlendState::UnbindPipeline()
{
	graphics->GetDeviceContext()->OMSetBlendState(backState, nullptr, 0xffffffff);
	SAFE_RELEASE(backState);
}
