#include "Framework.h"
#include "ScriptManager.h"
#include <angelscript.h>
#include <AngelScript/scriptbuilder/scriptbuilder.h>
#include <AngelScript/scriptstdstring/scriptstdstring.h>
#include <AngelScript/scriptstdstring/scriptstdwstring.h>

ScriptManager::ScriptManager(class Context* context)
	: ISubsystem(context)
{
	scriptBuilder = new CScriptBuilder();
}

ScriptManager::~ScriptManager()
{
	while (!ctxs.empty())
	{
		ctxs.top()->Release();
		ctxs.pop();
	}

	if (scriptEngine)
	{
		scriptEngine->ShutDownAndRelease();
		scriptEngine = nullptr;
	}
	SAFE_DELETE(scriptBuilder);
}

const bool ScriptManager::Initialize()
{
	scriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	if (!scriptEngine)
	{
		LOG_ERROR("Failed to Created ScriptEngine");
		assert(!scriptEngine);
		return false;
	}

	RegisterStdString(scriptEngine);   // std::string 클래스 넣기
	RegisterStdWString(scriptEngine);   // std::wstring 클래스 넣기
	RegistEnum();
	RegistType();
	RegistSubsystem();
	RegistActor();
	RegistSceneComponent();
	RegistValueType();
	RegistUI();
	scriptEngine->GetStringFactoryReturnTypeId();

	scriptEngine->SetMessageCallback(asMETHOD(ScriptManager, MessageCallback), this, asCALL_THISCALL);
	//scriptEngine->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES, true);
	//scriptEngine->SetEngineProperty(asEP_STRING_ENCODING, 0);
	scriptEngine->SetEngineProperty(asEP_SCRIPT_SCANNER, 0);

	return true;
}


void ScriptManager::MessageCallback(const asSMessageInfo* msg)
{
	char buffer[1024];

	const char* type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";

	sprintf_s(buffer, "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);

#ifndef NDEBUG
	MessageBoxA(nullptr, buffer, nullptr, MB_OK);
#endif
}

asIScriptContext* ScriptManager::RequestContext()
{
	if (ctxs.empty())
		return scriptEngine->CreateContext();
	else
	{
		asIScriptContext* ctx = ctxs.top();
		ctxs.pop();

		return ctx;
	}
}

void ScriptManager::ReturnContext(asIScriptContext* ctx)
{
	ctxs.emplace(ctx);
}
