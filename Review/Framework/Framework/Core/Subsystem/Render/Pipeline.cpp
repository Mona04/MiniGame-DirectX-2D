#include "Framework.h"
#include "Pipeline.h"

Pipeline::Pipeline(Context * context)
	: context(context)
	, vertexBuffer(nullptr)
	, indexBuffer(nullptr)
	, inputLayout(nullptr)
	, primitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, vertexShader(nullptr)
	, pixelShader(nullptr)
	, bVertexBuffer(false)
	, bIndexBuffer(false)
	, bInputLayout(false)
	, bPrimitiveTopology(true)
	, bVertexShader(false)
	, bPixelShader(false)
{
	graphics = context->GetSubsystem<Graphics>();
}

Pipeline::~Pipeline()
{
	// 딴데서 포인터 얻어오는 거라서 제거하면 안됨
}

void Pipeline::SetVertextBuffer(VertexBuffer * buffer)
{
	if (!buffer)
	{
		LOG_ERROR("Invalid Error");
		return;
	}

	if (vertexBuffer) {
		if (vertexBuffer->GetID() == buffer->GetID())
			return;
	}

	vertexBuffer = buffer;
	bVertexBuffer = true;
}

void Pipeline::SetIndexBuffer(IndexBuffer * buffer)
{
	if (!buffer)
	{
		LOG_ERROR("Invalid Error");
		return;
	}

	if (indexBuffer) {
		if (indexBuffer->GetID() == buffer->GetID())
			return;
	}

	indexBuffer = buffer;
	bIndexBuffer = true;
}

void Pipeline::SetInputLayout(InputLayout * layout)
{
	if (!layout)
	{
		LOG_ERROR("Invalid Error");
		return;
	}

	if (inputLayout) {
		if (inputLayout->GetID() == layout->GetID())
			return;
	}

	inputLayout = layout;
	bInputLayout = true;
}

void Pipeline::SetPrimitiveTopology(const D3D11_PRIMITIVE_TOPOLOGY & topology)
{
	if (primitiveTopology == topology)
		return;

	primitiveTopology = topology;
	bPrimitiveTopology = true;
}

void Pipeline::SetVertexShader(VertexShader * shader)
{
	if (!shader)
	{
		LOG_ERROR("Invalid Error");
		return;
	}

	if (vertexShader) {
		if (vertexShader->GetID() == shader->GetID())
			return;
	}

	vertexShader = shader;
	bVertexShader = true;
}

void Pipeline::SetVSConstantBuffer(ConstantBuffer * buffer)
{
	if (!buffer)
	{
		LOG_ERROR("Invalid Parameter");
		return;
	}

	vs_ConstantBuffers.emplace_back(buffer->GetBuffer());
}

void Pipeline::SetVSShaderResource(ID3D11ShaderResourceView * srv)
{
	if(!srv)
	{
		LOG_ERROR("Invalid Parameter");
		return;
	}

	vs_ShaderResources.emplace_back(srv);
}

void Pipeline::SetPixelShader(PixelShader * shader)
{
	if (!shader)
	{
		LOG_ERROR("Invalid Error");
		return;
	}

	if (pixelShader) {
		if (pixelShader->GetID() == shader->GetID())
			return;
	}

	pixelShader = shader;
	bPixelShader = true;
}

void Pipeline::SetPSConstantBuffer(ConstantBuffer * buffer)
{
	if (!buffer)
	{
		LOG_ERROR("Invalid Parameter");
		return;
	}

	ps_ConstantBuffers.emplace_back(buffer->GetBuffer());
}

void Pipeline::SetPSShaderResource(ID3D11ShaderResourceView * srv)
{
	if (!srv)
	{
		LOG_ERROR("Invalid Parameter");
		return;
	}

	ps_ShaderResources.emplace_back(srv);
}

void Pipeline::BindPipeline()
{
	IAStage();
	VSStage();
	RSStage();
	PSStage();
	OMStage();
}

void Pipeline::Draw()
{
	if (!vertexBuffer)
	{
		LOG_ERROR("Invalid parameter");
		return;
	}
	
	graphics->GetDeviceContext()->Draw
	(
		vertexBuffer->GetVertexCount(),
		vertexBuffer->GetVertexOffset()
	);
}

void Pipeline::Draw(const uint & vertexCount, const uint & vertexOffset)
{
	if (!vertexBuffer)
	{
		LOG_ERROR("Invalid parameter");
		return;
	}

	graphics->GetDeviceContext()->Draw
	(
		vertexCount,
		vertexOffset
	);
}

void Pipeline::DrawIndexed()
{
	if (!vertexBuffer || !indexBuffer)
	{
		LOG_ERROR("Invalid parameter");
		return;
	}

	graphics->GetDeviceContext()->DrawIndexed
	(
		indexBuffer->GetIndexCount(),
		indexBuffer->GetIndexOffset(),
		vertexBuffer->GetVertexOffset()
	);
}

void Pipeline::DrawIndexed(const uint & indexCount, const uint & indexOffset, const uint & vertexOffset)
{
	if (!vertexBuffer || !indexBuffer || indexCount == 0)
	{
		LOG_ERROR("Invalid parameter");
		return;
	}

	graphics->GetDeviceContext()->DrawIndexed
	(
		indexCount,
		indexOffset,
		vertexOffset
	);
}