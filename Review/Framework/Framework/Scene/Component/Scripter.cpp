#include "Framework.h"
#include "Scripter.h"
#include <AngelScript/scriptbuilder/scriptbuilder.h>

Scripter::Scripter(Context* context)
	: IComponent(context)
	, script(nullptr), scriptOBJ(nullptr)
{
	scriptManager = context->GetSubsystem<ScriptManager>();
	resourceManager = context->GetSubsystem<ResourceManager>();

	IComponent::type = ComponentType::Scripter;
}

Scripter::~Scripter()
{
	SAFE_RELEASE(scriptOBJ)
}

void Scripter::Update()
{
	if(script && script->IsBuilded())
		script->UpdateFunc(scriptOBJ);
}

void Scripter::Render()
{
}

void Scripter::SetScript(const std::string& path, const std::string& name, void* in_arg)
{
	if (path == NULL_STRING || path == "" || name == NULL_STRING || name == "")
	{
		this->script = nullptr;
		this->arg = nullptr;
		return;
	}
	
	script = resourceManager->Load<Script>(path, name);   // we have to use script immediately , we cant not load script by ohter thread
	arg = in_arg;

	if (!script || !script->IsBuilded())
		return;

	scriptOBJ = script->ConstructorFunc(arg);
	script->StartFunc(scriptOBJ);
}
