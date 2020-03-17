#pragma once

enum class ScriptLanguage : uint
{
	C, 
	CPlusPlus,
	AngelScript,
	HLSL
};

class ToolScript final
{
public:
	static const std::string BaseScriptCode;

public:
	static ToolScript* Get()
	{
		static ToolScript instance;
		return &instance;
	}

	void Initialize(class Context* context);
	void Render();

	void SetScript(const std::string& path);
	void SetScriptLanguage(const ScriptLanguage& language);

	const bool& InVisible() { return isVisible; }
	void SetIsVisible(const bool& var) { isVisible = var; }
	
private:
	ToolScript() = default;
	~ToolScript() = default;

	void CreateNewScript();

private:
	class Context* context;
	std::string path;
	bool isVisible;
};