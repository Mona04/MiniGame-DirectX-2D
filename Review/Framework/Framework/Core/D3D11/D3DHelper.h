#pragma once
#include "Framework.h"

namespace D3D11_Helper
{
	inline const bool CheckShaderError(const HRESULT& hr, ID3DBlob* error)
	{
		if (FAILED(hr)) 
		{
			if (error != nullptr)
			{
				std::string str = reinterpret_cast<const char*>(error->GetBufferPointer());
				Log::ErrorF("Shader : %s ", str.c_str());
			}
			return false;
		}
		return true;
	}

	inline const bool CompileShader
	(
		const std::string& path,
		const std::string& entryPoint,
		const std::string& shaderModel,
		D3D_SHADER_MACRO* defines,
		ID3DBlob** blob
	)
	{
#ifdef _DEBUG
		int shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#else
		uint shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
		ID3DBlob* error = nullptr;
		auto hr = D3DCompileFromFile
		(
			FileSystem::ToWstring(path).c_str(),
			defines,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entryPoint.c_str(),
			shaderModel.c_str(),
			shaderFlags,
			0,
			blob,
			&error
		);

		auto result = CheckShaderError(hr, error);

		SAFE_RELEASE(error);
		return result;
	}
}

