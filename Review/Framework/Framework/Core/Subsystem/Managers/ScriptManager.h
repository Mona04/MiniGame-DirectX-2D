#pragma once
#include "../ISubsystem.h"

class ScriptManager : public ISubsystem
{
public:
	ScriptManager(class Context* context);
	~ScriptManager();

	const bool Initialize() override;

	class asIScriptContext* RequestContext();
	void ReturnContext(asIScriptContext* ctx);

	class asIScriptEngine* GetScriptEngine() { return scriptEngine; }

private:
	const bool RegistEnum();
	const bool RegistType();
	const bool RegistSubsystem();
	const bool RegistActor();
	const bool RegistSceneComponent();
	const bool RegistValueType();
	const bool RegistUI();

	void MessageCallback(const struct asSMessageInfo* msg);

private:
	class asIScriptEngine* scriptEngine;
	std::stack<class asIScriptContext*> ctxs;
};