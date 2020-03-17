#pragma once
#include "../ISubsystem.h"

class GameManager final : public ISubsystem
{
public:
	GameManager(class Context* context);
	~GameManager();

	const bool Initialize() override;
	void Update();

	void MainMenu_Start();
	void MainMenu_Exit();
	void LoadGame(int slot);
	void SaveGame(int slot);
	void Exit_To_MainMenu() { BackToMainMenu();	}

	void MainMenu_LoadReady();

	void NormalEnding();
	void TrueEnding();
	void SetGradiateTime(float time) { _gradiate_limitTime = time; }

private:
	void GamePrepare();
	void GameOver();
	void LoadResource();
	void BackToMainMenu();

	void Init_Dialog();
	void Gradiate();

public:
	class Controller* GetProtagonistController();
	class Actor* GetProtagonist() { return protagonist; }
	std::string GetProtagonistLv();
	std::string GetProtagonistMobName();
	void EnforceProtagonistJump();
	void EnforceProtagonistSpeed();

	void MainMenu_SetStack(int var) { _mainMenu_Stack = var; }
	int MainMenu_GetStack() { return _mainMenu_Stack; }
	
	void SetBgm(const std::string& path);

public:
	std::string GetSlotTag(int slot) { return "Slot" + std::to_string(slot) + " "; }
	Data_Save* GetSaveData(int slot) { return saveDatas[slot]; }

private:
	class UIManager* uiManager;
	class SceneManager* sceneManager;
	class PhysicsManager* physicsManager;
	class DataManager* dataManager;
	class DialogManager* dialogManager;
	class InventoryManager* inventoryManager;
	class MonsterManager* monsterManager;
	class Thread* thread;
	class ResourceManager* resourceManager;

private:
	Actor* protagonist = nullptr;
	std::vector<Data_Save*> saveDatas;

	class AudioClip* bgm;

private:
	int _slot = -1;
	int _maxSlot = 3;
	int _mainMenu_Stack = 0;
	float _gradiate_limitTime = 0;
};