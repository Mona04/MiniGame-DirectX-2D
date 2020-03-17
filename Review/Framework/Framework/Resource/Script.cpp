#include "Framework.h"
#include "Script.h"
#include <AngelScript/scriptbuilder/scriptbuilder.h>

int Script::moduleNum = 0;

Script::Script(Context* context)
	: IResource(context)
	, scriptManager(nullptr)
	, scriptEngine(nullptr)
	, scriptBuilder(nullptr)
	, path("")
	, className("")
	, scriptOBJ(nullptr)
	, startFUNC(nullptr)
	, updateFUNC(nullptr)
	, constructorFUNC(nullptr)
{
	scriptManager = context->GetSubsystem<ScriptManager>();
	scriptEngine = scriptManager->GetScriptEngine();
	scriptBuilder = new CScriptBuilder();
}

Script::~Script()
{
	SAFE_DELETE(scriptBuilder);
}

void Script::SaveToFile(const std::string& path)
{
}

void Script::LoadFromFile(const std::string& path)
{
	std::vector<std::string> names =  FileSystem::GetPartOfName(path);
	this->className = names[0];
	this->argName = names[1];
	this->path = path;
	this->isBuilded = false;
	int r;

	//BuilderSet
	r = scriptBuilder->StartNewModule(scriptEngine, (className + std::to_string(moduleNum++)).c_str()); if(!Check(r)) return;
	r = scriptBuilder->AddSectionFromFile(path.c_str()); if (!Check(r)) return;
	r = scriptBuilder->BuildModule(); if (!Check(r)) return;

	//Get functions in the script
	int typeID = scriptBuilder->GetModule()->GetTypeIdByDecl(className.c_str()); if(!Check(typeID)) return;
	asITypeInfo* type = scriptEngine->GetTypeInfoById(typeID);  if (!Check(type)) return;
	startFUNC = type->GetMethodByDecl("void Start()"); if (!Check(startFUNC)) return;
	updateFUNC = type->GetMethodByDecl("void Update()"); if (!Check(updateFUNC)) return;
	constructorFUNC = type->GetFactoryByDecl((className + " @" + className + "(" + argName + " @)").c_str()); if (!Check(constructorFUNC)) return;
	
	isBuilded = true;
}

const bool Script::ConstructorFunc(void* arg)
{
	asIScriptContext* ctx = scriptEngine->RequestContext();
	{
		int r;
		r = ctx->Prepare(constructorFUNC); assert(r == 0);
		r = ctx->SetArgObject(0, arg); assert(r == 0);
		r = ctx->Execute(); assert(r == 0);

		scriptOBJ = *static_cast<asIScriptObject * *>(ctx->GetAddressOfReturnValue());
		scriptOBJ->AddRef();

		r = ctx->Unprepare(); assert(r >= 0);
	}
	scriptEngine->ReturnContext(ctx);

	return true;
}

const bool Script::StartFunc()
{
	asIScriptContext* ctx = scriptManager->RequestContext();
	{
		int r;
		r = ctx->Prepare(startFUNC); if (!Check(r)) return false;
		r = ctx->SetObject(scriptOBJ); if (!Check(r)) return false;
		r = ctx->Execute(); if (!Check(r)) return false;;
		r = ctx->Unprepare(); if (!Check(r)) return false;
	}
	scriptManager->ReturnContext(ctx);
	return true;
}

const bool Script::UpdateFunc()
{
	asIScriptContext* ctx = scriptManager->RequestContext();
	{
		int r;
		r = ctx->Prepare(updateFUNC); if (!Check(r)) return false;
		r = ctx->SetObject(scriptOBJ); if (!Check(r)) return false;
		r = ctx->Execute(); if (!Check(r)) return false;
		r = ctx->Unprepare(); if (!Check(r)) return false;
	}
	scriptManager->ReturnContext(ctx);

	return true;
}

bool Script::Check(const int& r)
{
	if (r < 0)
	{
		isBuilded = false;
		return false;
	}
	else
	{
		return true;
	}
}



