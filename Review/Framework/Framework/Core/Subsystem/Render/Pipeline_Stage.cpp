#include "Framework.h"
#include "Pipeline.h"

void Pipeline::IAStage()
{
	if (bVertexBuffer)
	{
		vertexBuffer->BindPipeline();
		bVertexBuffer = false;
	}

	if (bIndexBuffer)
	{
		indexBuffer->BindPipeline();
		bIndexBuffer = false;
	}

	if (bInputLayout)
	{
		inputLayout->BindPipeline();
		bInputLayout = false;
	}

	if (bPrimitiveTopology)
	{
		graphics->GetDeviceContext()->IASetPrimitiveTopology(primitiveTopology);
		bPrimitiveTopology = false;
	}
}

void Pipeline::VSStage()
{
	if (bVertexShader)
	{
		vertexShader->BindPipeline();
		bVertexShader = false;
	}

	if (!vs_ConstantBuffers.empty())
	{
		graphics->GetDeviceContext()->VSSetConstantBuffers
		(
			1,
			vs_ConstantBuffers.size(),
			vs_ConstantBuffers.data()
		);

		vs_ConstantBuffers.clear();
		vs_ConstantBuffers.shrink_to_fit();
	}

	if (!vs_ShaderResources.empty())
	{
		graphics->GetDeviceContext()->VSSetShaderResources
		(
			0,
			vs_ShaderResources.size(),
			vs_ShaderResources.data()
		);

		vs_ShaderResources.clear();
		vs_ShaderResources.shrink_to_fit();
	}

	if (!vs_SamplerStates.empty())
	{
		graphics->GetDeviceContext()->VSGetSamplers
		(
			0,
			vs_SamplerStates.size(),
			vs_SamplerStates.data()
		);

		vs_SamplerStates.clear();
		vs_SamplerStates.shrink_to_fit();
	}
}

void Pipeline::RSStage()
{
}

void Pipeline::PSStage()
{
	if (bPixelShader)
	{
		pixelShader->BindPipeline();
		bPixelShader = false;
	}

	if (!ps_ConstantBuffers.empty())
	{
		graphics->GetDeviceContext()->PSSetConstantBuffers
		(
			0,
			ps_ConstantBuffers.size(),
			ps_ConstantBuffers.data()
		);

		ps_ConstantBuffers.clear();
		ps_ConstantBuffers.shrink_to_fit();
	}

	if (!ps_ShaderResources.empty())
	{
		graphics->GetDeviceContext()->PSSetShaderResources
		(
			0,
			ps_ShaderResources.size(),
			ps_ShaderResources.data()
		);

		ps_ShaderResources.clear();
		ps_ShaderResources.shrink_to_fit();
	}

	if (!ps_SamplerStates.empty())
	{
		graphics->GetDeviceContext()->PSGetSamplers
		(
			0,
			ps_SamplerStates.size(),
			ps_SamplerStates.data()
		);

		ps_SamplerStates.clear();
		ps_SamplerStates.shrink_to_fit();
	}
}

void Pipeline::OMStage()
{
}
