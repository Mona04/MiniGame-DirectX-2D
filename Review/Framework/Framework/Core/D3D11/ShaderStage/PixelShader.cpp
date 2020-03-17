#include "Framework.h"
#include "PixelShader.h"
#include "../D3DHelper.h"

PixelShader::PixelShader(Context * context)
	: shader(nullptr)
	, blob(nullptr)
	, path("")
	, entryPoint("")
	, shaderModel("")
{
	graphics = context->GetSubsystem<Graphics>();
}

PixelShader::~PixelShader()
{
	Clear();
}

void PixelShader::Create(const std::string & path, const std::string & entryPoint, const std::string& shaderModel, D3D_SHADER_MACRO* macros)
{
	this->path = path;
	this->entryPoint = entryPoint;
	this->shaderModel = shaderModel;

	auto result = D3D11_Helper::CompileShader(path, entryPoint, shaderModel, macros, &blob);
	if (!result)
	{
		LOG_ERROR("Fail Creating Shader");
		return;
	}

	HRESULT hr = graphics->GetDevice()->CreatePixelShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);

	assert(SUCCEEDED(hr));
}

void PixelShader::Clear()
{
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void PixelShader::BindPipeline()
{
	graphics->GetDeviceContext()->PSSetShader(shader, nullptr, 0);
}
