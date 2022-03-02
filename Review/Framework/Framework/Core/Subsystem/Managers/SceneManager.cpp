#include "Framework.h"
#include "SceneManager.h"
#include "Framework/Scene/Scene.h"

SceneManager::SceneManager(Context * context)
	: ISubsystem(context)
	, currentScene(nullptr)
{
	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));
}

SceneManager::~SceneManager()
{
	for (auto scene : scenes)
		SAFE_DELETE(scene.second);

	for (auto block : blocks)
		SAFE_DELETE(block.second);

	scenes.clear();
}

const bool SceneManager::Initialize()
{
	InitActorsCommon();
	return true;
}

void SceneManager::Update()
{
	if (!!currentScene)
		currentScene->Update();
}

void SceneManager::ClearScenes()
{
	currentScene = nullptr;

	for (auto scene : scenes)
		SAFE_DELETE(scene.second);

	scenes.clear();
}

void SceneManager::SetCurrentScene(const std::string & sceneName)
{
	if (scenes.count(sceneName) > 0)
	{
		currentScene = scenes[sceneName];
		context->GetSubsystem<Renderer>()->AcquireScene(currentScene);
		context->GetSubsystem<PhysicsManager>()->AcquireScene(currentScene);

	}
}

void SceneManager::RegistScene(const std::string & sceneName, Scene * scene)
{
	if (scenes.count(sceneName) > 0)
	{
		LOG_ERROR("Scene with same name eixst");
		SAFE_DELETE(scenes[sceneName]);
	}
	//1.
	scene->SetName(sceneName);
	scenes[sceneName] = scene;

	//2.
	//scenes.insert(std::make_pair(sceneName, scene));
}

void SceneManager::UnRigistScene(const std::string& sceneName)
{
	auto iter = scenes.find(sceneName);
	if (iter != scenes.end())
	{
		Scene* object = iter->second;
		scenes.erase(iter);
		SAFE_DELETE(object);
	}
}

Scene* SceneManager::CreateScene()
{
	static int tmp = 0;
	Scene* scene = new Scene(context);
	scene->SetName("Scene " + std::to_string(tmp++));
	RegistScene(scene->GetName(), scene);
	return scene;
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	Scene* scene = new Scene(context);
	scene->SetName(name);
	RegistScene(scene->GetName(), scene);
	return scene;
}

Scene* SceneManager::MakeScene(const std::string& name)
{
	Scene* scene = new Scene(context);
	scene->SetName(name);
	return scene;
}

void SceneManager::SaveScene(Scene* scene)
{
	scene->SaveToFile(_default_Path + scene->GetName() + ".scene");
}

Scene* SceneManager::LoadScene(const std::string& path)
{
	std::string name = FileSystem::GetIntactFileNameFromPath(path);
	if (scenes.count(name) > 0)
	{
		if(currentScene != nullptr && currentScene->GetName() == name) 
			currentScene = nullptr;
		LOG_ERROR("Scene with same name exist");
		SAFE_DELETE(scenes[name]);
	}

	Scene* scene = new Scene(context);
	scene->LoadFromFile(path);
	scene->Update();
	RegistScene(scene->GetName(), scene);

	return scene;
}

void SceneManager::SaveScene(const std::string& path, const std::string& name)
{
	if (scenes.find(name) == scenes.end())
	{
		LOG_WARNING("There is no scene with the name %s ", name.data());
		return;
	}
	scenes[name]->SaveToFile(path);
}

void SceneManager::InitActorsCommon()
{
	auto filepaths = FileSystem::GetFilesInDirectory("../../_Assets/Scene/Blocks");
	for (auto filepath : filepaths)
	{
		Actor* actor = new Actor(context);;
		actor->LoadFromFile(filepath);
		actor->SetActive(true);
		actor->Update();
		BlockKind kind = static_cast<BlockKind>(std::atoi(FileSystem::GetIntactFileNameFromPath(filepath).c_str()));
		blocks[kind] = actor;
	}
}

Actor* SceneManager::GetBlock(const BlockKind& var)
{
	if (blocks.find(var) != blocks.end())
		return blocks[var];
	else
		return nullptr;
}

void SceneManager::MoveActorOtherScene(const std::string& sceneName, const std::string& actorName, const Vector3& pos)
{
	if (currentScene->GetName() == sceneName)
		return;

	Scene* destScene = nullptr;
	if (scenes.find(sceneName) != scenes.end())
		destScene = scenes[sceneName];
	else
		destScene = LoadScene(_default_Path + sceneName + ".scene");  // also registed
	if (!destScene)
		return;

	Actor* actor = currentScene->DeleteActor(actorName);
	if (!!actor)
	{
		actor->GetComponent<Controller>()->Teleport(pos);
		destScene->AddActor(actor);
	}
	UnRigistScene(currentScene->GetName());
	SetCurrentScene(destScene->GetName());
}


