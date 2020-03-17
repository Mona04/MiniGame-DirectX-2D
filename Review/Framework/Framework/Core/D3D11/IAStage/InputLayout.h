#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class InputLayout final : public IPipeline
{
public:
	InputLayout(class Context* context);
	~InputLayout();

	void Create
	(
		D3D11_INPUT_ELEMENT_DESC* descs,
		const uint& count,
		ID3DBlob* blob
	);
	void Create(ID3DBlob* blob);

	void Clear();
	void BindPipeline();

	ID3D11InputLayout* GetInputLayout() { return inputLayout; }

private:
	class Graphics* graphics;
	ID3D11InputLayout* inputLayout;
};