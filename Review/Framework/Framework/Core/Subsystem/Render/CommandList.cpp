#include "Framework.h"
#include "CommandList.h"

Command::Command()
{
	cbuffers.reserve(D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
	srvs.reserve(D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
	samplers.reserve(D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT);
	renderTargets.reserve(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);
	Clear();
}

void Command::Clear()
{
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	cbuffers.clear();
	srvs.clear();
	samplers.clear();
	renderTargets.clear();

	commandType = CommandType::Unknown;
	passName = "N/A";
	
	vertexBuffer[0] = nullptr;	vertexBuffer[1] = nullptr;
	indexBuffer = nullptr;
	primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	inputLayout = nullptr;
	vertexShader = nullptr;
	pixelShader = nullptr;
	
	rasterizerState = nullptr;
	blendState = nullptr;
	depthStencilState = nullptr;

	depthStencilTarget = nullptr;
	clear_RenderTarget = nullptr;
	clear_DepthStencilTarget = nullptr;

	shaderStage = ShaderStage::VS;
	count = 0;
	vertexOffset[0] = 0;
	vertexOffset[1] = 0;
	indexOffset = 0;
	instanceCount = 0;
	bufferCount = 0;
	stride[0] = 0;
	stride[1] = 0;
	slot = 0;
	clear_flag = 0;
	clear_stencil = 0;
	clear_depth = 0;
	clear_color = Color4(0.0f, 0.0f, 0.0f, 0.0f);
}

CommandList::CommandList(Context * context)
	: command_capacity(2048)
	, command_count(0)
	, BackupRSState(nullptr)
	, BackupBlendState(nullptr)
	, BackupDepthStencilState(nullptr)
{
	commands.reserve(command_capacity);
	commands.resize(command_capacity);

	graphics = context->GetSubsystem<Graphics>();
}

CommandList::~CommandList()
{
	Clear();
}

void CommandList::Begin(const std::string & passName)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::Begin;
	cmd.passName = passName;
}

void CommandList::End()
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::End;
}

void CommandList::SetVertexBuffer(VertexBuffer* buffer, VertexBuffer* instanceBuffer)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetVertexBuffer;
	cmd.vertexBuffer[0] = buffer->GetBuffer();
	cmd.vertexBuffer[1] = instanceBuffer ? instanceBuffer->GetBuffer() : nullptr;
	cmd.count = buffer->GetVertexCount();
	cmd.vertexOffset[0] = buffer->GetVertexOffset();
	cmd.vertexOffset[1] = instanceBuffer ? instanceBuffer->GetVertexOffset() : 0;
	cmd.stride[0] = buffer->GetVertexStride();
	cmd.stride[1] = instanceBuffer ? instanceBuffer->GetVertexStride() : 0;
	cmd.bufferCount = instanceBuffer ? 2 : 1;
}

void CommandList::SetIndexBuffer(IndexBuffer * buffer)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetIndexBuffer;
	cmd.indexBuffer = buffer->GetBuffer();
	cmd.count = buffer->GetIndexCount();
	cmd.indexOffset = buffer->GetIndexOffset();
}

void CommandList::SetPrimitiveTopology(const D3D11_PRIMITIVE_TOPOLOGY & primitive_Topology)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetPrimitiveTopology;
	cmd.primitiveTopology = primitive_Topology;
}

void CommandList::SetInputLayout(InputLayout * inputLayout)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetInputLayout;
	cmd.inputLayout = inputLayout->GetInputLayout();
}

void CommandList::SetVertexShader(VertexShader * shader)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetVertexShader;
	cmd.vertexShader = shader->GetVertexShader();
}

void CommandList::SetPixelShader(PixelShader * shader)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetPixelShader;
	cmd.pixelShader = shader->GetPixelShader();
}

void CommandList::SetConstantBuffer(const uint & slot, const ShaderStage & stage, ID3D11Buffer * buffer)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetConstantBuffer;
	cmd.slot = slot;
	cmd.shaderStage = stage;
	cmd.count = 1;
	cmd.cbuffers.emplace_back(buffer);
}

void CommandList::SetConstantBuffers(const uint & slot, const ShaderStage & stage, std::vector<ID3D11Buffer*> buffers)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetConstantBuffer;
	cmd.slot = slot;
	cmd.shaderStage = stage;
	cmd.count = 1;
	cmd.cbuffers = buffers;
}

void CommandList::SetShaderResource(const uint & slot, const ShaderStage & stage, ID3D11ShaderResourceView * resource)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetShadeResource;
	cmd.slot = slot;
	cmd.shaderStage = stage;
	cmd.count = 1;
	cmd.srvs.emplace_back(resource);
}

void CommandList::SetShaderResources(const uint & slot, const ShaderStage & stage, std::vector<ID3D11ShaderResourceView*> resources)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetShadeResource;
	cmd.slot = slot;
	cmd.shaderStage = stage;
	cmd.count = resources.size();
	cmd.srvs = resources;
}

void CommandList::SetSamplerState(const uint & slot, const ShaderStage & stage, ID3D11SamplerState * sampler)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetSampler;
	cmd.slot = slot;
	cmd.shaderStage = stage;
	cmd.count = 1;
	cmd.samplers.emplace_back(sampler);
}

void CommandList::SetSamplerStates(const uint & slot, const ShaderStage & stage, const std::vector<ID3D11SamplerState*> samplers)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetSampler;
	cmd.slot = slot;
	cmd.shaderStage = stage;
	cmd.count = samplers.size();
	cmd.samplers = samplers;
}

void CommandList::SetRSState(ID3D11RasterizerState * state)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetRasterizerState;
	cmd.rasterizerState = state;
}

void CommandList::SetBlendState(ID3D11BlendState * state)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetBlendState;
	cmd.blendState = state;
}

void CommandList::SetDepthStencilState(ID3D11DepthStencilState* state)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetDepthStencilState;
	cmd.depthStencilState = state;
}

void CommandList::SetViewPort(const D3D11_VIEWPORT & viewport)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetViewport;
	cmd.viewport = viewport;
}

void CommandList::SetRenderTarget(ID3D11RenderTargetView * renderTarget, ID3D11DepthStencilView * depthStencilTarget)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetRenderTarget;
	cmd.count = 1;
	cmd.depthStencilTarget = depthStencilTarget ? depthStencilTarget : nullptr;
	cmd.renderTargets.emplace_back(renderTarget ? renderTarget : nullptr);
}

void CommandList::SetRenderTargets(const std::vector<ID3D11RenderTargetView*>& renderTargets, ID3D11DepthStencilView * depthStencilTarget)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::SetRenderTarget;
	cmd.count = renderTargets.size();
	cmd.depthStencilTarget = depthStencilTarget ? depthStencilTarget : nullptr;
	cmd.renderTargets = renderTargets;
}

void CommandList::ClearRenderTarget(ID3D11RenderTargetView * renderTarget, const Color4 & clear_color)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::ClearRenderTarget;
	cmd.clear_RenderTarget = renderTarget ? renderTarget : nullptr;
	cmd.clear_color = clear_color;
}

void CommandList::ClearRenderTargets(const std::vector<ID3D11RenderTargetView*>& renderTargets, const Color4 & clear_color)
{
	for (const auto& target : renderTargets)
		ClearRenderTarget(target, clear_color);
}

void CommandList::ClearDetphStencilTarget(ID3D11DepthStencilView * depthStencilTarget, const D3D11_CLEAR_FLAG & clearFlags, const float & clearDetph, const uint & clearStencil)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::ClearDepthStencil;
	cmd.clear_DepthStencilTarget = depthStencilTarget ? depthStencilTarget : nullptr;
	cmd.clear_flag = clearFlags;
	cmd.clear_depth = clearDetph;
	cmd.clear_stencil = clearStencil;
}

void CommandList::Draw(const uint & vertexCount, const uint & vertexOffset)
{
	Command& cmd = GetCommand();
	cmd.commandType = CommandType::Draw;
	cmd.count = vertexCount;
	cmd.vertexOffset[0] = vertexOffset;
}

void CommandList::DrawIndexed(const uint & indexCount, const uint & indexOffset, const uint & vertexOffset)
{
	auto& cmd = GetCommand();
	cmd.commandType = CommandType::DrawIndexed;
	cmd.count = indexCount;
	cmd.indexOffset = indexOffset;
	cmd.vertexOffset[0] = vertexOffset;
}

void CommandList::DrawIndexedInstanced(const uint& indexCount, const uint& instanceCount)
{
	auto& cmd = GetCommand();
	cmd.commandType = CommandType::DrawIndexedInstanced;
	cmd.count = indexCount;
	cmd.instanceCount = instanceCount;
}

const bool CommandList::Submit()
{
	ID3D11DeviceContext* deviceContext = graphics->GetDeviceContext();
	bool isThereSetRSState = false;
	bool isThereSetBlendState = false;
	bool isThereSetDepthStencilState = false;

	for (uint i = 0; i < command_count; i++)
	{
		Command& cmd = commands[i];

		switch (cmd.commandType)
		{
		case CommandType::Begin:
			break;
		case CommandType::End:
			break;
		case CommandType::SetVertexBuffer:
			deviceContext->IASetVertexBuffers(cmd.slot, cmd.bufferCount, &cmd.vertexBuffer[0], &cmd.stride[0], &cmd.vertexOffset[0]);
			break;
		case CommandType::SetIndexBuffer:
			deviceContext->IASetIndexBuffer(cmd.indexBuffer, DXGI_FORMAT_R32_UINT, cmd.indexOffset);
			break;
		case CommandType::SetPrimitiveTopology:
			deviceContext->IASetPrimitiveTopology(cmd.primitiveTopology);
			break;
		case CommandType::SetInputLayout:
			deviceContext->IASetInputLayout(cmd.inputLayout);
			break;
		case CommandType::SetVertexShader:
			deviceContext->VSSetShader(cmd.vertexShader, nullptr, 0);
			break;
		case CommandType::SetPixelShader:
			deviceContext->PSSetShader(cmd.pixelShader, nullptr, 0);
			break;
		case CommandType::SetConstantBuffer:
		{
			switch (cmd.shaderStage)
			{
			case ShaderStage::ALL:
				deviceContext->VSSetConstantBuffers(cmd.slot, cmd.count, cmd.cbuffers.data());
				deviceContext->PSSetConstantBuffers(cmd.slot, cmd.count, cmd.cbuffers.data());
				break;
			case ShaderStage::VS:
				deviceContext->VSSetConstantBuffers(cmd.slot, cmd.count, cmd.cbuffers.data());
				break;
			case ShaderStage::PS: 
				deviceContext->PSSetConstantBuffers(cmd.slot, cmd.count, cmd.cbuffers.data());
				break;
			}
		} break;
		case CommandType::SetShadeResource:
		{
			switch (cmd.shaderStage)
			{
			case ShaderStage::ALL:
				deviceContext->VSSetShaderResources(cmd.slot, cmd.count, cmd.srvs.data());
				deviceContext->PSSetShaderResources(cmd.slot, cmd.count, cmd.srvs.data());
				break;
			case ShaderStage::VS:
				deviceContext->VSSetShaderResources(cmd.slot, cmd.count, cmd.srvs.data());
				break;
			case ShaderStage::PS:
				deviceContext->PSSetShaderResources(cmd.slot, cmd.count, cmd.srvs.data());
				break;
			}
		} break;
		case CommandType::SetSampler:
		{
			switch (cmd.shaderStage)
			{
			case ShaderStage::ALL:
				deviceContext->VSSetSamplers(cmd.slot, cmd.count, cmd.samplers.data());
				deviceContext->PSSetSamplers(cmd.slot, cmd.count, cmd.samplers.data());
				break;
			case ShaderStage::VS:
				deviceContext->VSSetSamplers(cmd.slot, cmd.count, cmd.samplers.data());
				break;
			case ShaderStage::PS:
				deviceContext->PSSetSamplers(cmd.slot, cmd.count, cmd.samplers.data());
				break;
			}
		} break;
		case CommandType::SetRasterizerState:
			deviceContext->RSGetState(&BackupRSState);
			deviceContext->RSSetState(cmd.rasterizerState);
			isThereSetRSState = true;
			break;
		case CommandType::SetBlendState:
			deviceContext->OMGetBlendState(&BackupBlendState, nullptr, nullptr);
			deviceContext->OMSetBlendState(cmd.blendState, nullptr, 0xffffffff);
			isThereSetBlendState = true;
			break;
		case CommandType::SetDepthStencilState: 
			deviceContext->OMGetDepthStencilState(&BackupDepthStencilState, nullptr);
			deviceContext->OMSetDepthStencilState(cmd.depthStencilState, 1);
			isThereSetDepthStencilState = true;
			break;
		case CommandType::SetViewport:
			deviceContext->RSSetViewports(1, &cmd.viewport);
			break;
		case CommandType::SetRenderTarget:
			deviceContext->OMSetRenderTargets(cmd.count, cmd.renderTargets.data(), cmd.depthStencilTarget);
			break;
		case CommandType::ClearRenderTarget:
			deviceContext->ClearRenderTargetView(cmd.clear_RenderTarget, cmd.clear_color);
			break;
		case CommandType::ClearDepthStencil:
			deviceContext->ClearDepthStencilView(cmd.clear_DepthStencilTarget, cmd.clear_flag, cmd.clear_depth, cmd.clear_stencil);
			break;
		case CommandType::Draw:
			deviceContext->Draw(cmd.count, cmd.vertexOffset[0]);
			break;
		case CommandType::DrawIndexed:
			deviceContext->DrawIndexed(cmd.count, cmd.indexOffset, cmd.vertexOffset[0]);
			break;
		case CommandType::DrawIndexedInstanced:
			deviceContext->DrawIndexedInstanced(cmd.count, cmd.instanceCount, cmd.indexOffset, cmd.vertexOffset[0], cmd.vertexOffset[1]);
			break;
		}
	}

	SAFE_RELEASE(BackupRSState);
	SAFE_RELEASE(BackupBlendState);
	SAFE_RELEASE(BackupDepthStencilState);

	Clear();

	return true;
}

Command & CommandList::GetCommand()
{
	if (command_count >= commands.size())
	{
		uint new_size = command_count + 100;
		commands.reserve(new_size);
		commands.resize(new_size);

		LOG_WARNING_F(
			"Command list has grown to fit %d command. Consider making the capacity larger to avoid re-allocations.",
			command_count
		);
	}

	return commands[command_count++];
}

void CommandList::Clear()
{
	for (uint i = 0; i < command_count; i++)
		commands[i].Clear();

	command_count = 0;
}
