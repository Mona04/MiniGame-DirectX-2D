#pragma once

class Pipeline final
{
public:
	Pipeline(class Context* context);
	~Pipeline();

	Pipeline(const Context&) = delete;
	Pipeline& operator=(const Context&) = delete;

	// IA STAGE
	void SetVertextBuffer(class VertexBuffer* buffer);
	void SetIndexBuffer(class IndexBuffer* buffer);
	void SetInputLayout(class InputLayout* layout);
	void SetPrimitiveTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology);

	// VS STAGE
	void SetVertexShader(class VertexShader* shader);
	void SetVSConstantBuffer(class ConstantBuffer* buffer);
	void SetVSShaderResource(ID3D11ShaderResourceView* srv);
	//void SetVSSamplerState();

	// PS STAGE
	void SetPixelShader(class PixelShader* shader);
	void SetPSConstantBuffer(class ConstantBuffer* buffer);
	void SetPSShaderResource(ID3D11ShaderResourceView* srv);
	//void SetVSSamplerState();

	void BindPipeline();

	void Draw();
	void Draw(const uint& vertexCount, const uint& vertexOffset);

	void DrawIndexed();
	void DrawIndexed(const uint& indexCount, const uint& indexOffset, const uint& vertexOffset);

private:
	void IAStage();
	void VSStage();
	void RSStage();
	void PSStage();
	void OMStage();

private:
	class Context* context;
	class Graphics* graphics;

	class VertexBuffer* vertexBuffer;
	class IndexBuffer* indexBuffer;
	class InputLayout* inputLayout;
	D3D11_PRIMITIVE_TOPOLOGY primitiveTopology;

	class VertexShader* vertexShader;
	std::vector<ID3D11Buffer*> vs_ConstantBuffers;
	std::vector<ID3D11ShaderResourceView*> vs_ShaderResources;
	std::vector<ID3D11SamplerState*> vs_SamplerStates;

	class PixelShader* pixelShader;
	std::vector<ID3D11Buffer*> ps_ConstantBuffers;
	std::vector<ID3D11ShaderResourceView*> ps_ShaderResources;
	std::vector<ID3D11SamplerState*> ps_SamplerStates;

private:
	bool bVertexBuffer;
	bool bIndexBuffer;
	bool bInputLayout;
	bool bPrimitiveTopology;
	bool bVertexShader;
	bool bPixelShader;
};