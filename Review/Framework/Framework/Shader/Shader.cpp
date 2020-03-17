#include "Framework.h"
#include "Shader.h"

Shader::Shader(Context * context)
	: context(context)
	, inputLayout(nullptr)
{
	shaderID = GUIDGenerator::Generate();
}

Shader::~Shader()
{
	SAFE_DELETE(inputLayout);

	for (auto& shader : shaders) {
		if (shader.first == ShaderStage::VS) {
			auto tmp = reinterpret_cast<VertexShader*>(shader.second);
			SAFE_DELETE(tmp);
		}
		else {
			auto tmp = reinterpret_cast<PixelShader*>(shader.second);
			SAFE_DELETE(tmp);
		}
	}

	shaders.clear();
	defines.clear();
}

VertexShader* const Shader::GetVertexShader()
{
	if (shaders.find(ShaderStage::VS) == shaders.end())
		return nullptr;

	return reinterpret_cast<VertexShader*>(shaders[ShaderStage::VS]);
}

PixelShader* const Shader::GetPixelShader()
{
	if (shaders.find(ShaderStage::PS) == shaders.end())
		return nullptr;

	return reinterpret_cast<PixelShader*>(shaders[ShaderStage::PS]);
}

void Shader::AddShader(const ShaderStage & stage, const std::string & path, const std::string & entryPoint, const std::string & shaderModel)
{
	std::vector<D3D_SHADER_MACRO> macros;
	for (const auto& define : defines)
		macros.emplace_back(D3D_SHADER_MACRO{ define.first.c_str(), define.second.c_str() });
	macros.emplace_back(D3D_SHADER_MACRO{ nullptr,nullptr });

	switch (stage)
	{
	case ShaderStage::VS :
	{
		auto iter = shaders.insert(std::make_pair(stage, new VertexShader(context)));
		
		if (iter.second)
		{
			auto shader = reinterpret_cast<VertexShader*>(iter.first->second);
			shader->Create
			(
				path,
				entryPoint == "N/A" ? "VS" : entryPoint,
				shaderModel == "N/A" ? "vs_5_0" : shaderModel,
				macros.data()
			);

			if (!inputLayout)
				inputLayout = new InputLayout(context);
			else
				inputLayout->Clear();

			inputLayout->Create(shader->GetBlob());
		}
		
	} break;
	case ShaderStage::PS:
	{
		auto iter = shaders.insert(std::make_pair(stage, new PixelShader(context)));
		if (iter.second)
		{
			auto shader = reinterpret_cast<PixelShader*>(iter.first->second);
			shader->Create
			(
				path,
				entryPoint == "N/A" ? "PS" : entryPoint,
				shaderModel == "N/A" ? "ps_5_0" : shaderModel,
				macros.data()
			);
		}
	} break;
	}
}

void Shader::AddDefine(const std::string & define, const std::string & value)
{
	defines[define] = value;
}

void Shader::Clear()
{
	for (const auto& shader : shaders)
		Clear(shader.first);
}

void Shader::Clear(const ShaderStage & stage)
{
	switch (stage)
	{
	case ShaderStage::VS:
		reinterpret_cast<VertexShader*>(shaders[stage])->Clear();
		inputLayout->Clear();
		break;
	case ShaderStage::PS:
		reinterpret_cast<PixelShader*>(shaders[stage])->Clear();
		break;
	}
}
