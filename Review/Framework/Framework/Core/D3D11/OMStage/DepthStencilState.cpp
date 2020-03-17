#include "Framework.h"
#include "DepthStencilState.h"

DepthStencilState::DepthStencilState(Context* context)
	: state(nullptr)
	, backState(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
}

DepthStencilState::~DepthStencilState()
{
	Clear();
}

void DepthStencilState::Create(const bool& depthEnable, const D3D11_DEPTH_WRITE_MASK& srcBlend, const D3D11_COMPARISON_FUNC& comparisionFunc)
{
	D3D11_DEPTH_STENCIL_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	desc.DepthEnable = depthEnable;
	desc.DepthWriteMask = srcBlend;
	desc.DepthFunc = comparisionFunc;

	HRESULT hr = graphics->GetDevice()->CreateDepthStencilState
	(
		&desc,
		&state
	);
	assert(SUCCEEDED(hr));
}

void DepthStencilState::Clear()
{
	SAFE_RELEASE(backState);
	SAFE_RELEASE(state);
}

void DepthStencilState::BindPipeline()
{
	graphics->GetDeviceContext()->OMGetDepthStencilState(&backState, nullptr);
	graphics->GetDeviceContext()->OMSetDepthStencilState(state, 1);
}

void DepthStencilState::UnbindPipeline()
{
	graphics->GetDeviceContext()->OMSetDepthStencilState(backState, 1);
	SAFE_RELEASE(backState);
}
