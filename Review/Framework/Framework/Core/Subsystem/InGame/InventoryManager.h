#pragma once
#include "../ISubsystem.h"

class InventoryManager final : public ISubsystem
{
public:
	InventoryManager(class Context* context);
	~InventoryManager();

	const bool Initialize() override;
	void Update();

	void Clear();

private:
	void UpdateCover();
	void UpdateClick();

public:
	void SetInventoryData(const std::string& name);
	class Data_Inventory* GetInventoryData() { return inventoryData; }

	void SetInventory(class Inventory* inventory);
	class Inventory* GetInventory() { return inventory; }

	void OpenInventory();
	void CloseInventory();
	void ToggleInventory();

	bool InsertItemAuto(const std::string& itemName, int amount);
	bool InsertItem(int x, int y, const std::string& itemName, int amount);
	void DeleteItem(int x, int y, int amount);
	bool DeleteItem_Auto(const std::string& itemName, int amount);
	void DeleteItemAll(int x, int y);
	int GetItemStock(const std::string& itemName);

	void UseItem(const std::string& itemName, int amount);

public:
	Data_Item* GetCoveredItem() { return _coveredItem; }
	Data_Item* GetTmpItem() { return _tmpItem; }
	int GetUsedItem() { int result = _usedItemCode; _usedItemCode = -1; return result; }

private:
	class UIManager* uiManager;
	class DialogManager* dialogManager;
	class SceneManager* sceneManager;
	class DataManager* dataManager;
	class MouseManager* mouseManager;
	class Thread* thread;

	class Inventory* inventory = nullptr;
	class Data_Inventory* inventoryData = nullptr;

private:
	Data_Item* _coveredItem = nullptr;
	Data_Item* _tmpItem = nullptr;
	int2 _coveredItemLoc = int2(0, 0);
	int2 _tmpItemLoc = int2(0, 0);
	int _usedItemCode = -1;

};