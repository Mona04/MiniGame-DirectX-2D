#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class BlendState final : public IPipeline
{
public:
	BlendState(class Context* context);
	~BlendState();

	void Create
	(
		const bool& blendEnable,
		const D3D11_BLEND& srcBlend,
		const D3D11_BLEND& destBlend,
		const D3D11_BLEND_OP& blendOp,
		const D3D11_BLEND& srcBlendAlpha,
		const D3D11_BLEND& destBlendAlpha,
		const D3D11_BLEND_OP& blendOpAlpha,
		const D3D11_COLOR_WRITE_ENABLE& renderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL
	);
	void Clear();
	void BindPipeline();
	void UnbindPipeline();

	ID3D11BlendState* GetState() { return state; }

private:
	class Graphics* graphics;
	
	ID3D11BlendState* state;
	ID3D11BlendState* backState;
};