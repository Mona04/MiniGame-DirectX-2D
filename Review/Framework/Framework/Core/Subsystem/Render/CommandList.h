#pragma once

enum class CommandType : uint
{
	Unknown,
	Begin,
	End,
	Draw,
	DrawIndexed,
	DrawIndexedInstanced,
	SetVertexBuffer,
	SetIndexBuffer,
	SetPrimitiveTopology,
	SetInputLayout,
	SetVertexShader,
	SetPixelShader,
	SetConstantBuffer,
	SetShadeResource,
	SetSampler,
	SetRasterizerState,
	SetBlendState,
	SetDepthStencilState,
	SetViewport,
	SetRenderTarget,
	ClearRenderTarget,
	ClearDepthStencil
};

struct Command final
{
	Command();	
	void Clear();

	CommandType commandType;
	std::string passName;

	ID3D11Buffer* vertexBuffer[2];
	ID3D11Buffer* indexBuffer;
	D3D11_PRIMITIVE_TOPOLOGY primitiveTopology;

	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	
	std::vector<ID3D11Buffer*> cbuffers;
	std::vector<ID3D11ShaderResourceView*> srvs;
	std::vector<ID3D11SamplerState*> samplers;

	ID3D11RasterizerState* rasterizerState;
	ID3D11BlendState* blendState;
	ID3D11DepthStencilState* depthStencilState;

	D3D11_VIEWPORT viewport;

	std::vector<ID3D11RenderTargetView*> renderTargets;
	ID3D11DepthStencilView* depthStencilTarget;
	
	ID3D11RenderTargetView* clear_RenderTarget;
	ID3D11DepthStencilView* clear_DepthStencilTarget;
	
	ShaderStage shaderStage;
	
	uint count;
	uint vertexOffset[2];
	uint indexOffset;
	uint bufferCount;
	uint instanceCount;
	uint stride[2];
	uint slot;
	uint clear_flag;
	uint clear_stencil;
	float clear_depth;
	Color4 clear_color;
};

class CommandList final
{
public:
	CommandList(class Context* context);
	~CommandList();

	void Begin(const std::string& passName);
	void End();

	void SetVertexBuffer(VertexBuffer* vertexBuffer, VertexBuffer* instanceBuffer = nullptr);
	void SetIndexBuffer(IndexBuffer* indexBuffer);
	void SetPrimitiveTopology(const D3D11_PRIMITIVE_TOPOLOGY& primitive_Topology);

	void SetInputLayout(InputLayout* inputLayout);
	void SetVertexShader(VertexShader* shader);
	void SetPixelShader(PixelShader* shader);

	void SetConstantBuffer(const uint& slot, const ShaderStage& stage, ID3D11Buffer* buffer);
	void SetConstantBuffers(const uint& slot, const ShaderStage& stage, std::vector<ID3D11Buffer*> buffer);

	void SetShaderResource(const uint& slot, const ShaderStage& stage, ID3D11ShaderResourceView* resource);
	void SetShaderResources(const uint& slot, const ShaderStage& stage, std::vector<ID3D11ShaderResourceView*> resources);

	void SetSamplerState(const uint& slot, const ShaderStage& stage, ID3D11SamplerState* sampler);
	void SetSamplerStates(const uint& slot, const ShaderStage& stage, const std::vector<ID3D11SamplerState*> samplers);
	
	void SetRSState(ID3D11RasterizerState* state);
	void SetBlendState(ID3D11BlendState* state);
	void SetDepthStencilState(ID3D11DepthStencilState* state);

	void SetViewPort(const D3D11_VIEWPORT& viewport);

	void SetRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStencilTarget = nullptr);
	void SetRenderTargets(const std::vector<ID3D11RenderTargetView*>& renderTarget, ID3D11DepthStencilView* depthStencilTarget = nullptr);
	void ClearRenderTarget(ID3D11RenderTargetView* renderTarget, const Color4& clear_color = Color4(0.0f, 0.0f, 0.0f, 1.0f));
	void ClearRenderTargets(const std::vector<ID3D11RenderTargetView*>& renderTargets, const Color4& clear_color = Color4(0.0f, 0.0f, 0.0f, 1.0f));

	void ClearDetphStencilTarget(ID3D11DepthStencilView* depthStencilTarget, const D3D11_CLEAR_FLAG& clearFlags, const float& clearDetph = 1.0f, const uint& clearStencil = 0);

	void Draw(const uint& vertexCount, const uint& vertexOffset = 0);
	void DrawIndexed(const uint& indexCount, const uint& indexOffset, const uint& vertexOffset);
	void DrawIndexedInstanced(const uint& indexCount, const uint& instanceCount);

	const bool Submit();

private:
	Command& GetCommand();
	void Clear();

private:
	Graphics* graphics;
	std::vector<Command> commands;
	uint command_capacity;
	uint command_count;

	ID3D11RasterizerState* BackupRSState;
	ID3D11BlendState* BackupBlendState;
	ID3D11DepthStencilState* BackupDepthStencilState;
};