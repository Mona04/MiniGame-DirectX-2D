#pragma once
#include "IComponent.h"

class Scripter : public IComponent
{
public:
	Scripter(class Context* context);
	~Scripter();

	void Update() override;
	void Render() override;

	void SetScript(const std::string& path = NULL_STRING, const std::string& name = NULL_STRING, void* arg = nullptr);
	class Script* GetScript() { return script; }

private:
	class ScriptManager* scriptManager;
	class ResourceManager* resourceManager;
	class Script* script;
	void* arg;
};