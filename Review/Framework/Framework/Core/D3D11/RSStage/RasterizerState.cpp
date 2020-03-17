#include "Framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(Context * context)
	: state(nullptr)
	, backState(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
}

RasterizerState::~RasterizerState()
{
	Clear();
}

void RasterizerState::Create(const D3D11_FILL_MODE & fillMode, const D3D11_CULL_MODE & cullMode)
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.FillMode = fillMode;
	desc.CullMode = cullMode;
	desc.FrontCounterClockwise = false;

	HRESULT hr = graphics->GetDevice()->CreateRasterizerState
	(
		&desc,
		&state
	);
	assert(SUCCEEDED(hr));
}

void RasterizerState::Clear()
{
	SAFE_RELEASE(backState);
	SAFE_RELEASE(state);
}

void RasterizerState::BindPipeline()
{
	graphics->GetDeviceContext()->RSGetState(&backState);
	graphics->GetDeviceContext()->RSSetState(state);
}

void RasterizerState::UnbindPipeline()
{
	graphics->GetDeviceContext()->RSSetState(backState);
	SAFE_RELEASE(backState);
}
