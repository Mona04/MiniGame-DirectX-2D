#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class PixelShader final : public IPipeline
{
public:
	PixelShader(class Context* context);
	~PixelShader();

	void Create
	(
		const std::string& path,
		const std::string& entryPoint = "PS",
		const std::string& shaderModel = "ps_5_0",
		D3D_SHADER_MACRO* macros = nullptr
	);
	void Clear();
	void BindPipeline();

	ID3D11PixelShader* GetPixelShader() { return shader; }

private:
	Graphics* graphics;
	ID3D11PixelShader* shader;
	ID3DBlob* blob;
	std::string path;
	std::string entryPoint;
	std::string shaderModel;
};