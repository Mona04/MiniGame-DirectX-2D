#pragma once
#include "IResource.h"

class Script : public IResource
{
private:
	friend class ResourceManager;

private:
	Script(class Context* context);
	~Script();

	Script(const Script&) = delete;
	Script& operator=(const Script&) = delete;

	void SaveToFile(const std::string& path) override;
	void LoadFromFile(const std::string& path) override;

public:
	const bool ConstructorFunc(void* arg);
	const bool StartFunc();
	const bool UpdateFunc();

	const bool IsBuilded() { return this->isBuilded; }

private:
	bool Check(const int& r);
	bool Check(void* pointer) { if (pointer == nullptr) return false; else return true; }

private:
	class ScriptManager* scriptManager;
	class asIScriptEngine* scriptEngine;
	class CScriptBuilder* scriptBuilder;

	std::string path;
	std::string className;
	std::string argName;

	class asIScriptObject* scriptOBJ;
	class asIScriptFunction* constructorFUNC;
	class asIScriptFunction* startFUNC;
	class asIScriptFunction* updateFUNC;

	bool isBuilded = false;
private:
	static int moduleNum;
};