#pragma once
#include "../ISubsystem.h"

enum class AnimationMotionType : uint
{
	Stand, Walk, Run, Jump, Attack1, Attack2, Hit, Die
};

class SceneManager final : public ISubsystem
{
public:
	SceneManager(class Context* context);
	~SceneManager();

	const bool Initialize() override;
	void Update();

	void ClearScenes();

	class Scene* GetCurrentScene() const { return currentScene; }
	void SetCurrentScene(const std::string& sceneName);
	std::map<std::string, class Scene*>& GetScenes() { return scenes; }

	void RegistScene(const std::string& sceneName, class Scene* scene);
	void UnRigistScene(const std::string& sceneName);

	Scene* CreateScene();
	Scene* CreateScene(const std::string& name);

	Scene* MakeScene(const std::string& name);
	void SaveScene(Scene* scene);
	Scene* LoadScene(const std::string& path);
	void SaveScene(const std::string& path, const std::string& name);

	class Actor* GetBlock(const BlockKind& var);
	
public:
	void MoveActorOtherScene(const std::string& sceneName, const std::string& actorName, const Vector3& pos);

private:
	void InitActorsCommon();

private:
	class Scene* currentScene;
	std::map<std::string, class Scene*> scenes;
	std::map<BlockKind, class Actor*> blocks;
	std::string _default_Path = "../../_Assets/Scene/";
};