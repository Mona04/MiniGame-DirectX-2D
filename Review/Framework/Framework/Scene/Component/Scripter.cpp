#include "Framework.h"
#include "Scripter.h"

Scripter::Scripter(Context* context)
	: IComponent(context)
	, script(nullptr)
{
	scriptManager = context->GetSubsystem<ScriptManager>();
	resourceManager = context->GetSubsystem<ResourceManager>();

	IComponent::type = ComponentType::Scripter;
}

Scripter::~Scripter()
{
}

void Scripter::Update()
{
	if(script && script->IsBuilded())
		script->UpdateFunc();
}

void Scripter::Render()
{
}

void Scripter::SetScript(const std::string& path, const std::string& name, void* arg)
{
	if (path == NULL_STRING || path == "" || name == NULL_STRING || name == "")
	{
		this->script = nullptr;
		this->arg = nullptr;
		return;
	}
	
	this->script = resourceManager->Load<Script>(path, name);   // we have to use script immediately , we cant not load script by ohter thread
	this->arg = arg;

	if (!script || !script->IsBuilded())
		return;

	script->ConstructorFunc(arg);
	script->StartFunc();
}
