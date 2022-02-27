#pragma once
#include "../ISubsystem.h"


// Script 로 빼내야하는 거 임시로 둔 서브시스템

class ExtraManager final : public ISubsystem
{
public:
	ExtraManager(class Context* context);
	~ExtraManager();

	void Clear();

	const bool Initialize() override;
	void Update();

	void UpdateSaveLoad();

private:
	void Update_MainGame();
	bool Synchronization_MainGame();

private:
	class UIManager* uiManager;
	class SceneManager* sceneManager;
	class DataManager* dataManager;
	class DialogManager* dialogManager;
	class InventoryManager* inventoryManager;
	class MonsterManager* monsterManager;
	class Thread* thread;
	class ResourceManager* resourceManager;
	class MouseManager* mouseManager;

private:
	UI* mainGame = nullptr;
	ProgressBar* hp_Bar = nullptr;
	ProgressBar* mp_Bar = nullptr;
	ProgressBar* sp_Bar = nullptr;
	ProgressBar* exp_Bar = nullptr;
	class Box* menuButton = nullptr;
	class VerticalList* verticalList = nullptr;
	class SaveLoad* saveLoad = nullptr;

	Controller* protagonist_controller = nullptr;
};