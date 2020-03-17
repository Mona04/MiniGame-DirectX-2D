#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class RasterizerState final : public IPipeline
{
public:
	RasterizerState(class Context* context);
	~RasterizerState();

	void Create
	(
		const D3D11_FILL_MODE& fillMode,
		const D3D11_CULL_MODE& cullMode
	);
	void Clear();

	void BindPipeline();
	void UnbindPipeline();

	ID3D11RasterizerState* GetState() { return state; }

private:
	class Graphics* graphics;

	ID3D11RasterizerState* state;
	ID3D11RasterizerState* backState;
};