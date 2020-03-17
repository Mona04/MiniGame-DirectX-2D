#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class VertexShader final : public IPipeline
{
public:
	VertexShader(class Context* context);
	~VertexShader();

	ID3DBlob* GetBlob() const { return blob; }
	ID3D11VertexShader* GetVertexShader() { return shader; }

	void Create
	(
		const std::string& path,
		const std::string& entryPoint = "VS",
		const std::string& shaderModel = "vs_5_0",
		D3D_SHADER_MACRO* macros = nullptr
	);
	void Clear();
	void BindPipeline();

private:
	Graphics* graphics;
	ID3D11VertexShader* shader;
	ID3DBlob* blob;
	std::string path;
	std::string entryPoint;
	std::string shaderModel;
};