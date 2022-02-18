#pragma once

class VertexShader;
class PixelShader;
class InputLayout;
enum class ShaderStage : uint;

class Shader final
{
	friend class ShaderManager;

public:

	Shader(class Context* context);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;


public:
	VertexShader* const GetVertexShader();
	PixelShader* const GetPixelShader();
	InputLayout* const GetInputLayout() { return inputLayout; }

	void AddShader
	(
		const ShaderStage& stage,
		const std::string& path,
		const std::string& entryPoint = "N\A",
		const std::string& shaderModel = "N\A"
	);

	void AddDefine
	(
		const std::string& define,
		const std::string& value = "1"
	);

	void Clear();
	void Clear(const ShaderStage& stage);

	const uint& GetShaderID() { return shaderID; }

private:
	class Context* context;
	class InputLayout* inputLayout;
	std::map<ShaderStage, void*> shaders;
	std::map<std::string, std::string> defines;
	uint shaderID;
};