#include "Framework.h"
#include "InventoryManager.h"

InventoryManager::InventoryManager(Context* context)
	: ISubsystem(context)
{
	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));

	uiManager = context->GetSubsystem<UIManager>();
	sceneManager = context->GetSubsystem<SceneManager>();
	dataManager = context->GetSubsystem<DataManager>();
	thread = context->GetSubsystem<Thread>();
}

InventoryManager::~InventoryManager()
{
}

const bool InventoryManager::Initialize()
{
	dialogManager = context->GetSubsystem<DialogManager>();
	mouseManager = context->GetSubsystem<MouseManager>();
	return true;
}

void InventoryManager::Update()
{
	if (!inventory)
		return;

	UpdateCover();
	UpdateClick();
	ShowItemToolTip();
	ShowTmpItem();
}

void InventoryManager::Clear()
{
	inventory = nullptr;
}

void InventoryManager::UpdateCover()
{
	if (!inventory->GetIsVisible())
		return;

	_coveredItemLoc = inventory->GetCoveredItemLoc();
	if (_coveredItemLoc.x < 0 || _coveredItemLoc.y < 0)
	{
		_coveredItem = nullptr;
		return;
	}
	std::string itemName = inventoryData->GetItemName(_coveredItemLoc.x, _coveredItemLoc.y);
	if (itemName == "N\A")
	{
		_coveredItem = nullptr;
		return;
	}
	_coveredItem = dataManager->GetData<Data_Item>(itemName);
}

void InventoryManager::UpdateClick()
{
	if (!inventory->GetIsVisible())
	{
		_coveredItem = nullptr;
		return;
	}
	if (mouseManager->IsClicked())  // pick up item from inventory
	{
		if (_coveredItemLoc.x > -1 && _coveredItemLoc.y > -1)
		{
			DeleteItem(_coveredItemLoc.x, _coveredItemLoc.y, 1);
			_tmpItem = _coveredItem;
			_tmpItemLoc = _coveredItemLoc;
		}
		return;
	}
	else if (mouseManager->IsDragged())
	{

	}
	else if (mouseManager->IsDblClicked())  // consume item in the inventory
	{
		if (_tmpItem)
		{
			//DeleteItem(_coveredItemLoc.x, _coveredItemLoc.y);
			_usedItemCode = _tmpItem->_code;
			_tmpItem = nullptr;
		}
	}
	else  // put back in place or place you want
	{
		if (_tmpItem)
		{
			if (_coveredItemLoc.x > -1 && _coveredItemLoc.y > -1)
			{
				// Insert TmpItem to Covered Loc
				if (!InsertItem(_coveredItemLoc.x, _coveredItemLoc.y, _tmpItem->GetName(), 1))
					// Insert TmpItem to Original Loc
					if (!InsertItem(_tmpItemLoc.x, _tmpItemLoc.y, _tmpItem->GetName(), 1))
						InsertItemAuto(_tmpItem->GetName(), 1);
				_tmpItem = nullptr;
			}
			else
			{
				if (!InsertItem(_tmpItemLoc.x, _tmpItemLoc.y, _tmpItem->GetName(), 1))
					InsertItemAuto(_tmpItem->GetName(), 1);
				_tmpItem = nullptr;
			}
		}
	}
}

void InventoryManager::ShowItemToolTip()
{
	if (!uiManager || !mouseManager) return;

	UI* currentUI = uiManager->GetCurrentUI();
	if (!currentUI) return;

	ToolTip* toolTip = currentUI->GetComponent<ToolTip>();
	if (toolTip == nullptr) return;

	Data_Item* itemData = GetCoveredItem();
	const Vector3& mousePos = mouseManager->GetMousePos();
	if (itemData == nullptr)
	{
		toolTip->SetIsVisible(false);
		return;
	}

	toolTip->ShowItemInfo(mousePos.x, mousePos.y, itemData);
}

void InventoryManager::ShowTmpItem()
{
	if (!uiManager || !mouseManager) return;

	UI* currentUI = uiManager->GetCurrentUI();
	if (!currentUI) return;

	Box* ui = uiManager->GetCurrentUI()->GetComponent<Box>("ItemImage");
	if (ui == nullptr) return;

	Data_Item* itemData = GetTmpItem();
	if (itemData == nullptr)
	{
		ui->SetIsVisible(false);
		return;
	}

	Vector2 itemScale = GetInventory()->GetItemScale();
	ui->GetFirstFrame()->GetRenderable()->SetTexture(TextureType::Albedo, itemData->_imagePath, itemData->_imagePath);
	ui->GetFirstFrame()->GetTransform()->SetScale(Vector3(itemScale.x * itemData->_sizeX, itemScale.y * itemData->_sizeY, 0));
	ui->GetFirstFrame()->GetTransform()->SetPosition(mouseManager->GetMousePos());
	ui->SetIsVisible(true);
}

void InventoryManager::SetInventoryData(const std::string& name)
{
	inventoryData = dataManager->GetData<Data_Inventory>(name);
	inventory->Clear_Items();

	std::string itemName = "N\A";
	int itemAmount = 0;
	for (int x = 0; x < inventoryData->_maxX; x++)
	{
		for (int y = 0; y < inventoryData->_maxY; y++)
		{
			itemName = inventoryData->_itemNames[y * inventoryData->_maxX + x];
			itemAmount = inventoryData->_itemAmount[y * inventoryData->_maxX + x];
			if (itemName != "N\A" && itemName != "Occupied")
				inventory->InsertItem(x, y, dataManager->GetData<Data_Item>(itemName), itemAmount);
		}
	}
}

void InventoryManager::SetInventory(Inventory* in_inventory)
{
	inventory = in_inventory;
}

void InventoryManager::OpenInventory()
{
	inventory->SetIsVisible(true);
}

void InventoryManager::CloseInventory()
{
	inventory->SetIsVisible(false);
}

void InventoryManager::ToggleInventory()
{
	if (!inventory) return;

	inventory->GetIsVisible() ? CloseInventory() : OpenInventory();
}

// === Item Insert / Delete =============================================================

bool InventoryManager::InsertItemAuto(const std::string& itemName, int amount)
{
	Data_Item* itemData = dataManager->GetData<Data_Item>(itemName);
	if (!itemData) return false;

	for (int y = 0; y < inventoryData->_maxY; y++)
		for (int x = 0; x < inventoryData->_maxX; x++)
			if (inventoryData->GetItemName(x, y) == itemName)
				if (InsertItem(x, y, itemName, amount))
					return true;

	for (int y = 0; y < inventoryData->_maxY; y++)
		for (int x = 0; x < inventoryData->_maxX; x++)
		{
			auto loc = inventoryData->InsertItem(x, y, itemData, amount);
			if (loc.first > -1)
			{
				inventory->InsertItem(loc.first, loc.second, itemData, inventoryData->GetItemAmount(loc.first, loc.second));
				context->GetSubsystem<MonsterManager>()->UpdateEvolutionData();  // 스크립트로 빼야하는데
				return true;
			}
			else
			{
				continue;
			}
		}

	return false;
}

bool InventoryManager::InsertItem(int x, int y, const std::string& itemName, int amount)
{
	if (x > inventoryData->_maxX || y > inventoryData->_maxY)
		return false;
	
	Data_Item* itemData = dataManager->GetData<Data_Item>(itemName);
	auto loc = inventoryData->InsertItem(x, y, itemData, amount);

	if (loc.first > -1)
	{
		inventory->InsertItem(loc.first, loc.second, itemData, inventoryData->GetItemAmount(loc.first, loc.second));
		context->GetSubsystem<MonsterManager>()->UpdateEvolutionData();
		return true;
	}
	else
	{
		return false;
	}
}

void InventoryManager::DeleteItem(int x, int y, int amount)
{
	if (x > inventoryData->_maxX || y > inventoryData->_maxY)
		return;

	auto deleted = dataManager->GetData<Data_Item>(inventoryData->GetItemName(x, y));
	auto loc = inventoryData->DeleteItem(x, y, deleted, amount);
	if (loc.first > -1)
	{
		inventory->DeleteItem(loc.first, loc.second, inventoryData->GetItemAmount(loc.first, loc.second));
		context->GetSubsystem<MonsterManager>()->UpdateEvolutionData();
	}
}

bool InventoryManager::DeleteItem_Auto(const std::string& itemName, int amount)
{
	if (amount < 0 || GetItemStock(itemName) <  amount)
		return false;

	std::vector<std::pair<int, int>> itemLoc = inventoryData->GetItemLoc(dataManager->GetData<Data_Item>(itemName));
	Data_Item* deleted = nullptr;

	int leftAmount = amount, tmpAmount = 0;
	for (const auto& _loc : itemLoc)
	{
		deleted = dataManager->GetData<Data_Item>(inventoryData->GetItemName(_loc.first, _loc.second));

		tmpAmount = inventoryData->GetItemAmount(_loc.first, _loc.second);
		tmpAmount = leftAmount > tmpAmount ? tmpAmount : leftAmount;
		leftAmount -= tmpAmount;
	}

	if (leftAmount > 0) return false;


	leftAmount = amount;
	for (const auto& _loc : itemLoc)
	{
		deleted = dataManager->GetData<Data_Item>(inventoryData->GetItemName(_loc.first, _loc.second));

		tmpAmount = inventoryData->GetItemAmount(_loc.first, _loc.second);
		tmpAmount = leftAmount > tmpAmount ? tmpAmount : leftAmount;
		leftAmount -= tmpAmount;

		inventoryData->DeleteItem(_loc.first, _loc.second, deleted, tmpAmount);
		inventory->DeleteItem(_loc.first, _loc.second, inventoryData->GetItemAmount(_loc.first, _loc.second));
	}
	context->GetSubsystem<MonsterManager>()->UpdateEvolutionData();

	return true;
}

void InventoryManager::DeleteItemAll(int x, int y)
{
	if (x > inventoryData->_maxX || y > inventoryData->_maxY)
		return;

	auto deleted = dataManager->GetData<Data_Item>(inventoryData->GetItemName(x, y));
	inventoryData->DeleteItemAll(x, y, deleted);
	inventory->DeleteItemAll(x, y);
	context->GetSubsystem<MonsterManager>()->UpdateEvolutionData();
}

int InventoryManager::GetItemStock(const std::string& itemName)
{
	return !!inventoryData ? inventoryData->GetItemStock(dataManager->GetData<Data_Item>(itemName)) : 0;
}

void InventoryManager::UseItem(const std::string& itemName, int amount)
{
	Data_Item* data = dataManager->GetData<Data_Item>(itemName);
	if (!data) return;

	int stock = GetItemStock(itemName);
	if (stock < amount) return;
	
	DeleteItem_Auto(itemName, amount);
	_usedItemCode = dataManager->GetData<Data_Item>(itemName)->_code;
}
