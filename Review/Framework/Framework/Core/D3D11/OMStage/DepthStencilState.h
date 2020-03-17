#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class DepthStencilState final : public IPipeline
{
public:
	DepthStencilState(class Context* context);
	~DepthStencilState();

	void Create
	(
		const bool& depthEnable, 
		const D3D11_DEPTH_WRITE_MASK& srcBlend = D3D11_DEPTH_WRITE_MASK_ALL,
		const D3D11_COMPARISON_FUNC& comparisionFunc = D3D11_COMPARISON_LESS
	);
	void Clear();
	void BindPipeline();
	void UnbindPipeline();

	ID3D11DepthStencilState* GetState() { return state; }

private:
	class Graphics* graphics;

	ID3D11DepthStencilState* state;
	ID3D11DepthStencilState* backState;
};